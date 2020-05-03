#include "camera.h"

void initializeCamera() {
    cameraPosition[0] = 0.0f;
    cameraPosition[1] = 10.0f;
    cameraPosition[2] = 0.0f;
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
    mouseSensitivity = 0.1f;
    notFirstMouseMovement = 0.0f;
}

void updateCamera() {
        cameraFront[0] = cos(glm_rad(yaw)) * cos(glm_rad(pitch));
        cameraFront[1] = sin(glm_rad(pitch));
        cameraFront[2] = sin(glm_rad(yaw)) * cos(glm_rad(pitch));
        glm_vec3_normalize(cameraFront);
        glm_vec3_crossn(cameraFront, worldUp, cameraRight);
        glm_vec3_normalize(cameraRight);
        glm_vec3_crossn(cameraRight, cameraFront, cameraUp);
        glm_vec3_normalize(cameraUp);
        vec3 temp;
        glm_vec3_add(cameraPosition, cameraFront, temp);
        glm_lookat(cameraPosition, temp, cameraUp, viewMatrix);
        //TODO: getViewMatrix
        passMatrixToShader(viewMatrix, "viewMatrix");
        movementSpeed = 10.0f * deltaTime;
}

void moveForward() {
    cameraPosition[0] += cameraFront[0] * movementSpeed;
    cameraPosition[2] += cameraFront[2] * movementSpeed;
    updateCamera();
}

void moveBackward() {
    cameraPosition[0] -= cameraFront[0] * movementSpeed;
    cameraPosition[2] -= cameraFront[2] * movementSpeed;
    updateCamera();
}

void strafeLeft() {
    cameraPosition[0] -= cameraRight[0] * movementSpeed;
    cameraPosition[2] -= cameraRight[2] * movementSpeed;
    updateCamera();
}

void strafeRight() {
    cameraPosition[0] += cameraRight[0] * movementSpeed;
    cameraPosition[2] += cameraRight[2] * movementSpeed;
    updateCamera();
}

void processMouse(GLFWwindow* placeholder, double xpos, double ypos) {
   if(gameMode == 1) {
        if(!notFirstMouseMovement) {
            lastX = xpos;
            lastY = ypos;
            notFirstMouseMovement = 1;
        }
        xOffSet = xpos - lastX;
        yOffSet = lastY - ypos;
        lastX = xpos;
        lastY = ypos;
        xOffSet *= mouseSensitivity;
        yOffSet *= mouseSensitivity;
        yaw += xOffSet;
        pitch += yOffSet;
        if(pitch > 89.0f)
            pitch = 89.0f;
        if(pitch < -89.0f)
            pitch = -89.0f;
        updateCamera();
   }
   else if (gameMode == 0) {
        pitch = -45.0f;
        yaw = 0.0f;
        updateCamera();
   }
   else {
   printf("A fatal error occurred at line 96 of camera.c!\n");
   }
}
