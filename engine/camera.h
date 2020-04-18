#ifndef BARBARIA99_CAMERA_H
#define BARBARIA99_CAMERA_H

#include <cglm/cglm.h>
#include "shader.h"
#include <GLFW/glfw3.h>
#include "../global_values.h"

mat4 viewMatrix;

vec3 worldUp;
vec3 cameraPosition;
vec3 cameraFront;
vec3 cameraUp;
vec3 cameraRight;

float yaw;
float pitch;
float movementSpeed;
float mouseSensitivity;
float lastX;
float lastY;
float xOffSet;
float yOffSet;

int notFirstMouseMovement;

void initializeCamera();

void setupDefaultMatrices();

void updateCamera();

void moveForward();

void moveBackward();

void strafeLeft();

void strafeRight();

void processMouse(GLFWwindow* placeholder, double xpos, double ypos);

#endif //BARBARIA99_CAMERA_H
