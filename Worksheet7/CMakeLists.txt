# CMakeLists.txt (fragment of)
cmake_minimum_required(VERSION 2.8.0)
project(MathsLib)
include(CTest)
# ...
# description of executables and libraries
# ...
add_library (maths adder.cpp)
add_executable(test1 test1.cpp)
target_link_libraries(test1 maths)
add_test(test1 test1)
