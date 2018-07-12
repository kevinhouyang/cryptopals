#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../util.h"

#define BUFLEN 100

int main(int argc, char ** argv)
{
	if (argc != 2) {
		printf("error: provide a key as an arugment");
		return EXIT_FAILURE;
	}
	size_t bytes_read, i;
	char buf[BUFLEN];
	char *key = argv[1];
	size_t key_length = strlen(key);
	size_t counter = 0;
	printf("key is: %s, (length %zd)\n", key, key_length);
	while((bytes_read = fread(buf, sizeof(char), BUFLEN, stdin)) > 0) {
		for (i = 0; i < bytes_read; i++) {
			printf("%02x", (char) xor(key[counter], buf[i]));
			counter = (counter + 1) % key_length;
		}
	}
	printf("\n");
	if (ferror(stdin)) {
		perror("reading stdin");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
