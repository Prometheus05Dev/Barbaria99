#include "camera.h"

void initializeCamera() {
    cameraPosition[0] = 0.0f;
    cameraPosition[1] = 0.0f;
    cameraPosition[2] = 3.0f;
    cameraFront[0] = 0.0f;
    cameraFront[1] = 0.0f;
    cameraFront[2] = -1.0f;
    movementSpeed = 0.05f;
}

void setupDefaultMatrices() {
    mat4 projectionMatrix;
    glm_perspective(45.0f, 1920.0f / 1080.0f, 0.1f, 100.0f, projectionMatrix);
    passMatrixToShader(projectionMatrix);
}

void moveForward() {
    glm_vec3_scale(cameraFront, movementSpeed, cameraFront);
    glm_vec3_add(cameraPosition, cameraFront, cameraPosition);
}

void moveBackward() {

}

void strafeLeft() {

}

void strafeRight() {

}