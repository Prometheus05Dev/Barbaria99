#include "camera.h"

void setupDefaultMatrices() {
    mat4 projectionMatrix;
    glm_perspective(45.0f, 1920.0f / 1080.0f, 0.1f, 100.0f, projectionMatrix);
    passMatrixToShader(projectionMatrix);
}
