#include <stdio.h>
#define STB_IMAGE_IMPLEMENTATION
#include "game/gameobject.h"
#include "game.h"
#include "global_values.h"

float deltaTime = 0.0f;
float lastFrame = 0.0f;
float currentFrame = 0.0f;

int main() {
    printf("Hello, World!\n");

    gameStart();

    int market = addGameObject(5.0f, 5.0f, 5.0f, "nils");
    int market2 = addGameObject(-5.0f, -5.0f, -5.0f, "stall");
    rotateObject(market, 180.0f, 0.0f, 1.0f, 0.0f);

    gameSet3D();
    gameBindShader(1);

    while(!gameWindowShouldClose){
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        gameResetGL();
        rotateAddObject(market, 1.0f, 1.0f, 0.0f, 0.0f);
        translateObject(market2, 0.01f, 0.01f, 0.01f);
        gameUpdate();
    }

    removeGameObject(market);
    removeGameObject(market2);
    gameFree();

    return 0;
}
