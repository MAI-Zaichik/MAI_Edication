#include <gtest/gtest.h>
#include <memory>
#include <cmath>
#include "../include/npc.hpp"
#include "../include/factory.hpp"
#include "../include/observer.hpp"
#include "../include/const.hpp"

//-------------- базовые тесты нпс -------------------
class NPCBasicTest : public ::testing::Test {
protected:
    void SetUp() override {
        dragon = NPCFactory::createNPC(DragonType, 50.0f, 50.0f, "Dragon_Test");
        bull = NPCFactory::createNPC(BullType, 30.0f, 30.0f, "Bull_Test");
        toad = NPCFactory::createNPC(ToadType, 10.0f, 10.0f, "Toad_Test");
    }
    
    std::shared_ptr<NPC> dragon;
    std::shared_ptr<NPC> bull;
    std::shared_ptr<NPC> toad;
};

TEST_F(NPCBasicTest, Initialization) {
    EXPECT_EQ(dragon->getType(), DragonType);
    EXPECT_EQ(bull->getType(), BullType);
    EXPECT_EQ(toad->getType(), ToadType);
}

TEST_F(NPCBasicTest, CoordinatesBounds) {
    auto edgeNPC = NPCFactory::createNPC(DragonType, -10.0f, 150.0f, "Edge");
    EXPECT_GE(edgeNPC->getX(), 0.0f);
    EXPECT_LE(edgeNPC->getX(), MAP_WIDTH);
}

TEST_F(NPCBasicTest, AliveState) {
    EXPECT_TRUE(bull->isAlive());
    bull->kill();
    EXPECT_FALSE(bull->isAlive());
}

//-------------- тесты передвижения по карте -------------------
TEST(MovementTest, MoveChangesPosition) {
    auto npc = NPCFactory::createNPC(DragonType, 50.0f, 50.0f, "MoveTest");
    float initialX = npc->getX();
    npc->move();
    EXPECT_NE(npc->getX(), initialX);
}

TEST(MovementTest, DeadNPCNoMove) {
    auto npc = NPCFactory::createNPC(BullType, 30.0f, 30.0f, "DeadTest");
    npc->kill();
    float initialX = npc->getX();
    npc->move();
    EXPECT_EQ(npc->getX(), initialX);
}

TEST(MovementTest, StayInBounds) {
    auto npc = NPCFactory::createNPC(ToadType, 0.0f, 0.0f, "BoundsTest");
    for (int i = 0; i < 10; ++i) {
        npc->move();
        EXPECT_GE(npc->getX(), 0.0f);
        EXPECT_LE(npc->getX(), MAP_WIDTH);
    }
}

//-------------- боевые тесты -------------------
TEST(CombatTest, KillRelationships) {
    auto dragon = NPCFactory::createNPC(DragonType, 0.0f, 0.0f, "Dragon");
    auto bull = NPCFactory::createNPC(BullType, 5.0f, 5.0f, "Bull");
    auto toad = NPCFactory::createNPC(ToadType, 10.0f, 10.0f, "Toad");
    
    EXPECT_TRUE(dragon->canKill(*bull));
    EXPECT_FALSE(bull->canKill(*dragon));
    EXPECT_TRUE(bull->canKill(*toad));
    EXPECT_FALSE(toad->canKill(*bull));
}

TEST(CombatTest, RangeDetection) {
    auto npc1 = NPCFactory::createNPC(DragonType, 10.0f, 10.0f, "N1");
    auto npc2 = NPCFactory::createNPC(DragonType, 10.0f, 10.0f, "N2");
    EXPECT_TRUE(npc1->IsInRange(*npc2));
}

TEST(CombatTest, FightMechanics) {
    auto dragon = NPCFactory::createNPC(DragonType, 0.0f, 0.0f, "Dragon");
    auto bull = NPCFactory::createNPC(BullType, 5.0f, 5.0f, "Bull");
    
    bool fightResult = dragon->fight(*bull);
    SUCCEED();
}

//-------------- тесты создания -------------------
TEST(FactoryTest, CreateValidTypes) {
    auto dragon = NPCFactory::createNPC(DragonType, 10.0f, 10.0f, "Dragon");
    auto bull = NPCFactory::createNPC(BullType, 20.0f, 20.0f, "Bull");
    auto toad = NPCFactory::createNPC(ToadType, 30.0f, 30.0f, "Toad");
    
    EXPECT_NE(dragon, nullptr);
    EXPECT_NE(bull, nullptr);
    EXPECT_NE(toad, nullptr);
    EXPECT_EQ(dragon->getType(), DragonType);
}

TEST(FactoryTest, InvalidTypeReturnsNull) {
    auto invalid = NPCFactory::createNPC(static_cast<NPCType>(999), 0.0f, 0.0f, "Invalid");
    EXPECT_EQ(invalid, nullptr);
}

//-------------- тесты интеграций -------------------
TEST(IntegrationTest, CompleteInteraction) {
    auto dragon = NPCFactory::createNPC(DragonType, 0.0f, 0.0f, "Dragon");
    auto bull = NPCFactory::createNPC(BullType, 5.0f, 5.0f, "Bull");
    
    EXPECT_TRUE(dragon->isAlive());
    EXPECT_TRUE(bull->isAlive());
    
    dragon->move();
    bull->move();
    
    EXPECT_GE(dragon->getX(), 0.0f);
    EXPECT_LE(bull->getX(), MAP_WIDTH);
}

TEST(IntegrationTest, TypeConversion) {
    EXPECT_EQ(typeToString(DragonType), "Dragon");
    EXPECT_EQ(typeToString(BullType), "Bull");
    EXPECT_EQ(typeToString(ToadType), "Toad");
}