#include <stdio.h>
#include <stdlib.h>
#include "openssl/evp.h"

//TODO define constants

int main(int argc, char ** argv)
{
    if (argc != 4) {
        printf("Error: %d arguments provided. Input: <key length 16> <infile> <outfile>\n", argc);
        return 1;
    }

    unsigned char *key = (unsigned char *) argv[1]; // key is taken with length 16 (so not as hex)
    unsigned char outbuf[1024];
    unsigned char inbuf[1024];
    int outlen = 0;
    int inlen = 0;

    FILE *in;
    FILE *out;
    EVP_CIPHER_CTX *ctx;

    printf("%s\n", argv[2]);
    printf("%s\n", argv[3]);

    if (!(in = fopen(argv[2], "r"))) { //text must be decoded to binary
        //error
        printf("Error opening file\n");
        exit(1);
    }

    if (!(out = fopen(argv[3], "w"))) { // open output stream
        //error
        printf("Error opening file\n");
        exit(1);
    }

    ctx = EVP_CIPHER_CTX_new(); // create a new context

    // pass in the context, the decryption type, implementation engine=NULL(?), our key, and IV (which ECB doesn't use)
    EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, NULL);

    OPENSSL_assert(EVP_CIPHER_CTX_key_length(ctx) == 16); //make sure the key length is correct

    while(1) {
        inlen = fread(inbuf, 1, 1024, in); //read from file
        printf("%d\n", inlen);
        if (inlen <= 0) {
            printf("end of input found\n");
            fclose(in);
            break;
        }

        //decrypt and write to file chunk by chunk
        if (!EVP_DecryptUpdate(ctx, outbuf, &outlen, inbuf, inlen)) {
            //error
            EVP_CIPHER_CTX_free(ctx);
            printf("Error at Decrypt Update!\n");
            return 1;
        }

        fwrite(outbuf, 1, outlen, out);
    }

    // decrypt final adds padding if padding requested, otherwise makes sure that
    // there aren't leftover bits to decrypt. returns error if there are leftovers
    if (!EVP_DecryptFinal(ctx, outbuf, &outlen)) {
        //error
        EVP_CIPHER_CTX_free(ctx);
        printf("Error at Decrypt Final!\n");
        return 1;
    }

    fwrite(outbuf, 1, outlen, out);
    printf("hello");

    fclose(out);
    EVP_CIPHER_CTX_free(ctx);

    return 0;
}
