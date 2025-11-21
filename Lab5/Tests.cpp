#include <gtest/gtest.h>
#include "/workspaces/C++/Lab5/include/dynamic_array.h"
#include <string>

TEST(MemoryResourceTest, BasicAllocationDeallocation) {
    MemoryResource mr;
    
    void* ptr = mr.allocate(100, 1);
    EXPECT_NE(ptr, nullptr);
    
    mr.deallocate(ptr, 100, 1);
}

TEST(MemoryResourceTest, MultipleAllocations) {
    MemoryResource mr;
    
    void* ptr1 = mr.allocate(50, 1);
    void* ptr2 = mr.allocate(100, 1);
    void* ptr3 = mr.allocate(25, 1);
    
    EXPECT_NE(ptr1, nullptr);
    EXPECT_NE(ptr2, nullptr);
    EXPECT_NE(ptr3, nullptr);
    EXPECT_NE(ptr1, ptr2);
    EXPECT_NE(ptr2, ptr3);
    
    mr.deallocate(ptr1, 50, 1);
    mr.deallocate(ptr2, 100, 1);
    mr.deallocate(ptr3, 25, 1);
}

TEST(DynamicArrayTest, ConstructorAndBasicOperations) {
    MemoryResource mr;
    std::pmr::polymorphic_allocator<int> alloc(&mr);
    
    DynamicArray<int> arr(5, alloc);
    EXPECT_EQ(arr.size(), 0);
    EXPECT_EQ(arr.capacity(), 5);
}

TEST(DynamicArrayTest, PushBackAndAccess) {
    MemoryResource mr;
    std::pmr::polymorphic_allocator<int> alloc(&mr);
    
    DynamicArray<int> arr(2, alloc);
    
    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(30); 
    
    EXPECT_EQ(arr.size(), 3);
    EXPECT_GE(arr.capacity(), 3);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
}


TEST(DynamicArrayTest, ComplexTypeSupport) {
    MemoryResource mr;
    std::pmr::polymorphic_allocator<std::string> alloc(&mr);
    
    DynamicArray<std::string> arr(2, alloc);
    
    arr.push_back("Hello");
    arr.push_back("World");
    arr.push_back("Test");
    
    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[0], "Hello");
    EXPECT_EQ(arr[1], "World");
    EXPECT_EQ(arr[2], "Test");
}

TEST(DynamicArrayTest, CustomStruct) {
    struct Point {
        int x, y;
        Point(int x = 0, int y = 0) : x(x), y(y) {}
    };
    
    MemoryResource mr;
    std::pmr::polymorphic_allocator<Point> alloc(&mr);
    
    DynamicArray<Point> arr(2, alloc);
    
    arr.push_back(Point(1, 2));
    arr.push_back(Point(3, 4));
    arr.push_back(Point(5, 6));
    
    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[0].x, 1);
    EXPECT_EQ(arr[0].y, 2);
    EXPECT_EQ(arr[1].x, 3);
    EXPECT_EQ(arr[1].y, 4);
}

TEST(DynamicArrayTest, OutOfRangeAccess) {
    MemoryResource mr;
    std::pmr::polymorphic_allocator<int> alloc(&mr);
    
    DynamicArray<int> arr(3, alloc);
    arr.push_back(1);
    
    EXPECT_NO_THROW(arr[0]);
    EXPECT_THROW(arr[1], std::out_of_range);
    EXPECT_THROW(arr[100], std::out_of_range);
}

TEST(DynamicArrayTest, IteratorOutOfRange) {
    MemoryResource mr;
    std::pmr::polymorphic_allocator<int> alloc(&mr);
    
    DynamicArray<int> arr(2, alloc);
    arr.push_back(1);
    
    auto it = arr.begin();
    EXPECT_NO_THROW(*it);
    
    ++it; 
    EXPECT_THROW(*it, std::out_of_range);
}

TEST(DynamicArrayTest, MemoryReuse) {
    MemoryResource mr;
    std::pmr::polymorphic_allocator<int> alloc(&mr);
    

    {
        DynamicArray<int> arr1(10, alloc);
        arr1.push_back(1);
        arr1.push_back(2);
    } 
    
    {
        DynamicArray<int> arr2(5, alloc);
        arr2.push_back(3);
        arr2.push_back(4);
    } 

    DynamicArray<int> arr3(3, alloc);
    arr3.push_back(5);
    
    EXPECT_EQ(arr3.size(), 1);
    EXPECT_EQ(arr3[0], 5);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}