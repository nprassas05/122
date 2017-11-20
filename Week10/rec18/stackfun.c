#include <stdio.h>

void print_substrings(char *p) {
	char *sub = p;
	while (*sub != '\0') {
		printf("%s\n", sub);
		sub++;
	}
}

int main() {
	char *s = "Nivedita";
	print_substrings(s);
	return 0;
}
