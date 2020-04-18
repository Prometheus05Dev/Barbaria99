#include "object.h"

void loadObjects() {

    char* modelDirectory = combineStrings(configPath, "/objects/models/");
    char* configDirectory = combineStrings(configPath, "/objects/configs/");
    char* textureDirectory = combineStrings(configPath, "/objects/textures/");

    int arrayReader = 0;
    int lineReader = 0;
    numObjects = 0;

    //Reads all the config files to fill in the GameObject structs
    DIR *configDir;
    struct dirent *configDirEntry;
    if ((configDir = opendir (configDirectory))) {
        while ((configDirEntry = readdir (configDir))) {
            if(strcmp(configDirEntry->d_name, ".") && strcmp(configDirEntry->d_name, "..")){
                FILE *tmpFile = fopen(combineStrings(configDirectory, configDirEntry->d_name), "r");
                size_t len = 255;
                char *line = malloc(sizeof(char) * len);
                if(!tmpFile){
                    printf("%s %s \n", "Could not read file:", configDirEntry->d_name);
                    return;
                }

                //Resizes array to get object count
                if(arrayReader == 0){
                    placeHolderObjectList = malloc(sizeof(struct PlaceHolderObject));
                }
                else if(arrayReader >= 1){
                    placeHolderObjectList = realloc(placeHolderObjectList, (arrayReader + 1) * sizeof(struct PlaceHolderObject));
                }

                //Reads line by line the file and sets the appropriate structure arguments
                while(fgets(line, len, tmpFile)) {
                    struct PlaceHolderObject tmpObject;
                    if(lineReader == 0) {
                        const char* name;
                        sscanf(line, "%s", &name);
                        tmpObject.name = name;
                    }
                    else if(lineReader == 1) {
                        int number = 0;
                        sscanf(line, "%d", &number);
                        tmpObject.type = number;
                    }
                    else if(lineReader == 2) {
                        int number = 0;
                        sscanf(line, "%d", &number);
                        tmpObject.textureType = number;
                    }
                    else if(lineReader == 3) {
                        int number = 0;
                        sscanf(line, "%d", &number);
                        tmpObject.modelType = number;
                    }
                    lineReader = lineReader + 1;
                    placeHolderObjectList[arrayReader] = tmpObject;
                }
                free(line);
                lineReader = 0;
                arrayReader = arrayReader + 1;
                numObjects = numObjects + 1;
            }
        }
        closedir (configDir);
    } else {
        perror("configDirectory of objects could not be opened!");
    }

    arrayReader = 0;

    //Reads all the model files to fill in the GameObject structs
    DIR *modelDir;
    struct dirent *modelDirEntry;
    if ((modelDir = opendir(modelDirectory))) {
        while((modelDirEntry = readdir(modelDir))) {
            if(strcmp(modelDirEntry->d_name, ".") && strcmp(modelDirEntry->d_name, "..")) {
                for(int i = 0; i < numObjects; i++) {
                    if(strncmp(modelDirEntry->d_name, &placeHolderObjectList[i].name, strlen(&placeHolderObjectList[i].name)) == 0) {
                        loadPMF(combineStrings(modelDirectory, modelDirEntry->d_name), i);
                    }
                }
                arrayReader = arrayReader + 1;
            }
        }
        closedir(modelDir);
    }
    else {
        perror("modelDirectory of objects could not be opened!");
    }

    DIR *textureDir;
    struct dirent *textureDirEntry;
    if((textureDir = opendir(textureDirectory))) {
        while((textureDirEntry = readdir(textureDir))) {
            if(strcmp(textureDirEntry->d_name, ".") && strcmp(textureDirEntry->d_name, "..")) {
                for(int i = 0; i < numObjects; i++) {
                    if(strncmp(textureDirEntry->d_name, &placeHolderObjectList[i].name, strlen(&placeHolderObjectList[i].name)) == 0) {
                        loadTexture(combineStrings(textureDirectory, textureDirEntry->d_name), i);
                    }
                }
            }
        }
    }
    else {
        perror("textureDirectory of objects could not be opened!");
    }

    free(modelDirectory);
    free(configDirectory);
    free(textureDirectory);
}


