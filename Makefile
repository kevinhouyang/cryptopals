LIBS = util.c
EXES = set_1_challenge_1 set_1_challenge_2

all: set_1

set_1_challenge_1: set_1_challenge_1.c *.c *.h
	${CC} -Wextra -Wpedantic $< ${LIBS} -o $@

set_1_challenge_2: set_1_challenge_2.c *.c *.h
	${CC} -Wextra -Wpedantic $< ${LIBS} -o $@

set_1: set_1_challenge_1 set_1_challenge_2

clean:
	rm -f ${EXES}
