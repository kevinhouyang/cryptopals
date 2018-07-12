#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../util.h"

/*
 * traverse the input string in steps of 3
 * -> produce 2 base64 characters per step
 * -> move the hex characters into a string of bits
 * -> mask in groups of 6 bits
 * -> output base64 characters according to table lookup
*/
int main(int argc, char ** argv)
{
	if (argc != 2) {
		printf("error: provide an input string");
		return EXIT_FAILURE;
	}

	char * in = argv[1];
	size_t len = strlen(in);
	int i;
	char * result = malloc(sizeof (char) * strlen(in));
	int counter = 0;

	for (i = 0; i < (int) strlen(in); i+= 3) { // 3 hex characters...
		hex_to_base64(result + counter, in + i);
		counter += 2; // ...is equivalent to 2 base64 characters
	}
	result[counter] = '\0';
	printf("%s\n", result);
	free(result);
	return 0;
}
