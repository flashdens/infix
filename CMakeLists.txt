Cmake_minimum_required(VERSION 3.21)
project(infix C)

set(CMAKE_C_STANDARD 17)

add_executable(infix main.c)
target_link_libraries(infix -lmingw32 -lallegro-5.0.10-monolith-md-debug)
