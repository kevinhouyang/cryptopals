EXES = set_2_challenge_9 set_2_challenge_10
CFLAGS = -Wextra -Wpedantic
LDFLAGS = -lm
UTILS = ../util.c ../util.h
LIBS = ../util.c
OPENSSLPATH = -I/usr/local/opt/openssl/include -L/usr/local/opt/openssl/lib

all: set_2

set_2: set_2_challenge_9 set_2_challenge_10 set_2_challenge_11

set_2_challenge_9: set_2_challenge_9.c
	${CC} ${CFLAGS} ${LDFLAGS} $< -o $@

set_2_challenge_10: set_2_challenge_10.c ${UTILS}
	${CC} ${CFLAGS} ${LDFLAGS} ${LIBS} ${OPENSSLPATH} $< -o $@ -lcrypto

set_2_challenge_11: set_2_challenge_11.c ${UTILS}
	${CC} ${CFLAGS} ${LDFLAGS} ${LIBS} $< -o $@

clean:
	rm -f ${EXES}
