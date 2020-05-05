#ifndef BARBARIA99_SHADER_H
#define BARBARIA99_SHADER_H

#include <elboronlib.h>
#include <prometheusgamelib.h>
#include <GL/glew.h>
#include <cglm/cglm.h>
#include "../global_values.h"

char *vertexShadersPath;
char *fragmentShadersPath;

struct Shader {
    int shaderProgram;
    int id;
};

int currentShader;

float fov2D;

struct Shader *shaderList;

void readShaderDir(); /*The  first two Symbols of shader name have to be identifier e.g. 01Lightning Shader. Every Vertex
 * Shader needs a Fragment Shader with the corresponding ID*/

void createShaders(int id, char *vertexShaderPath, char *fragmentShaderPath);

void bindShader(int id);

void setShader3D();

void setShader2D();

void setFov(float fov);

void passMatrixToShader(mat4 matrix, const char *name);

void freeShaders();

#endif //BARBARIA99_SHADER_H
