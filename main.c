#include <stdio.h>
#define STB_IMAGE_IMPLEMENTATION
#include "engine/object.h"
#include "engine/shader.h"
#include "engine/camera.h"
#include "engine/gamewindow.h"
#include "global_values.h"
#include <GLFW/glfw3.h>
#include "game/gameobject.h"

float deltaTime = 0.0f;
float lastFrame = 0.0f;
float currentFrame = 0.0f;

int main() {
    printf("Hello, World!\n");

    setupGameWindow();

    glewExperimental = GL_TRUE;
    glewInit();

    genConfigPath();
    readShaderDir();
    loadObjects();
    bindShader(1);
    initializeCamera();
    setupDefaultMatrices();

    glEnable(GL_DEPTH_TEST);

    int market = addGameObject(5.0f, 5.0f, 5.0f, "stall");
    int market2 = addGameObject(-5.0f, -5.0f, -5.0f, "stall");
    rotateObject(market, 180.0f, 0.0f, 1.0f, 0.0f);

    while(!gameWindowShouldClose){
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        bindShader(1);
        rotateAddObject(market, 1.0f, 1.0f, 0.0f, 0.0f);
        translateObject(market2, 0.01f, 0.01f, 0.01f);
        updateGameObjects();
        updateGameWindow();
        glfwPollEvents();
        processInput();
    }

    removeGameObject(market);
    removeGameObject(market2);
    freeObjects();
    freePGL();
    freeShaders();

    return 0;
}
