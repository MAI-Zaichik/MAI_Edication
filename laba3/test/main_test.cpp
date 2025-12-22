#include "../include/diamond.h"
#include "../include/figure.h"
#include "../include/figures.h"
#include "../include/pentagon.h"
#include "../include/point.h"
#include "../include/trapezoid.h"
#include <gtest/gtest.h>
#include <sstream>
#include <vector>

// ---------- Point ----------
TEST(PointTest, EqualityAndAccess) {
    Point p1(1.0, 2.0);
    Point p2(1.0, 2.0);
    Point p3(2.0, 3.0);

    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);

    EXPECT_DOUBLE_EQ(p1[0], 1.0);
    EXPECT_DOUBLE_EQ(p1[1], 2.0);
}

TEST(PointTest, IOTest) {
    std::stringstream ss("3 4");
    Point p;
    ss >> p;
    EXPECT_DOUBLE_EQ(p[0], 3.0);
    EXPECT_DOUBLE_EQ(p[1], 4.0);

    std::stringstream out;
    out << p;
    EXPECT_NE(out.str().find("3"), std::string::npos);
}

// ---------- Trapezoid ----------
TEST(TrapezoidTest, AreaAndCenter) {
    // Прямоугольная трапеция: (0,0), (4,0), (3,2), (1,2)
    Trapezoid t({{0, 0}, {4, 0}, {3, 2}, {1, 2}});
    double area = static_cast<double>(t);
    EXPECT_NEAR(area, 6.0, 1e-6); // (a+b)/2*h = (4+2)/2*2=6

    Point center = t.calcGeometricCenter();
    EXPECT_NEAR(center[0], 2.0, 1e-6);
    EXPECT_NEAR(center[1], 0.8888888, 1e-6);
}

TEST(TrapezoidTest, EqualityCopyMove) {
    Trapezoid t1({{0, 0}, {4, 0}, {3, 2}, {1, 2}});
    Trapezoid t2 = t1;
    EXPECT_TRUE(t1 == t2);

    Trapezoid t3 = std::move(t1);
    EXPECT_TRUE(t3 == t2);
}

// ---------- Diamond ----------
TEST(DiamondTest, EqualityAndArea) {
    // Ромб со стороной = 2 и углом 60°
    Diamond d1({{0, 0}, {1, 1.732}, {2, 0}, {1, -1.732}});
    Diamond d2 = d1;
    EXPECT_TRUE(d1 == d2);

    double area = static_cast<double>(d1);
    EXPECT_GT(area, 0.0);
}

// ---------- Pentagon ----------
TEST(PentagonTest, AreaCalculation) {
    // Правильный пятиугольник радиусом 1
    Pentagon p({{0, 1},
                {0.951, 0.309},
                {0.588, -0.809},
                {-0.588, -0.809},
                {-0.951, 0.309}});

    double area = static_cast<double>(p);
    EXPECT_GT(
        area,
        1.7); // площадь правильного пятиугольника со стороной ~1.175 ~1.72
}

TEST(PentagonTest, IOAndCopy) {
    Pentagon p1({{0, 0}, {1, 0}, {1, 1}, {0.5, 1.5}, {0, 1}});
    std::stringstream ss;
    ss << p1;
    EXPECT_NE(ss.str().find("("), std::string::npos);

    Pentagon p2 = p1;
    EXPECT_TRUE(p1 == p2);
}

// ---------- Figures array ----------
TEST(FiguresTest, AddPrintAndTotalArea) {
    Figures figures;
    Figure *t = new Trapezoid({{0, 0}, {4, 0}, {3, 2}, {1, 2}});
    Figure *p = new Pentagon({{0, 1},
                              {0.951, 0.309},
                              {0.588, -0.809},
                              {-0.588, -0.809},
                              {-0.951, 0.309}});

    // Добавляем вручную
    Figures f({t, p});
    EXPECT_EQ(f.getSize(), 2);

    double totalArea = f.calcTotalArea();
    EXPECT_GT(totalArea, 8.0);

    // Удаление по индексу
    f.deleteFigure(0);
    EXPECT_EQ(f.getSize(), 1);
}

