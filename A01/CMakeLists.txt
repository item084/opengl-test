cmake_minimum_required(VERSION 3.14)
project(A01)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp shape.cpp shape.h)
add_executable(A01 ${SOURCE_FILES})
target_link_libraries(A01 opengl32 glu32 freeglut)