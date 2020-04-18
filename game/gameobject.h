#ifndef BARBARIA99_GAMEOBJECT_H
#define BARBARIA99_GAMEOBJECT_H

#include "../engine/object.h"
#include <stdio.h>
#include <stdlib.h>

struct GameObject {
    float xPosition, yPosition, zPosition;
    float xScale, yScale, zScale;
    int objectID;
};

int gameObjectCount;

struct GameObject *gameObjectList;

void updateGameObjects(); //Takes one instance of an object and places it for each Game object to proper direction

int addGameObject(float x, float y, float z, const char* name); //Places an object into the world. Returns game object ID.

void transformObject(int gameObjectID, float x, float y, float z);

void translateObject(int gameObjectID, float x, float y, float z);

void scaleObject(int gameObjectID, float x, float y, float z);

void removeGameObject(int gameObjectID);

#endif //BARBARIA99_GAMEOBJECT_H
