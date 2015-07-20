#include "../internal.h"
#include <string.h>

int fgetc(FILE *f) {
	char ch[1];
	if (fread(ch, 1, 1, f)) {
		return ch[0];
	} else {
		return EOF;
	}
}

strong_alias(fgetc, getc);