LIBS = util.c
EXES = set_1_challenge_1 set_1_challenge_2 set_1_challenge_3
CFLAGS = -Wextra -Wpedantic
LDFLAGS = -lm

all: set_1

set_1_challenge_1: set_1_challenge_1.c *.c *.h
	${CC} ${CFLAGS} ${LDFLAGS} $< ${LIBS} -o $@

set_1_challenge_2: set_1_challenge_2.c *.c *.h
	${CC} ${CFLAGS} ${LDFLAGS} $< ${LIBS} -o $@

set_1_challenge_3: set_1_challenge_3.c *.c *.h
	${CC} ${CFLAGS} ${LDFLAGS} $< ${LIBS} -o $@

set_1_challenge_4: set_1_challenge_3
	@echo nothing to compile for $@

set_1: set_1_challenge_1 set_1_challenge_2 set_1_challenge_3 set_1_challenge_4

clean:
	rm -f ${EXES}
