#ifndef BARBARIA99_GAMEWINDOW_H
#define BARBARIA99_GAMEWINDOW_H

#include <GLFW/glfw3.h>
#include <stdio.h>

extern int gameWindowShouldClose;

GLFWwindow *gameWindow;

void setupGameWindow();

void updateGameWindow();

void processInput();

#endif //BARBARIA99_GAMEWINDOW_H
