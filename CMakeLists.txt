cmake_minimum_required(VERSION 3.26)
project(infix C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(infix
        funkcjeallegrowe.h
        funkcjegrowe.h
        main.c)

target_include_directories(infix PUBLIC ${allegro-5_INCLUDE_DIRS})
target_link_libraries(infix PUBLIC allegro allegro_ttf allegro_image allegro_audio allegro_acodec allegro_font)