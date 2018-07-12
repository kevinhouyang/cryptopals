#!/bin/sh -e

CIPHERTEXT="1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"
make set_1_challenge_3
./set_1_challenge_3 $CIPHERTEXT | sort -nr | head -1
