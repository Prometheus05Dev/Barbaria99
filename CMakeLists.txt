cmake_minimum_required(VERSION 3.17)
project(Barbaria99 C)

set(CMAKE_C_STANDARD 99)

include_directories(libs)

add_compile_options("-lGL -lGLEW -lglfw -ldl -lX11 -lpthread -lXrandr -lXi")
link_libraries("-lGL -lGLEW -lglfw -ldl -lX11 -lpthread -lXrandr -lXi")

add_executable(Barbaria99 main.c engine/object.c game/gameobject.c libs/elboronlib.c)