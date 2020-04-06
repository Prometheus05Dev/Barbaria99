#ifndef BARBARIA99_GAMEOBJECT_H
#define BARBARIA99_GAMEOBJECT_H

#include <elboronlib.h>
#include <stdio.h>
#include <dirent.h>

#define _LINUX

#ifdef _WINDOWS
//Do something to provide windows API informations.
#endif

#ifdef _LINUX
#include <pwd.h>
#include <zconf.h>
#include <string.h>
#include <stdlib.h>
#endif

struct Vertex {
    float x, y, z;
    float normalX, normalY, normalZ;
    float textureX, textureY;
};

struct PlaceHolderObject {
    const char *name; //Name of Object to get texture path and model path.
    int type; //Building or Entity
    int textureType; //PNG or JPG,...
    int modelType;  //PMF OR EAF
    //OpenGL data
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    struct Vertex *vertices;
    unsigned int numIndices;
    unsigned int *indices;
};

struct PlaceHolderObject *placeHolderObjectList; /*Array for game objects to access their placeholder and move it to
                                                    proper direction */

int numObjects; //Don't forget the index of numObjects starts at 1!

char *configPath;

void getConfigPath(); //Using Linux, returns ${HOME}/.config/barbaria under Windows Application Data

void loadObjects(); // Fills the placeHolderObjectList and sets their attributes

void loadPMF(char* path, int objectNumber); //Loads PMF(Prometheus Model File) file, to be called by loadObjects

void constructOpenGLData(int objectNumber);

void freeObjects(); //Frees manually allocated memory

#endif //BARBARIA99_GAMEOBJECT_H