// ---------- Streams ----------
TEST(IOTest, InputOutputFigure) {
    std::stringstream input("0 0 4 0 3 2 1 2");
    Trapezoid t;
    input >> t;
    std::stringstream output;
    output << t;
    EXPECT_NE(output.str().find("("), std::string::npos);
}

// -------------------- ВСПОМОГАТЕЛЬНОЕ --------------------
static double shoelace(const std::vector<Point>& pts) {
    // только для выпуклых/простых многоугольников с обходом по час/против час
    double s = 0.0;
    size_t n = pts.size();
    for (size_t i = 0; i < n; ++i) {
        const Point& a = pts[i];
        const Point& b = pts[(i+1)%n];
        s += a[0]*b[1] - a[1]*b[0];
    }
    return std::abs(s) * 0.5;
}

// -------------------- БАЗОВЫЕ СВЯЗКИ --------------------
TEST(FigureBaseTest, DoubleEqualsCalcArea) {
    Trapezoid t({{0,0},{4,0},{3,2},{1,2}});
    EXPECT_NEAR(static_cast<double>(t), t.calcArea(), 1e-9);

    Diamond d({{0,0},{2,2},{4,0},{2,-2}}); // ромб (квадрат, повернутый на 45°)
    EXPECT_NEAR(static_cast<double>(d), d.calcArea(), 1e-9);

    Pentagon p({{0,1},{0.951,0.309},{0.588,-0.809},{-0.588,-0.809},{-0.951,0.309}});
    EXPECT_NEAR(static_cast<double>(p), p.calcArea(), 1e-9);
}

TEST(FigureBaseTest, OstreamOstreamOperatorsWorkPolymorphically) {
    Trapezoid t({{0,0},{4,0},{3,2},{1,2}});
    Figure& base = t;

    std::stringstream out;
    out << base; // friend operator<<(ostream&, const Figure&)
    const auto s = out.str();
    // Минимальные инварианты: что-то напечаталось и есть скобки/цифры
    EXPECT_FALSE(s.empty());
    EXPECT_NE(s.find("("), std::string::npos);
    EXPECT_NE(s.find("0"), std::string::npos);
}

TEST(FigureBaseTest, IstreamOperatorDispatchesViaFigureRef) {
    // Проверяем, что >> на Figure& корректно вызывает виртуальное чтение производного
    std::stringstream in("0 0 4 0 3 2 1 2");
    Trapezoid t;
    Figure& base = t;
    in >> base;
    EXPECT_FALSE(in.fail());

    EXPECT_NEAR(static_cast<double>(t), 6.0, 1e-9);
}

// -------------------- POINT --------------------
TEST(PointMoreTest, IndexingMutatesAndReads) {
    Point p(1,2);
    p[0] = 10.5;
    p[1] = -3.25;
    EXPECT_DOUBLE_EQ(p[0], 10.5);
    EXPECT_DOUBLE_EQ(p[1], -3.25);
}

TEST(PointMoreTest, StreamInputRejectsBadData) {
    Point p;
    std::stringstream in("not_a_number 2");
    in >> p;
    EXPECT_TRUE(in.fail());
}

// -------------------- ПЛОЩАДИ ПРОСТЫЕ ФИГУРЫ --------------------
TEST(AreaTest, TrapezoidAsRectangle) {
    // прямоугольник 4x2 => 8
    Trapezoid t({{0,0},{4,0},{4,2},{0,2}});
    EXPECT_NEAR(static_cast<double>(t), 8.0, 1e-9);
}

TEST(AreaTest, DiamondAsSquareRotated) {
    // Квадрат со стороной 2*sqrt(2) => площадь 8
    Diamond d({{0,0},{2,2},{4,0},{2,-2}});
    EXPECT_NEAR(static_cast<double>(d), 8.0, 1e-9);
}

