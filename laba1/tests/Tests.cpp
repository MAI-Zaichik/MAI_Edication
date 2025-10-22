#include <gtest/gtest.h>
#include "../include/ToTurkish.h"

TEST(ToTurkishTest, ZeroToNine) {
    EXPECT_EQ(ToTurkish(0), "sifir");
    EXPECT_EQ(ToTurkish(1), "bir");
    EXPECT_EQ(ToTurkish(5), "beş");
    EXPECT_EQ(ToTurkish(9), "dokuz");
}

TEST(ToTurkishTest, Tens) {
    EXPECT_EQ(ToTurkish(10), "on");
    EXPECT_EQ(ToTurkish(20), "yirmi");
    EXPECT_EQ(ToTurkish(50), "elli");
    EXPECT_EQ(ToTurkish(90), "doksan");
}

TEST(ToTurkishTest, CompoundNumbers) {
    EXPECT_EQ(ToTurkish(11), "on bir");
    EXPECT_EQ(ToTurkish(25), "yirmi beş");
    EXPECT_EQ(ToTurkish(67), "altmiş yedi");
    EXPECT_EQ(ToTurkish(99), "doksan dokuz");
}

TEST(ToTurkishTest, EdgeCases) {
    EXPECT_EQ(ToTurkish(-1), "Error: number must be > 0 and < 100");
    EXPECT_EQ(ToTurkish(100), "Error: number must be > 0 and < 100");
    EXPECT_EQ(ToTurkish(999), "Error: number must be > 0 and < 100");
}

TEST(ToTurkishTest, BoundaryValues) {
    EXPECT_EQ(ToTurkish(0), "sifir");
    EXPECT_EQ(ToTurkish(9), "dokuz");
    EXPECT_EQ(ToTurkish(10), "on");
    EXPECT_EQ(ToTurkish(99), "doksan dokuz");
}