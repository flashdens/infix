Cmake_minimum_required(VERSION 3.21)
project(vitalyi C)

set(CMAKE_C_STANDARD 17)

add_executable(vitalyi main.c)
target_link_libraries(vitalyi -lmingw32 -lallegro-5.0.10-monolith-md-debug)
