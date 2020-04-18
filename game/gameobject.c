#include "gameobject.h"

void updateGameObjects() {

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
    return 0;
}

void removeGameObject(int gameObjectID) {

}
