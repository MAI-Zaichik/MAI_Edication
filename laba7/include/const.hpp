#pragma once

constexpr int MAP_WIDTH = 100;
constexpr int MAP_HEIGHT = 100;
constexpr int GAME_TIME = 30;
constexpr int NPC_COUNT = 50;

namespace Movement {
    constexpr float DRAGON_SPEED = 50.0f;
    constexpr float DRAGON_KILL_RANGE = 30.0f;
    
    constexpr float BULL_SPEED = 30.0f;
    constexpr float BULL_KILL_RANGE = 10.0f;
    
    constexpr float TOAD_SPEED = 1.0f;
    constexpr float TOAD_KILL_RANGE = 10.0f;


    inline float GetSpeed(int type) {
        switch (type) {
            case DragonType: return DRAGON_SPEED;
            case BullType: return BULL_SPEED;
            case ToadType: return TOAD_SPEED;
            default: return 0.0f;
        }
    }
    
    inline float GetRange(int type) {
        switch (type) {
            case DragonType: return DRAGON_KILL_RANGE;
            case BullType: return BULL_KILL_RANGE;
            case ToadType: return TOAD_KILL_RANGE;
            default: return 0.0f;
        }
    }
}