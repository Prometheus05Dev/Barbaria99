#include "game.h"

void gameStart() {
    setupGameWindow();
    glewExperimental = GL_TRUE;
    glewInit();
    genConfigPath();
    readShaderDir();
    loadObjects();
    bindShader(1);
    initializeCamera();
    glEnable(GL_DEPTH_TEST);
}

void gameSet2D() {
    setShader2D();
}

void gameSet3D() {
    setShader3D();
}

void gameBindShader(int id) {
    bindShader(id);
}

void gameUpdate() {
    updateGameObjects();
    updateGameWindow();
    glfwPollEvents();
    processInput();
}

void gameFree() {
    freeObjects();
    freePGL();
    freeShaders();
}

void gameResetGL() {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
