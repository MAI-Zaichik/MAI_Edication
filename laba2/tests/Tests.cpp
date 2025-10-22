#include <gtest/gtest.h>
#include <stdexcept>
#include "../include/interface.h"

using namespace std;

TEST(DecimalTest, Default) {
    Decimal num("123");
    EXPECT_EQ(num.toString(), "123");
    
    Decimal num2("0");
    EXPECT_EQ(num2.toString(), "0");
    
    Decimal num3("0000123");
    EXPECT_EQ(num3.toString(), "123");
}

TEST(DecimalTest, Valid) {
    EXPECT_THROW(Decimal("12a3"), invalid_argument);
    EXPECT_THROW(Decimal("12-3"), invalid_argument);
    EXPECT_THROW(Decimal(""), invalid_argument);
}

TEST(DecimalTest, Copy) {
    Decimal num1("456");
    Decimal num2(num1);
    EXPECT_EQ(num2.toString(), "456");
    EXPECT_TRUE(num1.eq(num2));
}


TEST(DecimalTest, Add) {
    Decimal num1("3500");
    Decimal num2("400");
    Decimal result = num1.add(num2);
    EXPECT_EQ(result.toString(), "3900");
}

TEST(DecimalTest, Add_Carry) {
    Decimal num1("9999");
    Decimal num2("1");
    Decimal result = num1.add(num2);
    EXPECT_EQ(result.toString(), "10000");
}

TEST(DecimalTest, Add_Zero) {
    Decimal num1("4543");
    Decimal num2("0");
    Decimal result = num1.add(num2);
    EXPECT_EQ(result.toString(), "4543");
}

TEST(DecimalTest, Add_Large) {
    Decimal num1("999999999");
    Decimal num2("1");
    Decimal result = num1.add(num2);
    EXPECT_EQ(result.toString(), "1000000000");
}


TEST(DecimalTest, Subtract) {
    Decimal num1("999");
    Decimal num2("333");
    Decimal result = num1.subtract(num2);
    EXPECT_EQ(result.toString(), "666");
}

TEST(DecimalTest, SubtractEqual) {
    Decimal num1("775");
    Decimal num2("775");
    Decimal result = num1.subtract(num2);
    EXPECT_EQ(result.toString(), "0");
}

TEST(DecimalTest, Subtract_Borrow) {
    Decimal num1("1000");
    Decimal num2("1");
    Decimal result = num1.subtract(num2);
    EXPECT_EQ(result.toString(), "999");
}

TEST(DecimalTest, Subtract_Invalid) {
    Decimal num1("69");
    Decimal num2("200");
    EXPECT_THROW(num1.subtract(num2), invalid_argument);
}


TEST(DecimalTest, Eq) {
    Decimal num1("111");
    Decimal num2("111");
    Decimal num3("222");
    
    EXPECT_TRUE(num1.eq(num2));
    EXPECT_FALSE(num1.eq(num3));
}

TEST(DecimalTest, Lt) {
    Decimal num1("111");
    Decimal num2("222");
    Decimal num3("100");
    Decimal num4("80");
    
    EXPECT_TRUE(num1.lt(num2));
    EXPECT_FALSE(num1.lt(num3));
    EXPECT_FALSE(num1.lt(num4));
}

TEST(DecimalTest, Gt) {
    Decimal num1("1000");
    Decimal num2("999");
    Decimal num3("1002");
    Decimal num4("5000");
    
    EXPECT_TRUE(num1.gt(num2));
    EXPECT_FALSE(num1.gt(num3));
    EXPECT_FALSE(num1.gt(num4));
}


TEST(DecimalTest, Size) {
    Decimal num1("4545");
    EXPECT_EQ(num1.size(), 4);
    
    Decimal num2("0");
    EXPECT_EQ(num2.size(), 1);
    
    Decimal num3("999999");
    EXPECT_EQ(num3.size(), 6);
}