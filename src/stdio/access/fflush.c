#include "../internal.h"

#include <assert.h>

int fflush(FILE *f) {
	if (f) {
		if (!f->bufpolicy) return 0;
		if (f->bufpolicy == _IONBF) {
			if (f->bufpos) {
				f->seek(f, -1, SEEK_CUR);
			}
			return 0;
		}
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

	int ret = 0;
	list_forEach(&allFiles, f, FILE, list) {
		if (fflush(f)) ret = EOF;
	}
	return ret;
}