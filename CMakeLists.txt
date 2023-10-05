cmake_minimum_required(VERSION 3.26)
project(infix C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(infix
        src/main.c
        include/utils.h
        include/infix.h
        src/infix.c
        src/utils.c
)

target_include_directories(infix PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(infix PUBLIC allegro allegro_ttf allegro_image allegro_audio allegro_acodec allegro_font)