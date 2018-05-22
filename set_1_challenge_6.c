#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

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
		sum += character_hamming_distance(a[i], b[i]);
	}
	return sum;
}

int main(int argc, char ** argv)
{
	if (argc != 3) {
		printf("error: provide two arguments");
		return EXIT_FAILURE;
	}
	char *a = argv[1];
	char *b = argv[2];
	size_t a_len = strlen(a);
	size_t b_len = strlen(b);
	if (a_len != b_len) {
		printf("error: strings must be equal length");
		return EXIT_FAILURE;
	}
	int distance = hamming_distance(a, b, a_len);
	printf("%d\n", distance);
}
