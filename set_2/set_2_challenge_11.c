#include <stdio.h>
#include <stdlib.h>
#include "../util.h"

#define OUTFILE "../texts/11appended.txt"

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("Error: include plaintext file to encrypt!\n");
    }

    unsigned char inbuf[1024];
    FILE *in;
    FILE *out;
    int inlen = 0;

    if (!(in = fopen(argv[1], "r"))) {
        //error
        printf("Error opening file\n");
        exit(1);
    }

    if (!(out = fopen(OUTFILE, "w"))) { // open output stream
        //error
        printf("Error opening file\n");
        exit(1);
    }

    // get a random key
    int rand_front = arc4random_uniform(5) + 5;
    int rand_back = arc4random_uniform(5) + 5;

    unsigned char key[16];
    generate_random_key(key);

    // append 5-10 random bytes to front of plaintext

    int i;
    for (i = 0; i < rand_front; i++) {
        // well wait should i do this random or should i keep it uniform?
        // guess it cant hurt to be random :/
        // inbuf[i] = arc4random_unform(255);
        inbuf[i] = 'A';
    }

    inlen = fread(inbuf + i, 1, 1024 - i, in) + i;

    do {
        fwrite(inbuf, 1, inlen, out);
    } while ((inlen = fread(inbuf, 1, 1024, in)));


    fclose(in);

    unsigned char padding[rand_back];
    for (int i = 0; i < rand_back; i++) {
        padding[i] = 'A';
    }
    fwrite(padding, 1, sizeof(padding)/sizeof(padding[0]), out);

    fclose(out);

    return 0;
}

//TODO: move encyrption code to utils
//TODO: choose randomly between the two encryptions and encrypt appended text
