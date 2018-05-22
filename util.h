#ifndef BASE64_H
#define BASE64_H
#include <stddef.h>
#include <limits.h>
#include <ctype.h>
void hex_to_base64(char *, char*);
char hex_to_int(char);
char int_to_hex(int);
long long xor(long long, long long);
void single_byte_xor(char, char *, char *, size_t);
void hex_to_bytes(char *, char *, size_t);
int score_english_plaintext(char *);
#endif
