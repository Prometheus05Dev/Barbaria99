#ifndef BARBARIA99_GAMEWINDOW_H
#define BARBARIA99_GAMEWINDOW_H

#include <stdio.h>
#include "camera.h"
#include <GLFW/glfw3.h>

extern int gameWindowShouldClose;

GLFWwindow *gameWindow;

void setupGameWindow();

void updateGameWindow();

void processInput();

void processMouse(float offSetX, float offSetY);

#endif //BARBARIA99_GAMEWINDOW_H
