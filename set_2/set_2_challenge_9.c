#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{

    // get the length of the text
    // take modulo block length
    // create new buffer of length + remainder, initialized with proper bytes
    // transfer everything over, return

    if (argc != 3) {
        printf("Error: please provide ciphertext and blocksize\n");
    }

    char *inbuf = argv[1];
    int buflen = strlen(inbuf);

    int blocksize = atoi(argv[2]);
    int remainlen;

    //no padding necessary
    if ((remainlen = buflen % blocksize) == 0) {
        printf("%s\n", inbuf);
        return 0;
    }

    int padlen = blocksize - remainlen;

    char result[buflen + padlen];
    memset(result, 4, buflen + padlen); //must manually initialize because length is variable at compile time
    result[buflen + padlen] = '\0'; //null terminate string

    //copy over and print result string
    int i = 0;
    for ( ; i < buflen; i++) {
        result[i] = inbuf[i];
        printf("%c", result[i]);
    }

    for ( ; i < (int) strlen(result); i++) {
        printf("%x", result[i]);
    }
    printf("\n");

    //ensure that string was properly padded
    assert( (int) strlen(result) % blocksize == 0);
    return 0;
}
