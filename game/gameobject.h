#ifndef BARBARIA99_GAMEOBJECT_H
#define BARBARIA99_GAMEOBJECT_H

#include "../engine/object.h"
#include <stdio.h>
#include <stdlib.h>

struct GameObject {
    float xPosition, yPosition, zPosition;
    int objectID;
};

int gameObjectCount = 0;

struct GameObject *gameObjectList;

void updateGameObjects(); //Takes one instance of an object and places it for each Game object to proper direction

int addGameObject(float x, float y, float z, const char* name); //Places an object into the world. Returns game object ID.

void removeGameObject(int gameObjectID);

#endif //BARBARIA99_GAMEOBJECT_H
