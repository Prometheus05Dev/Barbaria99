#ifndef BARBARIA99_GAMEWINDOW_H
#define BARBARIA99_GAMEWINDOW_H

#include "../global_values.h"
#include <stdio.h>
#include "camera.h"
#include <GLFW/glfw3.h>

extern int gameWindowShouldClose;

GLFWwindow *gameWindow;

void setupGameWindow();

void updateGameWindow();

void setWindow3D();

void setWindow2D();

void processInput();

#endif //BARBARIA99_GAMEWINDOW_H
