#include "object.h"

void getConfigPath() {
#ifdef _LINUX
    struct passwd *pw = getpwuid(getuid());
    configPath = combineStrings(pw->pw_dir, "/.config/barbaria");
#endif
#ifdef _WINDOWS
#endif
}


void loadObjects() {
    char* modelDirectory = combineStrings(configPath, "/objects/models/");
    char* configDirectory = combineStrings(configPath, "/objects/configs/");

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

    free(modelDirectory);
    free(configDirectory);
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
                char delimiter[] = " ";
                char *lineWords = strtok(currentLine, delimiter);
                struct Vertex tempVertex;
                while(lineWords){
                    float vertexAsNumber = atof(lineWords);
                    switch(linePosition){
                        case 0:
                            printf("Vertex-X: %f \n", vertexAsNumber);
                            tempVertex.x = vertexAsNumber;
                            break;
                        case 1:
                            printf("Vertex-Y: %f \n", vertexAsNumber);
                            tempVertex.y = vertexAsNumber;
                            break;
                        case 2:
                            printf("Vertex-Z: %f \n", vertexAsNumber);
                            tempVertex.z = vertexAsNumber;
                            break;
                        case 3:
                            printf("Normal-X: %f \n", vertexAsNumber);
                            tempVertex.normalX = vertexAsNumber;
                            break;
                        case 4:
                            printf("Normal-Y: %f \n", vertexAsNumber);
                            tempVertex.normalY = vertexAsNumber;
                            break;
                        case 5:
                            printf("Normal-Z: %f \n", vertexAsNumber);
                            tempVertex.normalZ = vertexAsNumber;
                            break;
                        case 6:
                            printf("Texture-X: %f \n", vertexAsNumber);
                            tempVertex.textureX = vertexAsNumber;
                            break;
                        case 7:
                            printf("Texture-Y: %f \n", vertexAsNumber);
                            tempVertex.textureY = vertexAsNumber;
                            break;
                        default:
                            break;
                    }
                    ++linePosition;
                    lineWords = strtok(NULL, delimiter);
                }
                linePosition = 0;
            }
            else if(loadMode == 1){
                numIndices++;
                sscanf(currentLine, "%d", &currentIndex);
                placeHolderObjectList[objectNumber].indices = realloc(placeHolderObjectList[objectNumber].indices, numIndices *
                        sizeof(*placeHolderObjectList[objectNumber].indices));
                placeHolderObjectList[objectNumber].indices[numIndices-1] = currentIndex;
            }
            else {
                printf("A weird bug occurred at line 136 of object.c");
                return;
            }
        }
    }
    placeHolderObjectList[objectNumber].numIndices = numIndices;
    free(path);
}

void freeObjects() {
    free(configPath);
}