LIBS = util.c
EXES = set_1_challenge_1 set_1_challenge_2 set_1_challenge_3 set_1_challenge_5 set_1_challenge_6
CFLAGS = -Wextra -Wpedantic
LDFLAGS = -lm

all: set_1

set_1: set_1_challenge_1 set_1_challenge_2 set_1_challenge_3 set_1_challenge_4 set_1_challenge_5 set_1_challenge_6

set_1_challenge_1: set_1_challenge_1.c util.c util.h
	${CC} ${CFLAGS} ${LDFLAGS} $< ${LIBS} -o $@

set_1_challenge_2: set_1_challenge_2.c util.c util.h
	${CC} ${CFLAGS} ${LDFLAGS} $< ${LIBS} -o $@

set_1_challenge_3: set_1_challenge_3.c util.c util.h
	${CC} ${CFLAGS} ${LDFLAGS} $< ${LIBS} -o $@

set_1_challenge_4: set_1_challenge_3
	@echo nothing to compile for $@

set_1_challenge_5: set_1_challenge_5.c util.c util.h
	${CC} ${CFLAGS} ${LDFLAGS} $< ${LIBS} -o $@

set_1_challenge_6: set_1_challenge_6.c util.c util.h
	${CC} ${CFLAGS} ${LDFLAGS} $< ${LIBS} -o $@

clean:
	rm -f ${EXES}
