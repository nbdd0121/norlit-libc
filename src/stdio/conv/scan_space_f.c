#include "internal.h"
#include <ctype.h>

int scan_space_f(FILE* f) {
	int ch;
	int count = 0;
	while (isspace(ch = fgetc(f))) count++;
	ungetc(ch, f);
	return count;
}