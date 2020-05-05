#include "shader.h"

float fov2D = 45.0f;

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
                                char tempString[3];
                                memset(tempString, '\0', sizeof(tempString));
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
    const char *vsSource = vertexShaderSource;
    const char *fsSource = fragmentShaderSource;
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vsSource, NULL);
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

    glShaderSource(fragmentShader, 1,&fsSource, NULL);
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
    free(fullVertexShaderPath);
    free(fullFragmentShaderPath);
    free(vertexShaderSource);
    free(fragmentShaderSource);
}

void setShader3D() {
    mat4 projectionMatrix;
    glm_perspective(45.0f, 1920.0f / 1080.0f, 0.1f, 100.0f, projectionMatrix);
    passMatrixToShader(projectionMatrix, "projectionMatrix");
}

void setShader2D() {
    mat4 projectionMatrix;
    glm_perspective(fov2D, 1920.0f / 1080.0f, 0.1f, 100.0f, projectionMatrix);
    passMatrixToShader(projectionMatrix, "projectionMatrix");
}

void bindShader(int id) {
    glUseProgram(shaderList[id-1].shaderProgram);
    currentShader = shaderList[id-1].shaderProgram;
}

void setFov(float fov) {
    if(gameMode == 0) {
        mat4 projectionMatrix;
        glm_perspective(fov, 1920.0f / 1080.0f, 1.0f, 10.0f, projectionMatrix);
        passMatrixToShader(projectionMatrix, "projectionMatrix");
        fov2D = fov;
     }
    else {
        printf("Can not set FOV, 3D Mode!\n");
    }
}

void freeShaders() {
    free(vertexShadersPath);
    free(fragmentShadersPath);
    free(shaderList);
}

void passMatrixToShader(mat4 matrix, const char *name) {
    glUniformMatrix4fv(glGetUniformLocation(currentShader, name), 1, GL_FALSE, matrix[0]);
}