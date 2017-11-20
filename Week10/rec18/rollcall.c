#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "xalloc.h"

struct student_header {
	size_t id;
	size_t numDays;
	bool *attended;
};
typedef struct student_header* student;

student student_new(int sId, char *s, int len) {
	student S = xmalloc(sizeof(struct student_header));
	S->numDays = len;
	S->id = sId;
	S->attended = xmalloc(sizeof(bool) * len);	
	return S;
}

void student_free(student S) {
	free(S->attended);
	free(S);
	return;
}	

int main() {
	student S = student_new(6571, "TTTTF", 5);
	student_free(S);
	return 0;
}
