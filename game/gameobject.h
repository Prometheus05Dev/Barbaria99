#ifndef BARBARIA99_GAMEOBJECT_H
#define BARBARIA99_GAMEOBJECT_H

#include "../engine/object.h"
#include <cglm/cglm.h>
#include <stdio.h>
#include <stdlib.h>

struct GameObject {
    vec3 translationVector;
    float rotationAngle;
    vec3 rotationVector;
    vec3 scaleVector;
    float rotationTempX, rotationTempY, rotationTempZ;
    int objectID;
};

struct GameObjectPointer {
    struct GameObject *object;
};

int gameObjectCount;

struct GameObjectPointer *gameObjectList;

void updateGameObjects(); //Takes one instance of an object and places it for each Game object to proper direction

int addGameObject(float x, float y, float z, const char* name); //Places an object into the world. Returns game object ID.

void transformObject(int gameObjectID, float x, float y, float z);

void translateObject(int gameObjectID, float x, float y, float z);

void rotateObject(int gameObjectID, float degrees, float x, float y, float z);

void rotateAddObject(int gameObjectID, float degrees, float x, float y, float z);

void scaleObject(int gameObjectID, float x, float y, float z);

void scaleAddObject(int gameObjectID, float x, float y, float z);

void removeGameObject(int gameObjectID);

#endif //BARBARIA99_GAMEOBJECT_H
