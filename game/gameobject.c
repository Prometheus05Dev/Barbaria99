#include "gameobject.h"

int gameObjectCount = 0;

void updateGameObjects() {
    for(int i = 0; i < gameObjectCount; i++) {
        placeHolderObjectList[gameObjectList[i].objectID].modelMatrix[3][0] = gameObjectList[i].xPosition;
        placeHolderObjectList[gameObjectList[i].objectID].modelMatrix[3][1] = gameObjectList[i].yPosition;
        placeHolderObjectList[gameObjectList[i].objectID].modelMatrix[3][2] = gameObjectList[i].zPosition;
        if(gameObjectList[i].xScale != 0) {
            placeHolderObjectList[gameObjectList[i].objectID].modelMatrix[0][0] = gameObjectList[i].xScale;
        }
        else {
            placeHolderObjectList[gameObjectList[i].objectID].modelMatrix[0][0] = 1.0f;
        }
        if(gameObjectList[i].xScale != 0) {
            placeHolderObjectList[gameObjectList[i].objectID].modelMatrix[1][1] = gameObjectList[i].yScale;
        }
        else {
            placeHolderObjectList[gameObjectList[i].objectID].modelMatrix[1][1] = 1.0f;
        }
        if(gameObjectList[i].xScale != 0) {
            placeHolderObjectList[gameObjectList[i].objectID].modelMatrix[2][2] = gameObjectList[i].zScale;
        }
        else {
            placeHolderObjectList[gameObjectList[i].objectID].modelMatrix[2][2] = 1.0f;
        }
        drawObject(gameObjectList[i].objectID);
    }
}

int addGameObject(float x, float y, float z, const char* name) {
    gameObjectCount++;
    if(gameObjectCount == 1) {
        gameObjectList = malloc(sizeof(struct GameObject));
    }
    else {
        gameObjectList = realloc(gameObjectList, gameObjectCount * sizeof(struct GameObject));
    }
    gameObjectList[gameObjectCount - 1].xPosition = x;
    gameObjectList[gameObjectCount - 1].yPosition = y;
    gameObjectList[gameObjectCount - 1].zPosition = z;
    gameObjectList[gameObjectCount - 1].objectID = getObjectNumber(name);
    for(int j = 0; j <= 3; j++) {
        for(int x = 0; x <= 3;x++) {
            if(j == x){
                placeHolderObjectList[gameObjectList[gameObjectCount - 1].objectID].modelMatrix[j][x] = 1.0f;
            }
            else {
                placeHolderObjectList[gameObjectList[gameObjectCount - 1].objectID].modelMatrix[j][x] = 0.0f;
            }
        }
    }
    transformObject(gameObjectCount, x, y, z);
    gameObjectList[gameObjectCount - 1].xScale = 1.0f;
    gameObjectList[gameObjectCount - 1].yScale = 1.0f;
    gameObjectList[gameObjectCount - 1].zScale = 1.0f;
    return gameObjectCount;
}

void transformObject(int gameObjectID, float x, float y, float z) {
    gameObjectList[gameObjectID - 1].xPosition = x;
    gameObjectList[gameObjectID - 1].yPosition = y;
    gameObjectList[gameObjectID - 1].zPosition = z;
}

void translateObject(int gameObjectID, float x, float y, float z) {
    gameObjectList[gameObjectID - 1].xPosition += x;
    gameObjectList[gameObjectID - 1].yPosition += y;
    gameObjectList[gameObjectID - 1].zPosition += z;
}

void scaleObject(int gameObjectID, float x, float y, float z) {
    gameObjectList[gameObjectID - 1].xScale = x;
    gameObjectList[gameObjectID - 1].yScale = y;
    gameObjectList[gameObjectID - 1].zScale = z;
}

void scaleAddObject(int gameObjectID, float x, float y, float z) {
    gameObjectList[gameObjectID - 1].xScale += x;
    gameObjectList[gameObjectID - 1].yScale += y;
    gameObjectList[gameObjectID - 1].zScale += z;
}

void removeGameObject(int gameObjectID) {

}