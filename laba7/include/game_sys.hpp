#pragma once
#include <vector>
#include <memory>
#include <thread>
#include <atomic>
#include <mutex>
#include <queue>
#include <functional>
#include <condition_variable>
#include "npc.hpp"

struct FightTask {
    std::shared_ptr<NPC> attacker;
    std::shared_ptr<NPC> defender;
    
    FightTask(std::shared_ptr<NPC> a, std::shared_ptr<NPC> d)
        : attacker(std::move(a)), defender(std::move(d)) {}
};

class GameSystem {
private:
    std::vector<std::shared_ptr<NPC>> npcs;

    std::thread movementThread;
    std::thread fightThread;
    std::thread printThread;
    
    std::atomic<bool> running{true};

    std::queue<FightTask> queueFight;
    std::mutex queueMutex;
    std::condition_variable queueCV;
    
    static std::mutex coutMutex;
    mutable std::shared_mutex npcsMutex;
    
public:
    GameSystem();
    ~GameSystem();
    
    void initialize();
    void start();
    void stop();
    
private:
    void move_work();
    void fight_work();
    void print_work();

    void AddFightTask(std::shared_ptr<NPC> a, std::shared_ptr<NPC> d);
    void printMap() const;
    void printSurvivors() const;

    std::shared_ptr<NPC> CreateRandNPC(int id);
};