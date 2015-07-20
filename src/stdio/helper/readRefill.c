#include "../internal.h"

#include <string.h>

int readRefill(FILE* f) {
	if (readMode(f)) return 1;

	if (f->buflim > f->bufpos) {
		return 0;
	}
	f->bufpos = 0;
	f->buflim = f->read(f, f->buffer + f->buflim, f->bufsize - 1);
	if (f->buflim == 0) {
		return 1;
	}
	return 0;
}
