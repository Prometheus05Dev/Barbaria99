#include "gameobject.h"

int gameObjectCount = 0;

void updateGameObjects() {
    for(int i = 0; i < gameObjectCount; i++) {
        drawObject(gameObjectList[gameObjectCount - 1].objectID);
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
    return gameObjectCount;
}

void removeGameObject(int gameObjectID) {

}
