#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "base64.h"

int main(int argc, char ** argv) {
    if (argc != 2) {
        printf("error: provide an input string");
        return EXIT_FAILURE;
    }

    char * in = argv[1];
    size_t len = strlen(in);
    int i;
    char * result = malloc(sizeof (char) * strlen(in));
    int counter = 0;

    for (i = 0; i < (int) strlen(in); i+= 3) {
        hex_to_base64(result + counter, in + i);
        counter += 2;
    }
    result[counter] = '\0';
    printf("%s\n", result);
    free(result);
    return 0;
}

