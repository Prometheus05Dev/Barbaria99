#ifndef BARBARIA99_GAMEWINDOW_H
#define BARBARIA99_GAMEWINDOW_H

#include "../global_values.h"
#include <stdio.h>
#include "camera.h"
#include <GLFW/glfw3.h>
#include "../game.h"

extern int gameWindowShouldClose;

int mode;

float fov;

GLFWwindow *gameWindow;

void setupGameWindow();

void updateGameWindow();

void setWindow3D();

void setWindow2D();

void processInput();

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

#endif //BARBARIA99_GAMEWINDOW_H
