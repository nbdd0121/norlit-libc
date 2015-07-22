#include "../internal.h"

int fgetc(FILE *f) {
	checkFile(f);

	if (f->bufpolicy == _IONBF) {
		char ch[1];
		if (fread(ch, 1, 1, f)) {
			return ch[0];
		} else {
			return EOF;
		}
	}
	if (readMode(f)) return EOF;
	if (f->bufpos >= f->buflim) {
		if (readRefill(f)) {
			return EOF;
		}
	}
	return (unsigned char)f->buffer[f->bufpos++];
}

strong_alias(fgetc, getc);