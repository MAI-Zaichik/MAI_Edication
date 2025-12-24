
#include "../include/npc.hpp"
#include "../include/observer.hpp"
#include "../include/fight.hpp"
#include "../include/factory.hpp"

void NPC::notify(std::shared_ptr<NPC> victim) {
    for (auto& w : observers) {
        if (auto obs = w.lock()) {
            obs->onKill(*this, *victim);
        }
    }
}

class Dragon : public NPC {
public:
    Dragon(float x, float y, std::string name)
        : NPC(DragonType, x, y, std::move(name)) {}

    bool canKill(const NPC& other) const override {
        return other.getType() == BullType;
    }

    void accept(FightVisitor& v) override {
        v.visit(std::shared_ptr<NPC>(this, [](NPC*){}));
    }
};

class Bull : public NPC {
public:
    Bull(float x, float y, std::string name)
        : NPC(BullType, x, y, std::move(name)) {}

    bool canKill(const NPC& other) const override {
        return other.getType() == ToadType;
    }

    void accept(FightVisitor& v) override {
        v.visit(std::shared_ptr<NPC>(this, [](NPC*){}));
    }
};

class Toad : public NPC {
public:
    Toad(float x, float y, std::string name)
        : NPC(ToadType, x, y, std::move(name)) {}

    bool canKill(const NPC& other) const override {
        return false;
    }

    void accept(FightVisitor& v) override {
        v.visit(std::shared_ptr<NPC>(this, [](NPC*){}));
    }
};

std::shared_ptr<NPC> NPCFactory::createNPC(
    NPCType type, float x, float y, const std::string& name
) {
    switch (type) {
        case DragonType: return std::make_shared<Dragon>(x, y, name);
        case BullType: return std::make_shared<Bull>(x, y, name);
        case ToadType: return std::make_shared<Toad>(x, y, name);
        default: return nullptr;
    }
}

std::string typeToString(NPCType t) {
    switch (t) {
        case DragonType: return "Dragon";
        case BullType: return "Bull";
        case ToadType: return "Toad";
        default: return "Unknown";
    }
}

std::istream& operator>>(std::istream& is, NPCType& t) {
    int value = 0;
    if (is >> value) {
        if (value >= DragonType && value <= BullType)
            t = static_cast<NPCType>(value);
        else
            t = Unknown;
    }
    return is;
}
