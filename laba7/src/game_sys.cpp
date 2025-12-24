#include "../include/game_sys.hpp"
#include "../include/factory.hpp"
#include "../include/observer.hpp"
#include "../include/const.hpp"
#include <iostream>
#include <chrono>
#include <random>

std::mutex GameSystem::coutMutex;

GameSystem::GameSystem() {
    auto consoleObs = std::make_shared<ConsoleObserver>();
    auto fileObs = std::make_shared<TextObserver>();

    for (auto& npc : npcs) {
        npc->attach(consoleObs);
        npc->attach(fileObs);
    }
}

GameSystem::~GameSystem() {
    stop();
}

void GameSystem::initialize() {
    std::unique_lock lock(npcsMutex);
    npcs.clear();

    for (int i = 0; i < NPC_COUNT; ++i) {
        npcs.push_back(CreateRandNPC(i));
    }
    
    {
        std::lock_guard<std::mutex> coutLock(coutMutex);
        std::cout << "Created " << npcs.size() << " NPCs\n";
        std::cout << "Game will run for " << GAME_TIME << " seconds\n";
    }
}

std::shared_ptr<NPC> GameSystem::CreateRandNPC(int id) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    
    std::uniform_int_distribution<> typeDist(0, 2);
    NPCType type = static_cast<NPCType>(typeDist(gen));
    
    std::uniform_real_distribution<> coordDist(0.0f, 100.0f);
    float x = coordDist(gen);
    float y = coordDist(gen);
    
    std::string name;
    switch (type) {
        case DragonType: name = "Dragon_" + std::to_string(id); break;
        case BullType: name = "Bull_" + std::to_string(id); break;
        case ToadType: name = "Toad_" + std::to_string(id); break;
        default: name = "Unknown_" + std::to_string(id); break;
    }
    
    return NPCFactory::createNPC(type, x, y, name);
}

void GameSystem::start() {
    running = true;
    
    movementThread = std::thread(&GameSystem::move_work, this);
    fightThread = std::thread(&GameSystem::fight_work, this);
    printThread = std::thread(&GameSystem::print_work, this);
    
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << "Game started!\n";
    }
}

void GameSystem::stop() {
    running = false;   
    queueCV.notify_all();

    if (movementThread.joinable()) movementThread.join();
    if (fightThread.joinable()) fightThread.join();
    if (printThread.joinable()) printThread.join();
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << "Game stopped!\n";
    }
}

void GameSystem::move_work() {
    while (running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        
        std::shared_lock lock(npcsMutex);
        
        for (auto& npc : npcs) {
            if (npc->isAlive()) {
                npc->move();
                
                for (auto& other : npcs) {
                    if (npc == other || !other->isAlive()) continue;
                    
                    if ((npc->canKill(*other) || other->canKill(*npc)) &&
                        npc->IsInRange(*other)) {
                        AddFightTask(npc, other);
                    }
                }
            }
        }
    }
}

void GameSystem::AddFightTask(std::shared_ptr<NPC> a, std::shared_ptr<NPC> d) {
    std::lock_guard<std::mutex> lock(queueMutex);
    queueFight.emplace(a, d);
    queueCV.notify_one();
}

void GameSystem::fight_work() {
    while (running) {
        FightTask task(nullptr, nullptr);
        
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            
            queueCV.wait(lock, [this]() {
                return !queueFight.empty() || !running;
            });
            
            if (!running && queueFight.empty()) break;
            
            if (!queueFight.empty()) {
                task = std::move(queueFight.front());
                queueFight.pop();
            }
        }
        
        if (task.attacker && task.defender) {
            if (!task.attacker->isAlive() || !task.defender->isAlive()) {
                continue;
            }
            
            std::shared_ptr<NPC> attacker, defender;
            
            if (task.attacker->canKill(*task.defender)) {
                attacker = task.attacker;
                defender = task.defender;
            } else if (task.defender->canKill(*task.attacker)) {
                attacker = task.defender;
                defender = task.attacker;
            } else {
                continue;
            }
            
            if (!attacker->IsInRange(*defender)) {
                continue;
            }
            
            if (attacker->fight(*defender)) {
                defender->kill();
                attacker->notify(defender);
                
                {
                    std::lock_guard<std::mutex> coutLock(coutMutex);
                    std::cout << attacker->getName() << " wins the fight against "
                              << defender->getName() << "!\n";
                }
            }
        }
    }
}

void GameSystem::print_work() {
    auto startTime = std::chrono::steady_clock::now();
    
    while (running) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
        printMap();
        
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTime);
        
        if (elapsed.count() >= GAME_TIME) {
            running = false;
            queueCV.notify_all();
            
            {
                std::lock_guard<std::mutex> lock(coutMutex);
                std::cout << "\n=== TIME'S UP! ===\n";
                printMap();
                printSurvivors();
            }
            
            break;
        }
    }
}

void GameSystem::printMap() const {
    const int width = MAP_WIDTH;
    const int height = MAP_HEIGHT;
    
    std::lock_guard<std::mutex> lock(coutMutex);
    
    std::cout << "\n=== MAP ===\n";

    char map[height][width];
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            map[i][j] = '.';
        }
    }

    std::shared_lock npcLock(npcsMutex);
    for (const auto& npc : npcs) {
        if (npc->isAlive()) {
            int x = static_cast<int>((npc->getX() / MAP_WIDTH) * (width - 1));
            int y = static_cast<int>((npc->getY() / MAP_HEIGHT) * (height - 1));
            
            if (x >= 0 && x < width && y >= 0 && y < height) {
                switch (npc->getType()) {
                    case DragonType: map[y][x] = 'D'; break;
                    case BullType: map[y][x] = 'B'; break;
                    case ToadType: map[y][x] = 'T'; break;
                    default: map[y][x] = '?'; break;
                }
            }
        }
    }

    for (int i = 0; i < height; ++i) {
        std::cout << "|";
        for (int j = 0; j < width; ++j) {
            std::cout << map[i][j];
        }
        std::cout << "|\n";
    }
    
    // Статистика
    int aliveCount = 0;
    for (const auto& npc : npcs) {
        if (npc->isAlive()) aliveCount++;
    }
    
    std::cout << "Alive: " << aliveCount << "/" << npcs.size() << "\n";
}

void GameSystem::printSurvivors() const {
    std::shared_lock lock(npcsMutex);
    
    std::cout << "\n=== SURVIVORS LIST ===\n";
    
    int count = 0;
    int dragons = 0, bulls = 0, toads = 0;
    
    for (const auto& npc : npcs) {
        if (npc->isAlive()) {
            count++;

            switch (npc->getType()) {
                case DragonType: dragons++; break;
                case BullType: bulls++; break;
                case ToadType: toads++; break;
            }
        }
    }
    
    if (count == 0) {
        std::cout << "No survivors! Everyone died.\n";
    } else {
        std::cout << "\n=== ITOG ===\n";
        std::cout << "Total survivors: " << count << "\n";
        std::cout << "  Dragons: " << dragons << "\n";
        std::cout << "  Bulls:   " << bulls << "\n";
        std::cout << "  Toads:   " << toads << "\n";
        
    }
}