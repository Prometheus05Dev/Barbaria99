#include "gameobject.h"

int gameObjectCount = 0;

void updateGameObjects() {
    for(int i = 0; i < gameObjectCount; i++) {
        for(int j = 0; j <= 3; j++) {
            for(int x = 0; x <= 3;x++) {
                if(j == x){
                    placeHolderObjectList[gameObjectList[gameObjectCount - 1].object[0].objectID].modelMatrix[j][x] = 1.0f;
                }
                else {
                    placeHolderObjectList[gameObjectList[gameObjectCount - 1].object[0].objectID].modelMatrix[j][x] = 0.0f;
                }
            }
        }
        placeHolderObjectList[gameObjectList[i].object[0].objectID].modelMatrix[3][0] = gameObjectList[i].object[0].xPosition;
        placeHolderObjectList[gameObjectList[i].object[0].objectID].modelMatrix[3][1] = gameObjectList[i].object[0].yPosition;
        placeHolderObjectList[gameObjectList[i].object[0].objectID].modelMatrix[3][2] = gameObjectList[i].object[0].zPosition;
        if(gameObjectList[i].object[0].rotationAngle != 0.0f) {
            glm_rotate(placeHolderObjectList[gameObjectList[i].object[0].objectID].modelMatrix, gameObjectList[i].object[0].rotationAngle, gameObjectList[i].object[0].rotationVector);
        }
        if(gameObjectList[i].object[0].xScale != 0) {
            placeHolderObjectList[gameObjectList[i].object[0].objectID].modelMatrix[0][0] = gameObjectList[i].object[0].xScale;
        }
        if(gameObjectList[i].object[0].xScale != 0) {
            placeHolderObjectList[gameObjectList[i].object[0].objectID].modelMatrix[1][1] = gameObjectList[i].object[0].yScale;
        }
        if(gameObjectList[i].object[0].xScale != 0) {
            placeHolderObjectList[gameObjectList[i].object[0].objectID].modelMatrix[2][2] = gameObjectList[i].object[0].zScale;
        }
        drawObject(gameObjectList[i].object[0].objectID);
    }
}

int addGameObject(float x, float y, float z, const char* name) {
    gameObjectCount++;
    if(gameObjectCount == 1) {
        gameObjectList = malloc(sizeof(struct GameObjectPointer));
        gameObjectList[gameObjectCount - 1].object = malloc(sizeof(struct GameObject));
    }
    else {
        gameObjectList = realloc(gameObjectList, gameObjectCount * sizeof(struct GameObjectPointer));
        gameObjectList[gameObjectCount - 1].object = malloc(sizeof(struct GameObject));
    }
    gameObjectList[gameObjectCount - 1].object[0].xPosition = x;
    gameObjectList[gameObjectCount - 1].object[0].yPosition = y;
    gameObjectList[gameObjectCount - 1].object[0].zPosition = z;
    gameObjectList[gameObjectCount - 1].object[0].objectID = getObjectNumber(name);
    for(int j = 0; j <= 3; j++) {
        for(int x = 0; x <= 3;x++) {
            if(j == x){
                placeHolderObjectList[gameObjectList[gameObjectCount - 1].object[0].objectID].modelMatrix[j][x] = 1.0f;
            }
            else {
                placeHolderObjectList[gameObjectList[gameObjectCount - 1].object[0].objectID].modelMatrix[j][x] = 0.0f;
            }
        }
    }
    transformObject(gameObjectCount, x, y, z);
    gameObjectList[gameObjectCount - 1].object[0].xScale = 1.0f;
    gameObjectList[gameObjectCount - 1].object[0].yScale = 1.0f;
    gameObjectList[gameObjectCount - 1].object[0].zScale = 1.0f;
    gameObjectList[gameObjectCount - 1].object[0].rotationAngle = 0.0f;
    glm_vec3_zero(gameObjectList[gameObjectCount - 1].object[0].rotationVector);
    return gameObjectCount;
}

void transformObject(int gameObjectID, float x, float y, float z) {
    gameObjectList[gameObjectID - 1].object[0].xPosition = x;
    gameObjectList[gameObjectID - 1].object[0].yPosition = y;
    gameObjectList[gameObjectID - 1].object[0].zPosition = z;
}

void translateObject(int gameObjectID, float x, float y, float z) {
    gameObjectList[gameObjectID - 1].object[0].xPosition += x;
    gameObjectList[gameObjectID - 1].object[0].yPosition += y;
    gameObjectList[gameObjectID - 1].object[0].zPosition += z;
}

void scaleObject(int gameObjectID, float x, float y, float z) {
    gameObjectList[gameObjectID - 1].object[0].xScale = x;
    gameObjectList[gameObjectID - 1].object[0].yScale = y;
    gameObjectList[gameObjectID - 1].object[0].zScale = z;
}

void scaleAddObject(int gameObjectID, float x, float y, float z) {
    gameObjectList[gameObjectID - 1].object[0].xScale += x;
    gameObjectList[gameObjectID - 1].object[0].yScale += y;
    gameObjectList[gameObjectID - 1].object[0].zScale += z;
}

void rotateObject(int gameObjectID, float degrees, float x, float y, float z) {
    gameObjectList[gameObjectID - 1].object[0].rotationAngle = degrees;
    gameObjectList[gameObjectID - 1].object[0].rotationVector[0] = x;
    gameObjectList[gameObjectID - 1].object[0].rotationVector[1] = y;
    gameObjectList[gameObjectID - 1].object[0].rotationVector[2] = z;
}

void removeGameObject(int gameObjectID) {
    free(gameObjectList[gameObjectID - 1].object);
}