#include "../internal.h"
#include <string.h>

int ungetc(int c, FILE *f) {
	if (f->bufpolicy == _IONBF) {
		if (f->bufpos == -1) {
			f->bufpos = (unsigned char)c;
			return 0;
		}
		return EOF;
	}
	if (readMode(f)) return EOF;
	if (f->bufpos == 0) {
		int maxshift = f->bufsize - f->buflim;
		// Reserve 16 places for ungetc
		if (maxshift > 16)maxshift = 16;
		if (f->buflim != f->bufpos)
			memmove(f->buffer + maxshift, f->buffer, f->buflim - f->bufpos);
		f->bufpos += maxshift;
		f->buflim += maxshift;
	}
	f->buffer[--f->bufpos] = c;
	return 0;
}