TEST(AreaTest, PentagonShoelaceConsistency) {
    std::vector<Point> pts = {
        {0,1},{0.951,0.309},{0.588,-0.809},{-0.588,-0.809},{-0.951,0.309}
    };
    Pentagon p({pts[0],pts[1],pts[2],pts[3],pts[4]});
    EXPECT_NEAR(static_cast<double>(p), shoelace(pts), 5e-3); // допуск: координаты округлены
}

// -------------------- ЦЕНТРЫ --------------------
TEST(CenterTest, RectangleCenter) {
    Trapezoid rect({{0,0},{4,0},{4,2},{0,2}});
    Point c = rect.calcGeometricCenter();
    EXPECT_NEAR(c[0], 2.0, 1e-9);
    EXPECT_NEAR(c[1], 1.0, 1e-9);
}

TEST(CenterTest, SymmetricDiamondCenterAtMidpoint) {
    Diamond d({{0,0},{2,2},{4,0},{2,-2}});
    Point c = d.calcGeometricCenter();
    EXPECT_NEAR(c[0], 2.0, 1e-6);
    EXPECT_NEAR(c[1], 0.0, 1e-6);
}

// -------------------- РАВЕНСТВО --------------------
TEST(EqualityTest, ReflexiveSymmetricTransitive) {
    Trapezoid a({{0,0},{4,0},{3,2},{1,2}});
    Trapezoid b = a;
    Trapezoid c = b;

    // Рефлексивность
    EXPECT_TRUE(a == a);
    // Симметричность
    EXPECT_TRUE(a == b);
    EXPECT_TRUE(b == a);
    // Транзитивность
    EXPECT_TRUE(b == c);
    EXPECT_TRUE(a == c);
}

TEST(EqualityTest, DifferentOrderShouldNotBeEqualIfOrderMatters) {
    Trapezoid t1({{0,0},{4,0},{4,2},{0,2}});
    Trapezoid t2({{4,0},{4,2},{0,2},{0,0}});
    EXPECT_FALSE(t1 == t2);
}

// -------------------- КОПИРОВАНИЕ/ПЕРЕМЕЩЕНИЕ ФИГУР --------------------
TEST(SpecialMembersTest, CopyMoveTrapezoid) {
    Trapezoid t1({{0,0},{4,0},{3,2},{1,2}});
    Trapezoid t2(t1);
    EXPECT_TRUE(t1 == t2);

    Trapezoid t3(std::move(t1));
    EXPECT_TRUE(t2 == t3);

    Trapezoid t4;
    t4 = t2;
    EXPECT_TRUE(t4 == t2);

    Trapezoid t5;
    t5 = std::move(t2);
    EXPECT_TRUE(t5 == t3);
}

// -------------------- STREAM IO ДЛЯ КАЖДОЙ ФИГУРЫ --------------------
TEST(StreamIOTest, TrapezoidReadWriteRoundTrip) {
    std::stringstream in("0 0 4 0 3 2 1 2");
    Trapezoid t;
    in >> t;
    ASSERT_FALSE(in.fail());

    std::stringstream out;
    out << t;
    EXPECT_FALSE(out.str().empty());
    EXPECT_NE(out.str().find("("), std::string::npos);
}

TEST(StreamIOTest, DiamondReadWriteRoundTrip) {
    std::stringstream in("0 0 2 2 4 0 2 -2");
    Diamond d;
    in >> d;
    ASSERT_FALSE(in.fail());

    std::stringstream out;
    out << d;
    EXPECT_FALSE(out.str().empty());
}

TEST(StreamIOTest, PentagonReadWriteRoundTrip) {
    std::stringstream in("0 1 0.951 0.309 0.588 -0.809 -0.588 -0.809 -0.951 0.309");
    Pentagon p;
    in >> p;
    ASSERT_FALSE(in.fail());

    std::stringstream out;
    out << p;
    EXPECT_FALSE(out.str().empty());
}

TEST(StreamIOTest, InputFailsOnTooFewNumbers) {
    std::stringstream in("0 0 4 0 3 2");
    Trapezoid t;
    in >> t;
    EXPECT_TRUE(in.fail());
}

