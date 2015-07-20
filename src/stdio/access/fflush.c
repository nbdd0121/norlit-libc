#include "../internal.h"

int fflush(FILE *f) {
	if (f->bufpolicy == _IONBF) return 0;
	if (f->write(f, f->buffer, f->bufpos) != f->bufpos) {
		f->flags |= FLAG_ERR;
		return EOF;
	}
	f->bufmode = 0;
	f->bufpos = 0;
	return 0;
}