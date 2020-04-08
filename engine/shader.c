#include "shader.h"

void readShaderDir() {

    vertexShadersPath = combineStrings(configPath, "/shaders/VertexShaders/");
    fragmentShadersPath = combineStrings(configPath, "/shaders/FragmentShaders/");

    DIR *vertexShaderDir;
    struct dirent *vertexShaderDirEntry;

    DIR *fragmentShaderDir;
    struct dirent *fragmentShaderDirEntry;

    if ((vertexShaderDir = opendir (vertexShadersPath))) {
        while ((vertexShaderDirEntry = readdir(vertexShaderDir))) {
            if (strcmp(vertexShaderDirEntry->d_name, ".") && strcmp(vertexShaderDirEntry->d_name, "..")) {
                if(fragmentShaderDir = opendir(fragmentShadersPath)) {
                    while(fragmentShaderDirEntry = readdir(fragmentShaderDir)) {
                        if(strcmp(fragmentShaderDirEntry->d_name, ".") && strcmp(fragmentShaderDirEntry->d_name, "..")) {
                            if(strncmp(vertexShaderDirEntry->d_name, fragmentShaderDirEntry->d_name, 2) == 0){
                                char *tempString;
                                int tempNumber;
                                strncpy(tempString, vertexShaderDirEntry->d_name,2);
                                sscanf(tempString, "%d", &tempNumber);
                                createShaders(tempNumber, vertexShaderDirEntry->d_name, fragmentShaderDirEntry->d_name);
                            }
                        }
                    }
                }
            }
        }
    }
}

void createShaders(int id, char *vertexShaderPath, char *fragmentShaderPath) {
    printf("Creating shader with id: %d and name: %s \n", id, vertexShaderPath);
}

void bindShader(int id) {

}

void freeShaders() {
    free(vertexShadersPath);
    free(fragmentShadersPath);
}
