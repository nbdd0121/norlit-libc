#include "../internal.h"
#include <string.h>

int fputc(int c, FILE *f) {
	char ch[1] = {(char)c};
	return (int)fwrite(ch, 1, 1, f) - 1;
}

strong_alias(fputc, putc);