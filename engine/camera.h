#ifndef BARBARIA99_CAMERA_H
#define BARBARIA99_CAMERA_H

#include <cglm/cglm.h>
#include "shader.h"

vec3 cameraPosition;

vec3 cameraFront;

float movementSpeed;

void initializeCamera();

void setupDefaultMatrices();

void moveForward();

void moveBackward();

void strafeLeft();

void strafeRight();

#endif //BARBARIA99_CAMERA_H
