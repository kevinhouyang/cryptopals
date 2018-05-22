LIBS = util.c
EXES = set_1_challenge_1 set_1_challenge_2 set_1_challenge_3
CFLAGS = -Wextra -Wpedantic

all: set_1

set_1_challenge_1: set_1_challenge_1.c *.c *.h
	${CC} ${CFLAGS} $< ${LIBS} -o $@

set_1_challenge_2: set_1_challenge_2.c *.c *.h
	${CC} ${CFLAGS} $< ${LIBS} -o $@

set_1_challenge_3: set_1_challenge_3.c *.c *.h
	${CC} ${CFLAGS} $< ${LIBS} -o $@

set_1: set_1_challenge_1 set_1_challenge_2 set_1_challenge_3

clean:
	rm -f ${EXES}
