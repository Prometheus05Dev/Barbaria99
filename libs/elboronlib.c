#include "elboronlib.h"

char *combineStrings(char *string1, char *string2) {
    char* tempString = malloc(strlen(string1) + strlen(string2));
    strcpy(tempString, string1);
    strcat(tempString, string2);
    return tempString;
}

