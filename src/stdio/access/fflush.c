#include "../internal.h"

#include <assert.h>

int fflush(FILE *f) {
	if (f->bufpolicy == _IONBF) return 0;
	if (f->bufmode == BUFMODE_WRITE) {
		if (writeFully(f, f->buffer, f->bufpos) != f->bufpos) {
			return EOF;
		}
	} else if (f->bufmode == BUFMODE_READ) {
		if (f->bufpos < f->buflim) {
			f->seek(f, f->bufpos - f->buflim, SEEK_CUR);
		}
	}
	f->bufmode = 0;
	f->bufpos = 0;
	f->buflim = 0;
	return 0;
}