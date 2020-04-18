#include "gameobject.h"

int gameObjectCount = 0;

void updateGameObjects() {
    for(int i = 0; i < gameObjectCount; i++) {
        placeHolderObjectList[gameObjectList[i].objectID].modelMatrix[3][0] = gameObjectList[i].xPosition;
        placeHolderObjectList[gameObjectList[i].objectID].modelMatrix[3][1] = gameObjectList[i].yPosition;
        placeHolderObjectList[gameObjectList[i].objectID].modelMatrix[3][2] = gameObjectList[i].zPosition;
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

void removeGameObject(int gameObjectID) {

}