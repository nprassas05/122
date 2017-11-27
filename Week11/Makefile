# call with make D='' to turn off debug mode
FLAGS=-Wall -Wextra -std=c99 -pedantic -Werror
D=-DDEBUG -g
GCC=gcc ${D} ${FLAGS}

default: ht

ht : lib/contracts.h lib/xalloc.h lib/xalloc.c ht.h ht.c ht-test.c
	$(GCC) lib/xalloc.c ht.c ht-test.c -o ht

sort:	lib/contracts.h lib/xalloc.h lib/xalloc.c sort.h sort.c sort-test.c
		$(GCC) lib/xalloc.c sort.c sort-test.c -o sort

sort-inclass:	lib/contracts.h lib/xalloc.h lib/xalloc.c sort.h sort-inclass.c sort-test-inclass.c
		$(GCC) lib/xalloc.c sort-inclass.c sort-test-inclass.c -o sort

clean :
	${RM} -rf a.out a.out.dSYM
	${RM} -rf ht ht.dSYM
	${RM} -rf sort sort.dSYM
