#ifndef BARBARIA99_CAMERA_H
#define BARBARIA99_CAMERA_H

#include <cglm/cglm.h>
#include "shader.h"

mat4 viewMatrix;

vec3 worldUp;

vec3 cameraPosition;
vec3 cameraFront;
vec3 cameraUp;
vec3 cameraRight;

float movementSpeed;

void initializeCamera();

void setupDefaultMatrices();

void updateCamera();

void moveForward();

void moveBackward();

void strafeLeft();

void strafeRight();

#endif //BARBARIA99_CAMERA_H
