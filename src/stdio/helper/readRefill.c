#include "../internal.h"

#include <string.h>

int readRefill(FILE* f) {
	if (f->bufpos != 0) {
		memmove(f->buffer, f->buffer + f->bufpos, f->buflim - f->bufpos);
		f->buflim -= f->bufpos;
		f->bufpos = 0;
	}
	f->buflim = f->read(f, f->buffer + f->buflim, f->bufsize - f->buflim);
	if (f->buflim == 0) {
		return 1;
	}
	return 0;
}
