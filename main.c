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
    getConfigPath();
    loadObjects();
    while(!shouldClose){
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    freeObjects();
    return 0;
}
