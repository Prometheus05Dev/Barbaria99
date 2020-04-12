#include "shader.h"

void readShaderDir() {

    int shaderCount = 0;

    shaderList = malloc(sizeof(struct Shader));

    vertexShadersPath = combineStrings(configPath, "/shaders/VertexShaders/");
    fragmentShadersPath = combineStrings(configPath, "/shaders/FragmentShaders/");

    DIR *vertexShaderDir;
    struct dirent *vertexShaderDirEntry;

    DIR *fragmentShaderDir;
    struct dirent *fragmentShaderDirEntry;

    if ((vertexShaderDir = opendir (vertexShadersPath))) {
        while ((vertexShaderDirEntry = readdir(vertexShaderDir))) {
            if (strcmp(vertexShaderDirEntry->d_name, ".") && strcmp(vertexShaderDirEntry->d_name, "..")) {
                ++shaderCount;
                shaderList = realloc(shaderList, shaderCount * sizeof(struct Shader));
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
    char *fullVertexShaderPath = combineStrings(vertexShadersPath, vertexShaderPath);
    char *fullFragmentShaderPath = combineStrings(fragmentShadersPath, fragmentShaderPath);
    char *vertexShaderSource = "";
    char *fragmentShaderSource = "";
    FILE *filePointer;
    int bufferLength = 256;
    char buffer[bufferLength];
    filePointer = fopen(fullVertexShaderPath, "r");
    while(fgets(buffer, bufferLength, filePointer)) {
        vertexShaderSource = combineStrings(vertexShaderSource, buffer);
    }
    filePointer = fopen(fullFragmentShaderPath, "r");
    while(fgets(buffer, bufferLength, filePointer)) {
        fragmentShaderSource = combineStrings(fragmentShaderSource, buffer);
    }
    fclose(filePointer);
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("Vertex Shader creation failed with error log: %s \n", infoLog);
    }
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1,  &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("Vertex Shader creation failed with error log: %s \n", infoLog);
    }
    struct Shader tempShader;
    tempShader.shaderProgram = glCreateProgram();
    glAttachShader(tempShader.shaderProgram, vertexShader);
    glAttachShader(tempShader.shaderProgram, fragmentShader);
    glLinkProgram(tempShader.shaderProgram);
    glGetProgramiv(tempShader.shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(tempShader.shaderProgram, 512, NULL, infoLog);
        printf("Linking of shader program failed: %s \n", infoLog);
    }
    shaderList[id - 1].id = id;
    shaderList[id - 1].shaderProgram = tempShader.shaderProgram;
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    free(fullVertexShaderPath);
    free(fullFragmentShaderPath);
    free(vertexShaderSource);
    free(fragmentShaderSource);
}

void bindShader(int id) {
    glUseProgram(shaderList[id-1].shaderProgram);
}

void freeShaders() {
    free(vertexShadersPath);
    free(fragmentShadersPath);
    free(shaderList);
}
