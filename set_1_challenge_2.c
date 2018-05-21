#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "base64.h"

int xor_int(int, int);

int main(int argc, char ** argv)
{
    if (argc != 3) {
        printf("error: provide two arugment strings");
        return EXIT_FAILURE;
    }
    char *input_a = argv[1];
    char *input_b = argv[2];
    size_t len_a = strlen(input_a);
    size_t len_b = strlen(input_b);
    if (len_a != len_b) {
        printf("error: strings are not the same length");
        return EXIT_FAILURE;
    }
    char *out = malloc((sizeof(char) * len_a) + 1);
    size_t i;
    /*
     * loop through each character
     *  -> convert each input character to binary (hex_to_int)
     *  -> xor them (xor_int)
     *  -> convert the xor'ed character back to hex (int_to_hex)
     */
    for (i = 0; i < len_a; i++) {
        int a = hex_to_int(input_a[i]);
        int b = hex_to_int(input_b[i]);
        int x = xor_int(a, b);
        out[i] = int_to_hex(x);
    }
    out[i + 1] = '\0';
    printf("%s\n", out);
    free(out);
    return 0;
}

int xor_int(int a, int b)
{
    return ~(a & b) & (a | b);
}
