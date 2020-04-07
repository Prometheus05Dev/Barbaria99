#include <stdio.h>
#include "engine/object.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef enum { false, true } bool;

bool shouldClose = false;

//TODO: Object GL data construction
//TODO: GameWindow implementation
//TODO: Shader implementation

int main() {
    printf("Hello, World!\n");

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *mainWindow = glfwCreateWindow(1920, 1080, "Barbaria",glfwGetPrimaryMonitor(), NULL);
    if(mainWindow == NULL) {
        printf("Creation of game window failed!");
        glfwTerminate();
    }
    glViewport(0, 0, 1920, 1080);
    glfwMakeContextCurrent(mainWindow);
    #ifdef _RUNTIME
    glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    #endif

    glewExperimental = GL_TRUE;
    glewInit();

    getConfigPath();
    loadObjects();
    while(!shouldClose){
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(mainWindow);
        glfwPollEvents();
    }
    freeObjects();
    return 0;
}
