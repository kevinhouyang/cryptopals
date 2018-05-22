#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "util.h"

char ciphertext[] = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";

void single_byte_xor(char, char *, char *, size_t);

int main()
{
	size_t hexlen = strlen(ciphertext);
	size_t bytelen = hexlen / 2;
	char *bytes = malloc(sizeof(char) * bytelen);
	/* fill a byte array of the ciphertext */
	char a, b;
	for (size_t i = 0; i < hexlen; i += 2) {
		a = hex_to_int(ciphertext[i]);
		b = hex_to_int(ciphertext[i + 1]);
		bytes[i / 2] = a << 4 | b;
	}
	char *xored = malloc(sizeof(char) * bytelen + 1);
	for (char c = 0; c < CHAR_MAX; c++) {
		single_byte_xor(c, xored, bytes, bytelen);
		xored[bytelen] = '\0';
		/*
		 * Woo!
		 * X(88):  Cooking MC's like a pound of bacon
		 */
		printf("%c(%d):\t%s\n", c, c, xored);
	}
	free(xored);
	free(bytes);
	return EXIT_SUCCESS;
}

void single_byte_xor(char byte, char * dest, char * src, size_t len)
{
	for (size_t i = 0; i < len; i++) {
		dest[i] = xor(byte, src[i]);
	}
}
