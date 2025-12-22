#include <gtest/gtest.h>
#include "../include/rhombus.h"
#include "../include/pentagon.h"
#include "../include/hexagon.h"

//-------------Вычисления площадей-------------
TEST(FigureTest, RhombusArea) {
    Rhombus<double> r(Point<double>(0,0), 4, 6);
    EXPECT_NEAR(r.area(), 12.0, 1e-9);
}

TEST(FigureTest, RhombusAreaZeroDiagonals) {
    Rhombus<double> r(Point<double>(0,0), 0, 0);
    EXPECT_NEAR(r.area(), 0.0, 1e-9);
}

TEST(FigureTest, RhombusAreaLargeValues) {
    Rhombus<double> r(Point<double>(0,0), 100.5, 75.3);
    EXPECT_GT(r.area(), 0.0);
}

TEST(FigureTest, PentagonAreaZeroRadius) {
    Pentagon<double> p(Point<double>(0,0), 0.0);
    EXPECT_NEAR(p.area(), 0.0, 1e-9);
}

TEST(FigureTest, PentagonAreaLargeRadius) {
    Pentagon<double> p(Point<double>(0,0), 10.0);
    EXPECT_GT(p.area(), 100.0);
}

TEST(FigureTest, HexagonArea) {
    Hexagon<double> h(Point<double>(0,0), 1.0);
    EXPECT_NEAR(h.area(), 2.5980762114, 1e-9);
}

TEST(FigureTest, HexagonAreaZeroRadius) {
    Hexagon<double> h(Point<double>(0,0), 0.0);
    EXPECT_NEAR(h.area(), 0.0, 1e-9);
}

TEST(FigureTest, HexagonAreaLargeRadius) {
    Hexagon<double> h(Point<double>(0,0), 5.0);
    EXPECT_GT(h.area(), 50.0);
}

//-----------Вычисление геометрического центра--------------
TEST(FigureTest, RhombusCenter) {
    Rhombus<double> r(Point<double>(2,3), 4, 6);
    Point<double> center = r.center();
    EXPECT_NEAR(center.x(), 2.0, 1e-9);
    EXPECT_NEAR(center.y(), 3.0, 1e-9);
}

TEST(FigureTest, RhombusCenterNegativeCoordinates) {
    Rhombus<double> r(Point<double>(-2,-3), 4, 6);
    Point<double> center = r.center();
    EXPECT_NEAR(center.x(), -2.0, 1e-9);
    EXPECT_NEAR(center.y(), -3.0, 1e-9);
}

TEST(FigureTest, PentagonCenter) {
    Pentagon<double> p(Point<double>(1,2), 1.0);
    Point<double> center = p.center();
    EXPECT_NEAR(center.x(), 1.0, 1e-9);
    EXPECT_NEAR(center.y(), 2.0, 1e-9);
}

TEST(FigureTest, PentagonCenterLargeValues) {
    Pentagon<double> p(Point<double>(100,200), 50.0);
    Point<double> center = p.center();
    EXPECT_NEAR(center.x(), 100.0, 1e-9);
    EXPECT_NEAR(center.y(), 200.0, 1e-9);
}

TEST(FigureTest, HexagonCenter) {
    Hexagon<double> h(Point<double>(-1,2), 1.5);
    Point<double> center = h.center();
    EXPECT_NEAR(center.x(), -1.0, 1e-9);
    EXPECT_NEAR(center.y(), 2.0, 1e-9);
}

TEST(FigureTest, HexagonCenterAtOrigin) {
    Hexagon<double> h(Point<double>(0,0), 2.0);
    Point<double> center = h.center();
    EXPECT_NEAR(center.x(), 0.0, 1e-9);
    EXPECT_NEAR(center.y(), 0.0, 1e-9);
}

//------------Тесты операторов-----------------------
TEST(FigureTest, OperatorDouble) {
    Rhombus<double> r(Point<double>(0,0), 4, 6);
    EXPECT_NEAR(static_cast<double>(r), 12.0, 1e-9);
}

TEST(FigureTest, OperatorDoublePentagon) {
    Pentagon<double> p(Point<double>(0,0), 1.0);
    double area = static_cast<double>(p);
    EXPECT_GT(area, 0.0);
}

TEST(FigureTest, OperatorDoubleHexagon) {
    Hexagon<double> h(Point<double>(0,0), 1.0);
    double area = static_cast<double>(h);
    EXPECT_GT(area, 0.0);
}

TEST(FigureTest, EqualitySameRhombus) {
    Rhombus<double> r1(Point<double>(0,0), 4, 6);
    Rhombus<double> r2(Point<double>(0,0), 4, 6);
    EXPECT_TRUE(r1.equals(r2));
}

TEST(FigureTest, EqualitySamePentagon) {
    Pentagon<double> p1(Point<double>(1,2), 3.0);
    Pentagon<double> p2(Point<double>(1,2), 3.0);
    EXPECT_TRUE(p1.equals(p2));
}

TEST(FigureTest, EqualitySameHexagon) {
    Hexagon<double> h1(Point<double>(-1,2), 1.5);
    Hexagon<double> h2(Point<double>(-1,2), 1.5);
    EXPECT_TRUE(h1.equals(h2));
}

TEST(FigureTest, DifferentTypes) {
    Rhombus<double> r(Point<double>(0,0), 4, 6);
    Pentagon<double> p(Point<double>(0,0), 1.0);
    EXPECT_FALSE(r.equals(p));
}

TEST(FigureTest, DifferentTypesHexagonRhombus) {
    Hexagon<double> h(Point<double>(0,0), 1.0);
    Rhombus<double> r(Point<double>(0,0), 4, 6);
    EXPECT_FALSE(h.equals(r));
}

TEST(FigureTest, DifferentPentagonSizes) {
    Pentagon<double> p1(Point<double>(0,0), 1.0);
    Pentagon<double> p2(Point<double>(0,0), 2.0);
    EXPECT_TRUE(p1.equals(p2)); // Метод equals сравнивает только количество точек
}


//К-------------Конструкторы и создание фигур---------------
TEST(FigureTest, DefaultConstructors) {
    Rhombus<double> r;
    Pentagon<double> p;
    Hexagon<double> h;
    
    EXPECT_GT(r.area(), 0);
    EXPECT_GT(p.area(), 0);
    EXPECT_GT(h.area(), 0);
}

TEST(FigureTest, ParameterizedConstructors) {
    Rhombus<double> r(Point<double>(5,5), 10, 8);
    Pentagon<double> p(Point<double>(-3,4), 2.5);
    Hexagon<double> h(Point<double>(0,-2), 3.0);
    
    EXPECT_NEAR(r.center().x(), 5.0, 1e-9);
    EXPECT_NEAR(p.center().x(), -3.0, 1e-9);
    EXPECT_NEAR(h.center().y(), -2.0, 1e-9);
}

//--------------------Ввод-вывод---------------------
TEST(FigureTest, PrintRhombus) {
    Rhombus<double> r(Point<double>(1,2), 4, 6);
    testing::internal::CaptureStdout();
    r.print(std::cout);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Rhombus:") != std::string::npos);
}

TEST(FigureTest, PrintPentagon) {
    Pentagon<double> p(Point<double>(0,0), 1.0);
    testing::internal::CaptureStdout();
    p.print(std::cout);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Pentagon:") != std::string::npos);
}

TEST(FigureTest, PrintHexagon) {
    Hexagon<double> h(Point<double>(0,0), 1.0);
    testing::internal::CaptureStdout();
    h.print(std::cout);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Hexagon:") != std::string::npos);
}
