#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "util.h"

char ciphertext[] = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";

int main()
{
	size_t hexlen = strlen(ciphertext);
	size_t bytelen = hexlen / 2;
	char *bytes = malloc(sizeof(char) * bytelen);
	hex_to_bytes(bytes, ciphertext, hexlen);
	char *xored = malloc(sizeof(char) * bytelen + 1);
	for (char c = 0; c < CHAR_MAX; c++) {
		single_byte_xor(c, xored, bytes, bytelen);
		xored[bytelen] = '\0';
		/*
		 * Woo!
		 * % make set_1_challenge_3; and ./set_1_challenge_3 | sort -nr | head -1
		 * > 271	X(88)	Cooking MC's like a pound of bacon
		 */
		printf("%d\t%c(%d)\t%s\n", score_english_plaintext(xored), c, c, xored);
	}
	free(xored);
	free(bytes);
	return EXIT_SUCCESS;
}
