#include "gamewindow.h"

int gameWindowShouldClose = 0;

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
#ifdef _RUNTIME
    glfwSetInputMode(gameWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
#endif
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
}