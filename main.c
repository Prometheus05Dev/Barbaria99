#include <stdio.h>
#include "engine/object.h"

int main() {
    printf("Hello, World!\n");
    getConfigPath();
    loadObjects();
    freeObjects();
    return 0;
}
