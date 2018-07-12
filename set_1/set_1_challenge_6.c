#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../util.h"

int character_hamming_distance(char a, char b) {
	char c = xor(a, b);
	int counter = 0;
	for( int i = 0; i < 8; i++) {
		counter += c >> i & 1;
	}
	return counter;
}

int hamming_distance(char* a, char* b, size_t len) {
	int sum = 0;
	for(size_t i = 0; i < len; i++) {
		//printf("a[%zu] is %c, b[%zu] is %c\n", i, a[i], i, b[i]);
		sum += character_hamming_distance(a[i], b[i]);
	}
	return sum;
}

void print_by_block(int blocklen, char * input, int cypher_len) {
	for (int i = 0; i < (int) strlen(input)/blocklen + 1; i++) {
		for (int j = 0; j < blocklen; j++) {
			if (i * blocklen + j  == cypher_len) {
				printf("\n");
				return;
			}
			printf("%c", input[i * blocklen + j]);
		}
		printf(" ");
	}
	printf("\n");
}

int main(int argc, char ** argv)
{
	if (argc != 2) {
		printf("error: provide cyphertext");
		return EXIT_FAILURE;
	}

	char *cypher = argv[1];
	size_t cypher_len = strlen(cypher);
	char transposed[cypher_len];
	int keysize = 0;
	double min_normal_dist = 1000000;
	for (int k = 2; k < 40; k++) {
		//printf("looping, k is %d\n", k);
		int dist = hamming_distance(cypher, cypher + k, k);
		if ((double) dist / (double) k < min_normal_dist) {
			min_normal_dist = (double) dist / (double) k;
			keysize = k;
		}
		//printf("%f\n", dist/k);
	}
	if (keysize == 0) {
		printf("error: didn't find keysize!");
	}
	if (min_normal_dist == 0) {
		printf("error: didn't min_normal_dist");
	}

	for (int i = 0; i < keysize; i++) {
		for (int j = 0; j < ((int) cypher_len) / keysize + 1; j++) {
			printf("%c", cypher[j * keysize + i]);
			if (j * keysize + i <= (int) cypher_len) {
				transposed[i * (cypher_len / keysize) + j] = cypher[j * keysize + i];
			}
		}
	}

	print_by_block(keysize, cypher, cypher_len);
	print_by_block(((int)cypher_len)/keysize, transposed, cypher_len);


	// print_by_block(keysize, cypher);
	// printf("original length: %zu\n", strlen(cypher));
	// printf("transposed length: %zu\n", strlen(transposed));
	// printf("keysize: %d\n", keysize);
	// printf("original: %s, length: %zu\n", cypher, cypher_len);
	// printf("transposed: %s, length: %zu\n", transposed, strlen(transposed));
}