// -------------------- CONTAINER Figures --------------------
TEST(FiguresContainerTest, ConstructFromInitListAndSizes) {
    auto* t = new Trapezoid({{0,0},{4,0},{3,2},{1,2}});
    auto* d = new Diamond({{0,0},{2,2},{4,0},{2,-2}});
    auto* p = new Pentagon({{0,1},{0.951,0.309},{0.588,-0.809},{-0.588,-0.809},{-0.951,0.309}});

    Figures f({t, d, p});
    EXPECT_EQ(f.getSize(), 3);
}

TEST(FiguresContainerTest, TotalAreaMatchesSum) {
    auto* t = new Trapezoid({{0,0},{4,0},{4,2},{0,2}});
    auto* d = new Diamond({{0,0},{2,2},{4,0},{2,-2}});
    Figures f({t, d});
    double sum = static_cast<double>(*t) + static_cast<double>(*d);
    EXPECT_NEAR(f.calcTotalArea(), sum, 1e-9);
}

TEST(FiguresContainerTest, DeleteByIndexHeadMiddleTail) {
    auto* t = new Trapezoid({{0,0},{4,0},{4,2},{0,2}});
    auto* d = new Diamond({{0,0},{2,2},{4,0},{2,-2}});
    auto* p = new Pentagon({{0,1},{0.951,0.309},{0.588,-0.809},{-0.588,-0.809},{-0.951,0.309}});

    Figures f({t, d, p});
    ASSERT_EQ(f.getSize(), 3);

    f.deleteFigure(0);
    EXPECT_EQ(f.getSize(), 2);

    f.deleteFigure(0);
    EXPECT_EQ(f.getSize(), 1);

    f.deleteFigure(0);
    EXPECT_EQ(f.getSize(), 0);
}

TEST(FiguresContainerTest, CopyAndMoveFiguresContainer) {
    auto* t = new Trapezoid({{0,0},{4,0},{3,2},{1,2}});
    auto* d = new Diamond({{0,0},{2,2},{4,0},{2,-2}});

    Figures f1({t, d});
    EXPECT_EQ(f1.getSize(), 2);

    Figures f2 = f1;
    EXPECT_EQ(f2.getSize(), 2);

    Figures f3 = std::move(f1);
    EXPECT_EQ(f3.getSize(), 2);
}

TEST(FiguresContainerTest, PrintHelpersDoNotCrashAndProduceOutput) {
    auto* t = new Trapezoid({{0,0},{4,0},{3,2},{1,2}});
    auto* d = new Diamond({{0,0},{2,2},{4,0},{2,-2}});

    Figures f({t, d});

    std::stringstream buf;
    auto* old = std::cout.rdbuf(buf.rdbuf());
    f.printCenterForEachFigure();
    f.printAreaForEachFigure();
    f.printCenterAndAreaForEachFigure();
    std::cout.rdbuf(old);

    EXPECT_FALSE(buf.str().empty());
}

// -------------------- ДОПОЛНИТЕЛЬНО: РЕАЛИСТИЧНЫЕ ПЛОЩАДИ --------------------
TEST(AreaRealisticTest, TrapezoidGeneralConsistencyWithShoelace) {
    std::vector<Point> pts = {{0,0},{4,0},{3,2},{1,2}};
    Trapezoid t({pts[0],pts[1],pts[2],pts[3]});
    EXPECT_NEAR(static_cast<double>(t), shoelace(pts), 1e-9);
}

TEST(AreaRealisticTest, DiamondConsistencyWithShoelace) {
    std::vector<Point> pts = {{0,0},{2,2},{4,0},{2,-2}};
    Diamond d({pts[0],pts[1],pts[2],pts[3]});
    EXPECT_NEAR(static_cast<double>(d), shoelace(pts), 1e-9);
}

TEST(AreaRealisticTest, PentagonConsistencyWithShoelace) {
    std::vector<Point> pts = {
        {0, 0}, {2, 0}, {3, 1}, {1.5, 2.5}, {-0.5, 1}
    };
    Pentagon p({pts[0],pts[1],pts[2],pts[3],pts[4]});
    EXPECT_NEAR(static_cast<double>(p), shoelace(pts), 1e-9);
}