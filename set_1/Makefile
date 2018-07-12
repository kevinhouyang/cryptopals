LIBS = ../util.c
EXES = set_1_challenge_1 set_1_challenge_2 set_1_challenge_3 set_1_challenge_5 set_1_challenge_6 set_1_challenge_7 set_1_challenge_8
CFLAGS = -Wextra -Wpedantic
LDFLAGS = -lm
OPENSSLPATH = -I/usr/local/opt/openssl/include -L/usr/local/opt/openssl/lib
UTILS = ../util.c ../util.h

all: set_1

set_1: set_1_challenge_1 set_1_challenge_2 set_1_challenge_3 set_1_challenge_4 set_1_challenge_5 set_1_challenge_6 set_1_challenge_7 set_1_challenge_8

set_1_challenge_1: set_1_challenge_1.c ${UTILS}
	${CC} ${CFLAGS} ${LDFLAGS} $< ${LIBS} -o $@

set_1_challenge_2: set_1_challenge_2.c ${UTILS}
	${CC} ${CFLAGS} ${LDFLAGS} $< ${LIBS} -o $@

set_1_challenge_3: set_1_challenge_3.c ${UTILS}
	${CC} ${CFLAGS} ${LDFLAGS} $< ${LIBS} -o $@

set_1_challenge_4: set_1_challenge_3
	@echo nothing to compile for $@

set_1_challenge_5: set_1_challenge_5.c ${UTILS}
	${CC} ${CFLAGS} ${LDFLAGS} $< ${LIBS} -o $@

set_1_challenge_6: set_1_challenge_6.c ${UTILS}
	${CC} ${CFLAGS} ${LDFLAGS} $< ${LIBS} -o $@

set_1_challenge_7: set_1_challenge_7.c
	${CC} ${CFLAGS} ${OPENSSLPATH} ${LDFLAGS} $< -o $@ -lssl -lcrypto

set_1_challenge_8: set_1_challenge_8.c
	${CC} ${CFLAGS} ${LDFLAGS} $< -o $@

clean:
	rm -f ${EXES}