void loadPMF(char* path, int objectNumber) {
    printf("Loading object: %s with number: %d \n", path, objectNumber);

    int lineCounter = 0;
    FILE *pmfFile;
    char* currentLine;
    size_t length = 0;
    ssize_t read;
    struct Vertex currentVertex;
    int numIndices = 0;
    int numVertices = 0;
    int currentIndex;
    int linePosition = 0;

    pmfFile = fopen(path, "r");
    int loadMode; //0 = Vertices 1 = Indices
    if(!pmfFile) {
        printf("The file: %s could not be opened!", path);
        return;
    }

    while((read = getline(&currentLine, &length, pmfFile)) != -1) {
        lineCounter++;

        if(strncmp(currentLine, "Vertices", 8) == 0) {
            placeHolderObjectList[objectNumber].vertices = malloc(0 * sizeof(struct Vertex));
            loadMode = 0;
            continue;
        }

        if(strncmp(currentLine, "Indices", 7) == 0) {
            placeHolderObjectList[objectNumber].indices = malloc(0 * sizeof(unsigned int));
            loadMode = 1;
            continue;
        }

        else{
            if(loadMode == 0){
                ++numVertices;

                placeHolderObjectList[objectNumber].vertices = realloc(placeHolderObjectList[objectNumber].vertices, numVertices *
                        sizeof(*placeHolderObjectList[objectNumber].vertices));

                char delimiter[] = " ";
                char *lineWords = strtok(currentLine, delimiter);
                struct Vertex tempVertex;

                while(lineWords){
                    float vertexAsNumber = atof(lineWords);
                    switch(linePosition){
                        case 0:
                            tempVertex.x = vertexAsNumber;
                            break;
                        case 1:
                            tempVertex.y = vertexAsNumber;
                            break;
                        case 2:
                            tempVertex.z = vertexAsNumber;
                            break;
                        case 3:
                            tempVertex.normalX = vertexAsNumber;
                            break;
                        case 4:
                            tempVertex.normalY = vertexAsNumber;
                            break;
                        case 5:
                            tempVertex.normalZ = vertexAsNumber;
                            break;
                        case 6:
                            tempVertex.textureX = vertexAsNumber;
                            break;
                        case 7:
                            tempVertex.textureY = vertexAsNumber;
                            break;
                        default:
                            break;
                    }

                    ++linePosition;
                    lineWords = strtok(NULL, delimiter);
                }

                linePosition = 0;
                placeHolderObjectList[objectNumber].vertices[numVertices-1] = tempVertex;
            }

            else if(loadMode == 1){
                numIndices++;
                sscanf(currentLine, "%u", &currentIndex);

                placeHolderObjectList[objectNumber].indices = realloc(placeHolderObjectList[objectNumber].indices, numIndices *
                        sizeof(*placeHolderObjectList[objectNumber].indices));
                placeHolderObjectList[objectNumber].indices[numIndices-1] = currentIndex;
            }

            else {
                printf("A weird bug occurred at line 136 of object.c");
                return;
            }
        }
        placeHolderObjectList[objectNumber].numVertices = numVertices;
    }
    placeHolderObjectList[objectNumber].numIndices = numIndices;
    constructOpenGLData(objectNumber);
    free(path);
}

void loadTexture(char* path, int objectNumber) {
    printf("Loading texture: %s with object number: %d\n", path, objectNumber);
    int textureWidth = 0;
    int textureHeight = 0;
    int bitsPerPixel = 0;
    stbi_uc *textureBuffer = stbi_load(path, &textureWidth, &textureHeight, &bitsPerPixel, 4);
    printf("Texture Width: %d Texture Height: %d Bits per Pixel: %d\n", textureWidth, textureHeight, bitsPerPixel);
    glGenTextures(1, &placeHolderObjectList[objectNumber].textureBufferId);
    glBindTexture(GL_TEXTURE_2D, placeHolderObjectList[objectNumber].textureBufferId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureBuffer);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void constructOpenGLData(int objectNumber) {
    printf("Constructing object: %s with object number: %d\n", &placeHolderObjectList[objectNumber].name, objectNumber);
    stbi_set_flip_vertically_on_load(1);
    glGenVertexArrays(1, &placeHolderObjectList[objectNumber].VAO);
    glGenBuffers(1, &placeHolderObjectList[objectNumber].VBO);
    glGenBuffers(1, &placeHolderObjectList[objectNumber].EBO);
    glBindVertexArray(placeHolderObjectList[objectNumber].VAO);
    glBindBuffer(GL_ARRAY_BUFFER, placeHolderObjectList[objectNumber].VBO);
    glBufferData(GL_ARRAY_BUFFER, placeHolderObjectList[objectNumber].numVertices * sizeof(struct Vertex), &placeHolderObjectList[objectNumber].vertices[0], GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, placeHolderObjectList[objectNumber].EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, placeHolderObjectList[objectNumber].numIndices * sizeof(unsigned int), &placeHolderObjectList[objectNumber].indices[0], GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (void*)offsetof(struct Vertex, normalX));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (void*)offsetof(struct Vertex, textureX));
    glEnableVertexAttribArray(2);
}

void drawObject(int objectNumber) {
    passMatrixToShader(placeHolderObjectList[objectNumber].modelMatrix, "modelMatrix");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, placeHolderObjectList[objectNumber].textureBufferId);
    glBindVertexArray(placeHolderObjectList[objectNumber].VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, placeHolderObjectList[objectNumber].EBO);
    glDrawElements(GL_TRIANGLES, placeHolderObjectList[objectNumber].numIndices, GL_UNSIGNED_INT, 0);
}

void freeObjects() {
}

int getObjectNumber(const char *name) {
    for(int i = 0; i < numObjects; i++) {
        if(strcmp(&placeHolderObjectList[i].name, name) == 0) {
            return i;
        }
    }
    printf("Object: %s could not be found!\n", name);
}
