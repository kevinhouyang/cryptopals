#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//TODO: decode text using decode, define constants

/*
 * takes in an array of size 320 characters, brute force checks for duplicates
 */
int num_duplicates(char * line)
{
    int duplicates = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = i + 1; j < 10; j++) {
            if (!strncmp(line + (i * 32), line + (j * 32), 32)) {
                duplicates += 1;
            }
        }
    }
    return duplicates;

}

int main(int argc, char ** argv)
{
    if (argc != 2) {
        printf("Error: provide a ciphertext file\n");
        return EXIT_FAILURE;
    }

    FILE *in;
    char inbuf[322];
    int collisions[205] = { 0 };
    int idx = 0;

    if (!(in = fopen(argv[1], "r"))) {
        //error
        printf("Error opening file\n");
        exit(1);
    } else {
        printf("file opened!\n");
    }

    // each line has 320 characters in hex = 1280 bits
    // each block has 16 bytes = 128 bits
    // so there are 10 blocks per line
    // if any of the blocks are exactly the same within the same line, it is
    // very likely that the line was encoded using ECB

    while (fgets(inbuf, 322, in)) {
        inbuf[321] = '\0';
        printf("checking line: %d!\n", idx);
        printf("%s\n", inbuf);
        collisions[idx] = num_duplicates(inbuf);
        idx += 1;
    }

    printf("closing file!\n");
    fclose(in);

    //find the row with the most collisions!
    int max = 0;
    int max_row = 0;
    for (int i = 0; i < 205; i++) {
        if (collisions[i] > max) {
            max = collisions[i];
            max_row = i;
        }
    }

    printf("the encrypted text is at row %d with %d collisions\n", max_row + 1, collisions[max_row]);
    return max_row;
    //soln: row 133
    //d880619740a8a19b7840a8a31c810a3d08649af70dc06f4fd5d2d69c744cd283e2dd052f6b641dbf9d11b0348542bb5708649af70dc06f4fd5d2d69c744cd2839475c9dfdbc1d46597949d9c7e82bf5a08649af70dc06f4fd5d2d69c744cd28397a93eab8d6aecd566489154789a6b0308649af70dc06f4fd5d2d69c744cd283d403180c98c8f6db1f2a3f9c4040deb0ab51b29933f2c123c58386b06fba186a
    //yay!!!!! but how do we decrypt this?
}
