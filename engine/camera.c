#include "camera.h"

void initializeCamera() {
    cameraPosition[0] = 0.0f;
    cameraPosition[1] = 0.0f;
    cameraPosition[2] = 3.0f;
    cameraFront[0] = 0.0f;
    cameraFront[1] = 0.0f;
    cameraFront[2] = -1.0f;
    cameraUp[0] = 0.0f;
    cameraUp[1] = 1.0f;
    cameraUp[2] = 0.0f;
    worldUp[0] = 0.0f;
    worldUp[1] = 1.0f;
    worldUp[2] = 0.0f;
    movementSpeed = 0.05f;
}

void setupDefaultMatrices() {
    mat4 projectionMatrix;
    glm_perspective(45.0f, 1920.0f / 1080.0f, 0.1f, 100.0f, projectionMatrix);
    passMatrixToShader(projectionMatrix, "projectionMatrix");
    updateCamera();
}

void updateCamera() {
    glm_vec3_normalize(cameraFront);
    glm_vec3_crossn(cameraFront, worldUp, cameraRight);
    glm_vec3_crossn(cameraRight, cameraFront, cameraUp);
    vec3 temp;
    glm_vec3_add(cameraPosition, cameraFront, temp);
    glm_lookat(cameraPosition, temp, cameraUp, viewMatrix);
    passMatrixToShader(viewMatrix, "viewMatrix");
}

void moveForward() {
    glm_vec3_scale(cameraFront, movementSpeed, cameraFront);
    glm_vec3_add(cameraPosition, cameraFront, cameraPosition);
    updateCamera();
}

void moveBackward() {
    glm_vec3_scale(cameraFront, movementSpeed, cameraFront);
    glm_vec3_sub(cameraPosition, cameraFront, cameraPosition);
    updateCamera();
}

void strafeLeft() {

}

void strafeRight() {

}
