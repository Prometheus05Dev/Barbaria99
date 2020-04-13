#include <stdio.h>
#include "engine/object.h"
#include "engine/shader.h"
#include <GLFW/glfw3.h>

typedef enum { false, true } bool;

//TODO: Object GL data construction
//TODO: Shader implementation

int main() {
    struct Vertex testVertices[3] = {
            {-0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f}
    };
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

    struct Vertex test1 = {};

    getConfigPath();
    readShaderDir();
    bindShader(1);

    unsigned int VAO;
    unsigned int VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(struct Vertex), &testVertices[0], GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (void*)offsetof(struct Vertex, normalX));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (void*)offsetof(struct Vertex, textureX));
    glEnableVertexAttribArray(2);

    while(!glfwWindowShouldClose(mainWindow)){
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(mainWindow);
        bindShader(1);
        glfwPollEvents();
        if(glfwGetKey(mainWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(mainWindow, true);
    }

    freeObjects();
    freePGL();
    freeShaders();

    return 0;
}
