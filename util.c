#include "util.h"
#include <stdio.h>
#include <stdlib.h>

char hex_to_int(char);
char int_to_base64(int);

void hex_to_base64(char *dest, char *in)
{
	int a, b, c;

	a = hex_to_int(in[0]);
	b = hex_to_int(in[1]);
	c = hex_to_int(in[2]);

	unsigned d = a << 8 | b << 4 | c;

	/*
	eg.
	a = 1111
	b = 0000
	c = 1000
	d = 111100001000
	*/

	unsigned mask1 = 63; // mask1 = 000000111111
	unsigned mask2 = mask1 << 6; // mask2 = 111111000000

	int e = (d & mask2) >> 6; // only preserve first 6 bits, shift right
	int f = d & mask1; // only preserve last 6 bits

	char g = int_to_base64(e); // convert values to base64 encoding
	char h = int_to_base64(f);

	dest[0] = g; // store result in passed array
	dest[1] = h;

	return;
}

char hex_to_int(char c) {
	if (c >= '0' && c <= '9') {
		return c - '0';
	} else if (c >= 'a' && c <= 'z') {
		return c - 'a' + 10;
	} else if (c >= 'A' && c <= 'Z') {
		return c - 'A' + 10;
	} else {
		return -1;
	}
}

void hex_to_bytes(char * dest, char * src, size_t len)
{
	char a, b;
	for (size_t i = 0; i < len; i += 2) { // basically concatenating 4 + 4 bits
		a = hex_to_int(src[i]);
		b = hex_to_int(src[i + 1]);
		dest[i / 2] = a << 4 | b;
	}
}

char int_to_hex(int i)
{
	if (i >= 0 && i <= 9) {
		return i + '0';
	} else if (i >= 10 && i <= 15) {
		return i + 'a' - 10;
	} else {
		return -1;
	}
}

char int_to_base64(int i)
{
	if (i >= 0 && i <= 25) {
		return i + 'A'; //
	} else if (i >= 26 && i <= 51) {
		return i + 'a' - 26;
	} else if (i >= 52 && i <= 61) {
		return i + '0' - 52;
	} else if (i == 62) {
		return '+';
	} else if (i == 63) {
		return '/';
	} else {
		return -1;
	}
}

long long xor(long long a, long long b)
{
	return ~(a & b) & (a | b);
}

void single_byte_xor(char byte, char * dest, char * src, size_t len)
{
	for (size_t i = 0; i < len; i++)
		dest[i] = xor(byte, src[i]);
}

void cbc_xor(unsigned char *iv, unsigned char *dest, size_t blocksize)
{

	for (size_t i = 0; i < blocksize; i++) {
		printf("%x xor'd with %x ", iv[i], dest[i]);
		dest[i] = iv[i] ^ dest[i];
		//xor(iv[i], dest[i]);
		printf("produces %x\n", dest[i]);
	}
}


int plaintext_to_lookup_index(char c)
{
	if (c >= 'A' && c <= 'Z') {
		return c - 'A';
	} else if (c >= 'a' && c <= 'z') {
		return c - 'a';
	} else {
		return 26;
	}

}
/*
 * "score" a string for likelihood it's English text. higher scores are
 * more likely (maybe?).
 */
int score_english_plaintext(char *str)
{

	static const float lookup[27] = {
		8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966,
		0.153, 0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987,
 		6.327, 9.056, 2.758, 0.978, 2.360, 0.150, 1.974, 0.074, 0
	};

	int score = 0;
	for (size_t i = 0; i < SSIZE_MAX && str[i] != '\0'; i++) {

		if (!isprint(str[i]) || iscntrl(str[i]))
			score = MIN(score, score - 20);
		else if (islower(str[i]))
			score = MAX(score, score + 20);
		else if (isupper(str[i]))
			score = MAX(score, score + 10);
		else if (isdigit(str[i]))
			score = MAX(score, score + 5);
		else if (ispunct(str[i]))
			score = MIN(score, score - 1);

		score += lookup[plaintext_to_lookup_index(str[i])];
	}
	return score;
}

/*
We need 16 random bytes = 32 nibbles.
Each nibble has 4 bits so 2^4 = 16 possible values, which we select from randomly
 */
void generate_random_key(char *key)
{
	for (int i = 0; i < 32; i++) {
		key[i] = int_to_hex(arc4random_uniform(16));
	}
}
//
// void encryption_oracle()
// {
//
// }
