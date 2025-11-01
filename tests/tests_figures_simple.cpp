#include <gtest/gtest.h>
#include "/workspaces/C++/include/TRS.h"
#include <sstream>

TEST(FigureTest, SquareAreaAndCenter) {
    Square sq(2, 3, 4);
    EXPECT_EQ(sq.area(), 16);
    auto center = sq.getCenter();
    EXPECT_EQ(center.first, 2);
    EXPECT_EQ(center.second, 3);
}

TEST(FigureTest, RectangleAreaAndCenter) {
    Rectangle rect(1, 2, 5, 6);
    EXPECT_EQ(rect.area(), 30);
    auto center = rect.getCenter();
    EXPECT_EQ(center.first, 1);
    EXPECT_EQ(center.second, 2);
}

TEST(FigureTest, TrapezoidAreaAndCenter) {
    Trapezoid trap(3, 4, 2, 6, 5);
    EXPECT_EQ(trap.area(), 20);
    auto center = trap.getCenter();
    EXPECT_EQ(center.first, 3);
    EXPECT_EQ(center.second, 4);
}

TEST(FigureTest, SquareComparison) {
    Square sq1(1, 1, 5);
    Square sq2(1, 1, 5);
    Square sq3(2, 2, 3);
    
    EXPECT_TRUE(sq1 == sq2);
    EXPECT_FALSE(sq1 == sq3);
}

TEST(FigureTest, RectangleComparison) {
    Rectangle rect1(0, 0, 4, 6);
    Rectangle rect2(0, 0, 4, 6);
    Rectangle rect3(0, 0, 5, 6);
    
    EXPECT_TRUE(rect1 == rect2);
    EXPECT_FALSE(rect1 == rect3);
}

TEST(FigureTest, DifferentTypesNotEqual) {
    Square sq(0, 0, 5);
    Rectangle rect(0, 0, 5, 5);
    
    EXPECT_FALSE(sq == rect);
}

TEST(FigureTest, SquareCopyAssignment) {
    Square sq1(1, 2, 5);
    Square sq2(10, 20, 10);
    
    sq2 = sq1;
    
    EXPECT_TRUE(sq1 == sq2);
    EXPECT_EQ(sq2.area(), 25);
}

TEST(FigureTest, RectangleCopyAssignment) {
    Rectangle rect1(1, 2, 4, 6);
    Rectangle rect2(10, 20, 8, 12);
    
    rect2 = rect1;
    
    EXPECT_TRUE(rect1 == rect2);
    EXPECT_EQ(rect2.area(), 24);
}

TEST(FigureTest, OutputOperator) {
    Square sq(0, 0, 4);
    std::ostringstream oss;
    oss << sq;
    
    std::string output = oss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_TRUE(output.find("Square") != std::string::npos);
}


TEST(FigureTest, ArrayOperations) {
    Array figures; 
    
    figures.push_back(new Square(0, 0, 2));
    figures.push_back(new Rectangle(0, 0, 3, 4));
    figures.push_back(new Trapezoid(0, 0, 2, 4, 3));
    
    EXPECT_EQ(figures.getSize(), 3); 
    
    double total = 0;
    for (int i = 0; i < figures.getSize(); i++) {
        total += figures[i]->area(); 
    }
    EXPECT_EQ(total, 25);
    
   
}

TEST(FigureTest, RemoveFromArray) {
    Array figures; 
    
    figures.push_back(new Square(0, 0, 2));
    figures.push_back(new Rectangle(0, 0, 3, 4));
    
    EXPECT_EQ(figures.getSize(), 2);
    
    figures.erase(0); 
    
    EXPECT_EQ(figures.getSize(), 1);
    EXPECT_EQ(figures[0]->area(), 12);
    
}

TEST(FigureTest, Polymorphism) {
    Array figures;
    
    figures.push_back(new Square(0, 0, 5));
    figures.push_back(new Rectangle(0, 0, 4, 6));
    
    EXPECT_EQ(figures[0]->area(), 25);
    EXPECT_EQ(figures[1]->area(), 24);
    

}

TEST(FigureTest, ArrayEmptyAndClear) {
    Array figures;
    
    EXPECT_TRUE(figures.empty()); 
    
    figures.push_back(new Square(0, 0, 2));
    EXPECT_FALSE(figures.empty());
    EXPECT_EQ(figures.getSize(), 1);
    

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}