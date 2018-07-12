#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "openssl/evp.h"
#include "../util.h"

#define BLOCKSIZE 16
#define DECODED "../texts/10decoded.bin"
#define OUTFILE "../texts/10encrypted.txt"

void print_as_hex(unsigned char * c, int l) {
    for (int i = 0; i < l; i ++) {
        printf("%x", c[i]);
    }
    printf("\n");
}

int main(int argc, char ** argv)
{
    if (argc != 3) {
        printf("Error: %d arguments provided. Input: <key> <infile>\n", argc );
        return 1;
    }

    unsigned char *key = (unsigned char *) argv[1];
    unsigned char iv[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    unsigned char *outbuf = malloc ( 16 * sizeof(unsigned char));
    unsigned char *inbuf = malloc ( 17 * sizeof(unsigned char));
    int outlen = 0;
    int inlen = 0;

    FILE *in;
    FILE *out;
    EVP_CIPHER_CTX *ctx;

    if (!(in = fopen(argv[2], "r"))) {
        //error
        printf("Error opening file\n");
        exit(1);
    }

    if (!(out = fopen(OUTFILE, "w"))) {
        //error
        printf("Error opening file\n");
        exit(1);
    }

    ctx = EVP_CIPHER_CTX_new(); // create a new context

    EVP_EncryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, NULL);

    while(1) {
        memset(inbuf, 4, 16);
        inlen = fread(inbuf, 1, 16, in); //read from file

        //printf("%d\n", inlen);
        if (inlen <= 0) {
            printf("end of input found\n");
            fclose(in);
            break;
        }

        // printf("input block: ");
        // print_as_hex(inbuf, 16);
        // printf("inlen: %d\n", inlen);
        //printf("gonna xor\n");
        cbc_xor(iv, inbuf, 16);

        // printf("xor'd block: ");
        // print_as_hex(inbuf, 16);


        //decrypt and write to file chunk by chunk
        if (!EVP_EncryptUpdate(ctx, outbuf, &outlen, inbuf, 16)) {
            //error
            EVP_CIPHER_CTX_free(ctx);
            printf("Error at Decrypt Update!\n");
            return 1;
        }

        //printf("updated\n");
        // printf("outlen: %d\n", outlen);
        fwrite(outbuf, 1, outlen, out);


        // printf("encrypted block: ");
        // print_as_hex(outbuf, 16);
        //printf("outbuf: %s\n", outbuf);
        strncpy(iv, outbuf, 16);

        // printf("new iv: ");
        // print_as_hex(iv, 16);
        // printf("\n");

        //printf("iv: %s\n", iv);
    }

    if (!EVP_EncryptFinal(ctx, outbuf, &outlen)) {
        //error
        EVP_CIPHER_CTX_free(ctx);
        printf("Error at Decrypt Final!\n");
        return 1;
    }

    fwrite(outbuf, 1, outlen, out);

    fclose(out);
    EVP_CIPHER_CTX_free(ctx);

    return 0;

}
