#include <stdio.h>
#define STB_IMAGE_IMPLEMENTATION
#include "global_values.h"
#include "game/gameobject.h"
#include "game.h"

float deltaTime = 0.0f;
float lastFrame = 0.0f;
float currentFrame = 0.0f;

int gameMode = 0.0f;

int main() {
    printf("Hello, World!\n");

    gameStart();

    int market = addGameObject(0.0f, 0.0f, 0.0f, "nils");
    int city = addGameObject(10.0f, 0.01f, -5.0f, "city");
    //int market2 = addGameObject(-5.0f, -5.0f, -5.0f, "stall");

    gameSet2D();

    while(!gameWindowShouldClose){
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        gameResetGL();
        //rotateAddObject(market, 1.0f, 1.0f, 0.0f, 0.0f);
        scaleObject(market, 100.0f, 100.0f, 100.0f);
        //translateObject(market2, 0.01f, 0.01f, 0.01f);
        gameUpdate();
    }

    removeGameObject(market);
    //removeGameObject(market2);
    gameFree();

    return 0;
}
