#include "../include/entities.hpp"
#include "../include/factory.hpp"
#include "../include/fight.hpp"
#include "../include/npc.hpp"
#include "../include/observer.hpp"
#include <gtest/gtest.h>
#include <memory>

// Тесты для проверки логики убийств
TEST(NPCTest, DragonCanKill) {
    auto dragon = NPCFactory::createNPC(DragonType, 0, 0, "Dragon");
    auto bull = NPCFactory::createNPC(BullType, 0, 0, "Bull");
    auto toad = NPCFactory::createNPC(ToadType, 0, 0, "Toad");
    auto anotherDragon = NPCFactory::createNPC(DragonType, 0, 0, "Dragon2");

    EXPECT_TRUE(dragon->canKill(*bull));     // Дракон убивает быка
    EXPECT_FALSE(dragon->canKill(*toad));    // Дракон НЕ убивает жабу
    EXPECT_FALSE(dragon->canKill(*anotherDragon)); // Дракон НЕ убивает дракона
}

TEST(NPCTest, BullCanKill) {
    auto bull = NPCFactory::createNPC(BullType, 0, 0, "Bull");
    auto dragon = NPCFactory::createNPC(DragonType, 0, 0, "Dragon");
    auto toad = NPCFactory::createNPC(ToadType, 0, 0, "Toad");
    auto anotherBull = NPCFactory::createNPC(BullType, 0, 0, "Bull2");

    EXPECT_TRUE(bull->canKill(*toad));       // Бык убивает жабу
    EXPECT_FALSE(bull->canKill(*dragon));    // Бык НЕ убивает дракона
    EXPECT_FALSE(bull->canKill(*anotherBull)); // Бык НЕ убивает быка
}

TEST(NPCTest, ToadCanKill) {
    auto toad = NPCFactory::createNPC(ToadType, 0, 0, "Toad");
    auto dragon = NPCFactory::createNPC(DragonType, 0, 0, "Dragon");
    auto bull = NPCFactory::createNPC(BullType, 0, 0, "Bull");
    auto anotherToad = NPCFactory::createNPC(ToadType, 0, 0, "Toad2");

    // Жаба никого не убивает
    EXPECT_FALSE(toad->canKill(*dragon));
    EXPECT_FALSE(toad->canKill(*bull));
    EXPECT_FALSE(toad->canKill(*anotherToad));
}

// Тесты для боевой системы
TEST(FightTest, DragonKillsBullInRange) {
    auto dragon = NPCFactory::createNPC(DragonType, 0, 0, "Dragon");
    auto bull = NPCFactory::createNPC(BullType, 10, 0, "Bull");

    // Создаем наблюдателей
    auto consoleObs = std::make_shared<ConsoleObserver>();
    auto fileObs = std::make_shared<TextObserver>();
    dragon->attach(consoleObs);
    dragon->attach(fileObs);
    bull->attach(consoleObs);
    bull->attach(fileObs);

    FightVisitor visitor(dragon, 15.0f); // Дистанция 10, диапазон 15
    visitor.visit(bull);

    EXPECT_FALSE(bull->isAlive());
    EXPECT_TRUE(dragon->isAlive()); 
}

TEST(FightTest, BullKillsToadInRange) {
    auto bull = NPCFactory::createNPC(BullType, 0, 0, "Bull");
    auto toad = NPCFactory::createNPC(ToadType, 5, 5, "Toad");

    auto consoleObs = std::make_shared<ConsoleObserver>();
    auto fileObs = std::make_shared<TextObserver>();
    bull->attach(consoleObs);
    bull->attach(fileObs);
    toad->attach(consoleObs);
    toad->attach(fileObs);

    FightVisitor visitor(bull, 10.0f);
    visitor.visit(toad);

    EXPECT_FALSE(toad->isAlive());
    EXPECT_TRUE(bull->isAlive());
}

TEST(FightTest, NoKillOutOfRange) {
    auto dragon = NPCFactory::createNPC(DragonType, 0, 0, "Dragon");
    auto bull = NPCFactory::createNPC(BullType, 100, 100, "Bull");

    auto observer = std::make_shared<ConsoleObserver>();
    dragon->attach(observer);
    bull->attach(observer);

    FightVisitor visitor(dragon, 15.0f);
    visitor.visit(bull);

    EXPECT_TRUE(bull->isAlive()); // Слишком далеко
    EXPECT_TRUE(dragon->isAlive());
}

TEST(FightTest, ToadCannotKillAnyone) {
    auto toad = NPCFactory::createNPC(ToadType, 0, 0, "Toad");
    auto bull = NPCFactory::createNPC(BullType, 5, 5, "Bull");

    auto observer = std::make_shared<ConsoleObserver>();
    toad->attach(observer);
    bull->attach(observer);

    FightVisitor visitor(toad, 10.0f);
    visitor.visit(bull);

    EXPECT_TRUE(bull->isAlive()); // Жаба не может убить быка
    EXPECT_TRUE(toad->isAlive());
}

TEST(FightTest, DeadNPCsCannotFight) {
    auto dragon = NPCFactory::createNPC(DragonType, 0, 0, "Dragon");
    auto bull = NPCFactory::createNPC(BullType, 10, 10, "Bull");

    // Убиваем дракона
    dragon->kill();

    FightVisitor visitor(dragon, 20.0f);
    visitor.visit(bull);

    EXPECT_TRUE(bull->isAlive()); // Мертвый дракон не может атаковать
}

TEST(FightTest, TwoWayFight) {
    // Тест на двусторонний бой
    auto dragon = NPCFactory::createNPC(DragonType, 0, 0, "Dragon");
    auto bull = NPCFactory::createNPC(BullType, 5, 5, "Bull");
    
    // Дракон может убить быка, но бык НЕ может убить дракона
    EXPECT_TRUE(dragon->canKill(*bull));
    EXPECT_FALSE(bull->canKill(*dragon));
    
    // Проверяем расстояние
    float dx = dragon->getX() - bull->getX();
    float dy = dragon->getY() - bull->getY();
    float dist = std::sqrt(dx*dx + dy*dy);
    EXPECT_LE(dist, 10.0f); // ~7.07
    
    // Дракон атакует быка
    FightVisitor visitor1(dragon, 10.0f);
    visitor1.visit(bull);
    
    EXPECT_FALSE(bull->isAlive());
    EXPECT_TRUE(dragon->isAlive());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}