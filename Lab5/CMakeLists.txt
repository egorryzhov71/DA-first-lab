cmake_minimum_required(VERSION 3.15)
project(DynamicArrayLab)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(GTest REQUIRED)


add_executable(main
    main.cpp
    include/dynamic_array.h
)

target_compile_features(main PRIVATE cxx_std_17)

add_executable(tests
    Tests.cpp
    include/dynamic_array.h
)

target_compile_features(tests PRIVATE cxx_std_17)


target_link_libraries(tests PRIVATE GTest::gtest GTest::gtest_main)

target_compile_options(main PRIVATE -Wall -Wextra -Wpedantic)
target_compile_options(tests PRIVATE -Wall -Wextra -Wpedantic)