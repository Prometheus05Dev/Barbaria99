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

    //Reads all the config files to fill in the GameObject structs
    DIR *configDir;
    struct dirent *configDirEntry;
    if ((configDir = opendir (configDirectory)) != NULL) {
        while ((configDirEntry = readdir (configDir)) != NULL) {
            if(strcmp(configDirEntry->d_name, ".") && strcmp(configDirEntry->d_name, "..")){
                FILE *tmpFile = fopen(combineStrings(configDirectory, configDirEntry->d_name), "r");
                size_t len = 255;
                char *line = malloc(sizeof(char) * len);
                if(tmpFile == NULL){
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
                while(fgets(line, len, tmpFile) != NULL) {
                    if(lineReader == 0) {
                        struct PlaceHolderObject tmpObject;
                        tmpObject.name = line;
                        placeHolderObjectList[arrayReader] = &tmpObject;
                    }
                    else if(lineReader == 1) {
                        int number = 0;
                        sscanf(line, "%d", &number);
                        placeHolderObjectList[arrayReader]->type = number;
                    }
                    else if(lineReader == 2) {
                        int number = 0;
                        sscanf(line, "%d", &number);
                        placeHolderObjectList[arrayReader]->textureType = number;
                    }
                    else if(lineReader == 3) {
                        int number = 0;
                        sscanf(line, "%d", &number);
                        placeHolderObjectList[arrayReader]->modelType = number;
                        printf("%d %d\n", placeHolderObjectList[arrayReader]->modelType, arrayReader);
                    }
                    lineReader = lineReader + 1;
                }
                free(line);
                lineReader = 0;
                arrayReader = arrayReader + 1;
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
    if ((modelDir = opendir(modelDirectory)) != NULL) {
        while ((modelDirEntry = readdir(modelDir)) != NULL) {
            if(strcmp(modelDirEntry->d_name, ".") && strcmp(modelDirEntry->d_name, "..")) {
                printf("%d %d \n", placeHolderObjectList[arrayReader]->modelType, arrayReader);
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


void loadOBJ(const char* path) {

}

void freeObjects() {
    free(configPath);
}