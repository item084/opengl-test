cmake_minimum_required(VERSION 3.14)
project(S01)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp shape.cpp shape.h map.cpp map.h)
add_executable(S01 ${SOURCE_FILES})
target_link_libraries(S01 opengl32 glu32 freeglut)