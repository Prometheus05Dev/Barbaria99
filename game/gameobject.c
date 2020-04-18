#include "gameobject.h"

int gameObjectCount = 0;

void updateGameObjects() {
    for(int i = 0; i < gameObjectCount; i++) {
        for(int j = 0; j <= 3; j++) {
            for(int x = 0; x <= 3;x++) {
                if(j == x){
                    placeHolderObjectList[gameObjectList[i].objectID].modelMatrix[j][x] = 1.0f;
                }
                else {
                    placeHolderObjectList[gameObjectList[i].objectID].modelMatrix[j][x] = 0.0f;
                }
            }
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
    return gameObjectCount;
}

void removeGameObject(int gameObjectID) {

}
