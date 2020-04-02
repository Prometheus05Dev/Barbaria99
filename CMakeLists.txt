cmake_minimum_required(VERSION 3.17)
project(Barbaria99 C)

set(CMAKE_C_STANDARD 99)

include_directories(libs)

add_executable(Barbaria99 main.c engine/object.c game/gameobject.c game/gameobject.h libs/elboronlib.c libs/elboronlib.h)