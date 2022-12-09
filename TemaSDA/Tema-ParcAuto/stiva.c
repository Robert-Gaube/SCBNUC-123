#include <stdio.h>
#include <stdlib.h>
#include "stiva.h"

void throw_error(char *msg) {
    printf("Error: %s\n", msg);
    exit(-1);
}