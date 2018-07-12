EXES = xor_test
CFLAGS = -Wextra -Wpedantic
LDFLAGS = -lm
UTILS = util.c util.h
LIBS = util.c
OPENSSLPATH = -I/usr/local/opt/openssl/include -L/usr/local/opt/openssl/lib

all: test

test: xor_test.c ${UTILS}
	${CC} ${CFLAGS} ${LDFLAGS} ${LIBS} $< -o $@

junk: test.c
	${CC} ${CFLAGS} ${LDFLAGS} ${LIBS} $< -o $@

clean:
	rm -f ${EXES}
