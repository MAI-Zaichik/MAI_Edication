#pragma once
#include <string>
#include <vector>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <random>

#include "entities.hpp"
#include "const.hpp"

class Observer;   
class FightVisitor;

class NPC {
protected:
    NPCType type;
    float x, y;
    std::string name;
    bool alive = true;
    std::vector<std::weak_ptr<Observer>> observers;
    
    mutable std::shared_mutex mtx;

public:
    NPC(NPCType t, float x_, float y_, std::string n)
    : type(t), x(x_), y(y_), name(std::move(n)) {
    x = std::max(0.0f, std::min(x, static_cast<float>(MAP_WIDTH)));
    y = std::max(0.0f, std::min(y, static_cast<float>(MAP_HEIGHT)));
}
    
    virtual ~NPC() = default;

    NPCType getType() const { 
        std::shared_lock lock(mtx);
        return type; 
    }
    
    std::string getName() const { 
        std::shared_lock lock(mtx);
        return name; 
    }
    
    float getX() const { 
        std::shared_lock lock(mtx);
        return x; 
    }
    
    float getY() const { 
        std::shared_lock lock(mtx);
        return y; 
    }
    
    bool isAlive() const { 
        std::shared_lock lock(mtx);
        return alive; 
    }

    void move() {
        if (!isAlive()) return;
    
        std::unique_lock lock(mtx);
    
        thread_local static std::mt19937 gen(std::random_device{}());
        thread_local static std::uniform_real_distribution<> dis(-1.0, 1.0);
    
        float speed = Movement::GetSpeed(type);
        float dx = dis(gen) * speed;
        float dy = dis(gen) * speed;
        
        x = x + dx;
        y = y + dy;
        x = std::max(0.0f, std::min(x, static_cast<float>(MAP_WIDTH)));
        y = std::max(0.0f, std::min(y, static_cast<float>(MAP_HEIGHT)));
    }
    
    void kill() { 
        std::unique_lock lock(mtx);
        alive = false; 
    }
    
    void attach(std::shared_ptr<Observer> obs) {
        std::unique_lock lock(mtx);
        observers.emplace_back(obs);
    }
    
    void notify(std::shared_ptr<NPC> victim);
    virtual bool canKill(const NPC& other) const = 0;
    virtual void accept(class FightVisitor& v) = 0;
    
    bool IsInRange(const NPC& other) const {
        std::shared_lock lock1(mtx);
        std::shared_lock lock2(other.mtx);
        
        float killRange = Movement::GetRange(type);
        float dx = x - other.x;
        float dy = y - other.y;
        float dist = std::sqrt(dx*dx + dy*dy);
        
        return dist <= killRange;
    }

    bool fight(NPC& other) {
        if (!isAlive() || !other.isAlive()) return false;
        
        thread_local static std::random_device rd;
        thread_local static std::mt19937 gen(rd());
        std::uniform_int_distribution<> dice(1, 6);
        
        int attackPower = dice(gen);
        int defensePower = dice(gen);
        
        return attackPower > defensePower;
    }
};