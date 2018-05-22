#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "util.h"

int main(int argc, char ** argv)
{
	if (argc != 2) {
		printf("error: provide a ciphertext argument\n");
		return EXIT_FAILURE;
	}
	char * ciphertext = argv[1];
	size_t hexlen = strlen(ciphertext);
	size_t bytelen = hexlen / 2;
	char *bytes = malloc(sizeof(char) * bytelen);
	hex_to_bytes(bytes, ciphertext, hexlen);
	char *xored = malloc(sizeof(char) * bytelen + 1);
	int score;
	for (char c = 0; c < CHAR_MAX; c++) {
		single_byte_xor(c, xored, bytes, bytelen);
		xored[bytelen] = '\0';
		/*
		 * Woo!
		 * % make set_1_challenge_3; and ./set_1_challenge_3 | sort -nr | head -1
		 * > 271	X(88)	Cooking MC's like a pound of bacon
		 */
		score = score_english_plaintext(xored);
		if (score > 0)
			printf("%d\t%c(%d)\t%s\n", score, c, c, xored);
	}
	free(xored);
	free(bytes);
	return EXIT_SUCCESS;
}
