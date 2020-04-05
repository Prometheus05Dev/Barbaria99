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
                    printf("%s \n", &placeHolderObjectList[i].name);
                    if(strncmp(modelDirEntry->d_name, &placeHolderObjectList[i].name, strlen(&placeHolderObjectList[i].name)) == 0) {
                        loadPMF(modelDirEntry->d_name, i);
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


void loadPMF(const char* path, int objectNumber) {
    printf("%s %d \n", path, objectNumber);
}

void freeObjects() {
    free(configPath);
}