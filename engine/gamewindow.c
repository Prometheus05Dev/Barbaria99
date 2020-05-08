#include "gamewindow.h"

int gameWindowShouldClose = 0;

float fov = 45.0f;

void setupGameWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    gameWindow = glfwCreateWindow(1920, 1080, "Barbaria", glfwGetPrimaryMonitor(), NULL);
    if(gameWindow == NULL) {
        printf("Creation of game window failed!");
        glfwTerminate();
    }
    glViewport(0, 0, 1920, 1080);
    glfwMakeContextCurrent(gameWindow);
    glfwSetCursorPosCallback(gameWindow, processMouse);
    glfwSetScrollCallback(gameWindow, scroll_callback);
    glfwSetInputMode(gameWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void updateGameWindow() {
    glfwSwapBuffers(gameWindow);
}

void processInput() {
    if(glfwGetKey(gameWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        gameWindowShouldClose = 1;
    if(glfwGetKey(gameWindow, GLFW_KEY_W) == GLFW_PRESS)
        moveForward();
    if(glfwGetKey(gameWindow, GLFW_KEY_S) == GLFW_PRESS)
        moveBackward();
    if(glfwGetKey(gameWindow, GLFW_KEY_A) == GLFW_PRESS)
        strafeLeft();
    if(glfwGetKey(gameWindow, GLFW_KEY_D) == GLFW_PRESS)
        strafeRight();
    if(glfwGetKey(gameWindow, GLFW_KEY_Q) == GLFW_PRESS)
        rotateLeft();
    if(glfwGetKey(gameWindow, GLFW_KEY_E) == GLFW_PRESS)
        rotateRight();
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    if(fov > 44.25f && fov < 45.3) {
        fov -= yoffset / 30.0f;
    }
    else if(fov <= 44.25f) {
        fov = 44.26f;
    }
    else if(fov >= 45.3f) {
        fov = 45.29f;
    }
    setFov(fov);
}

void setWindow3D() {
    glfwSetInputMode(gameWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void setWindow2D() {
    glfwSetInputMode(gameWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}