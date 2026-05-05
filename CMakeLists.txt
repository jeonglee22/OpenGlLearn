cmake_minimum_required(VERSION 3.20)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(LearnOpenGL
    src/main.cpp
    add_src/glad.c
)

target_link_libraries(LearnOpenGL
    ${CMAKE_SOURCE_DIR}/lib/libglfw3.a
    opengl32
    gdi32
    user32
)