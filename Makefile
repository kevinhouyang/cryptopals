set_1_challenge_1: set_1_challenge_1.c base64.c base64.h
	${CC} -Wextra -Wpedantic $< base64.c -o $@

set_1_challenge_2: set_1_challenge_2.c base64.c base64.h
	${CC} -Wextra -Wpedantic $< base64.c -o $@
