#include "gameobject.h"

int gameObjectCount = 0;

void updateGameObjects() {
    for(int i = 0; i < gameObjectCount; i++) {
        for(int j = 0; j <= 3; j++) {
            for(int x = 0; x <= 3;x++) {
                if(j == x){
                    placeHolderObjectList[gameObjectList[i].object[0].objectID].modelMatrix[j][x] = 1.0f;
                }
                else {
                    placeHolderObjectList[gameObjectList[i].object[0].objectID].modelMatrix[j][x] = 0.0f;
                }
            }
        }
        mat4 transformMatrix = GLM_MAT4_IDENTITY_INIT;
        mat4 translationMatrix = GLM_MAT4_IDENTITY_INIT;
        glm_translate(translationMatrix, gameObjectList[i].object[0].translationVector);
        glm_mat4_mul(transformMatrix, translationMatrix, transformMatrix);

        if(gameObjectList[i].object[0].rotationAngle != 0.0f) {
            mat4 rotationMatrixX = GLM_MAT4_IDENTITY_INIT;
            mat4 rotationMatrixY = GLM_MAT4_IDENTITY_INIT;
            mat4 rotationMatrixZ = GLM_MAT4_IDENTITY_INIT;
            mat4 rotationMatrix = GLM_MAT4_IDENTITY_INIT;
            glm_rotate_x(rotationMatrixX, gameObjectList[i].object[0].rotationAngle * gameObjectList[i].object[0].rotationVector[0], rotationMatrixX);
            glm_rotate_y(rotationMatrixY, gameObjectList[i].object[0].rotationAngle * gameObjectList[i].object[0].rotationVector[1], rotationMatrixY);
            glm_rotate_z(rotationMatrixZ, gameObjectList[i].object[0].rotationAngle * gameObjectList[i].object[0].rotationVector[2], rotationMatrixZ);
            glm_mat4_mul(rotationMatrixX, rotationMatrixY, rotationMatrixY);
            glm_mat4_mul(rotationMatrixY, rotationMatrixZ, rotationMatrixZ);
            glm_mat4_mul(rotationMatrixZ, rotationMatrix, rotationMatrix);
            glm_mat4_mul(transformMatrix, rotationMatrix, transformMatrix);
        }

        if(gameObjectList[i].object[0].scaleVector[0] != 0) {
            mat4 scaleMatrix = GLM_MAT4_IDENTITY_INIT;
            glm_scale(scaleMatrix, gameObjectList[i].object[0].scaleVector);
            glm_mat4_mul(transformMatrix, scaleMatrix, transformMatrix);
        }
        glm_mat4_mul(placeHolderObjectList[gameObjectList[i].object[0].objectID].modelMatrix, transformMatrix, placeHolderObjectList[gameObjectList[i].object[0].objectID].modelMatrix);
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
    gameObjectList[gameObjectCount - 1].object[0].translationVector[0] = x;
    gameObjectList[gameObjectCount - 1].object[0].translationVector[1] = y;
    gameObjectList[gameObjectCount - 1].object[0].translationVector[2] = z;
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
    gameObjectList[gameObjectCount - 1].object[0].scaleVector[0] = 1.0f;
    gameObjectList[gameObjectCount - 1].object[0].scaleVector[1] = 1.0f;
    gameObjectList[gameObjectCount - 1].object[0].scaleVector[2] = 1.0f;
    gameObjectList[gameObjectCount - 1].object[0].rotationAngle = 0.0f;
    glm_vec3_zero(gameObjectList[gameObjectCount - 1].object[0].rotationVector);
    gameObjectList[gameObjectCount - 1].object[0].rotationTempX = 0.0f;
    gameObjectList[gameObjectCount - 1].object[0].rotationTempY = 0.0f;
    gameObjectList[gameObjectCount - 1].object[0].rotationTempZ = 0.0f;
    return gameObjectCount;
}

void transformObject(int gameObjectID, float x, float y, float z) {
    gameObjectList[gameObjectID - 1].object[0].translationVector[0] = x;
    gameObjectList[gameObjectID - 1].object[0].translationVector[1] = y;
    gameObjectList[gameObjectID - 1].object[0].translationVector[2] = z;
}

void translateObject(int gameObjectID, float x, float y, float z) {
    gameObjectList[gameObjectID - 1].object[0].translationVector[0] += x;
    gameObjectList[gameObjectID - 1].object[0].translationVector[1] += y;
    gameObjectList[gameObjectID - 1].object[0].translationVector[2] += z;
}

void scaleObject(int gameObjectID, float x, float y, float z) {
    gameObjectList[gameObjectID - 1].object[0].scaleVector[0] = x;
    gameObjectList[gameObjectID - 1].object[0].scaleVector[1] = y;
    gameObjectList[gameObjectID - 1].object[0].scaleVector[2] = z;
}

void scaleAddObject(int gameObjectID, float x, float y, float z) {
    gameObjectList[gameObjectID - 1].object[0].scaleVector[0] += x;
    gameObjectList[gameObjectID - 1].object[0].scaleVector[1] += y;
    gameObjectList[gameObjectID - 1].object[0].scaleVector[2] += z;
}

void rotateObject(int gameObjectID, float degrees, float x, float y, float z) {
    degrees = degrees / 57.29578;
    gameObjectList[gameObjectID - 1].object[0].rotationAngle = degrees;
    gameObjectList[gameObjectID - 1].object[0].rotationVector[0] = x;
    gameObjectList[gameObjectID - 1].object[0].rotationVector[1] = y;
    gameObjectList[gameObjectID - 1].object[0].rotationVector[2] = z;
    if(x != 0) {
        gameObjectList[gameObjectID - 1].object[0].rotationTempX = x * degrees;
    }
    if(y != 0) {
        gameObjectList[gameObjectID - 1].object[0].rotationTempY = y * degrees;
    }
    if(z != 0) {
        gameObjectList[gameObjectID - 1].object[0].rotationTempZ = z * degrees;
    }
}

void rotateAddObject(int gameObjectID, float degrees, float x, float y, float z) {
    degrees = degrees / 57.29578;
    float medDegrees = (gameObjectList[gameObjectID - 1].object[0].rotationAngle + degrees) / 2;
    if(x != 0) {
        gameObjectList[gameObjectID - 1].object[0].rotationTempX += x * degrees;
        if((gameObjectList[gameObjectID - 1].object[0].rotationTempX * 57.29578) >= 360.0f) {
            gameObjectList[gameObjectID - 1].object[0].rotationTempX -= (360.0f / 57.29578);
        }
    }
    if(y != 0) {
        gameObjectList[gameObjectID - 1].object[0].rotationTempY += y * degrees;
        if((gameObjectList[gameObjectID - 1].object[0].rotationTempY * 57.29578) >= 360.0f) {
            gameObjectList[gameObjectID - 1].object[0].rotationTempY -= (360.0f / 57.29578);
        }
    }
    if(z != 0) {
        gameObjectList[gameObjectID - 1].object[0].rotationTempZ += z * degrees;
        if((gameObjectList[gameObjectID - 1].object[0].rotationTempZ * 57.29578) >= 360.0f) {
            gameObjectList[gameObjectID - 1].object[0].rotationTempZ -= (360.0f / 57.29578);
        }
    }
    gameObjectList[gameObjectID - 1].object[0].rotationVector[0] = gameObjectList[gameObjectID - 1].object[0].rotationTempX / medDegrees;
    gameObjectList[gameObjectID - 1].object[0].rotationVector[1] = gameObjectList[gameObjectID - 1].object[0].rotationTempY / medDegrees;
    gameObjectList[gameObjectID - 1].object[0].rotationVector[2] = gameObjectList[gameObjectID - 1].object[0].rotationTempZ / medDegrees;
    gameObjectList[gameObjectID - 1].object[0].rotationAngle = medDegrees;
}

void removeGameObject(int gameObjectID) {
    free(gameObjectList[gameObjectID - 1].object);
}