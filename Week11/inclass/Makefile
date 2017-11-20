FLAGS=-Wall -Wextra -std=c99 -pedantic -Werror
D=-DDEBUG -g
GCC=gcc ${D} ${FLAGS}

default: ht

ht : lib/contracts.h lib/xalloc.h lib/xalloc.c ht.h ht-resize.c ht-test.c
	$(GCC) lib/xalloc.c ht-resize.c ht-test.c -o ht

.PHONY: clean
clean :
	${RM} -rf a.out a.out.dSYM
	${RM} -rf ht ht.dSYM
