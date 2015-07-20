#include "../internal.h"

#include <stdlib.h>
#include <errno.h>

int setvbuf(FILE * restrict f, char * restrict buf, int mode, size_t size) {
	if (f->bufpolicy != 0) {
		errno = EINVAL;
		return 1;
	}
	if (mode == _IONBF) {
		f->bufpolicy = mode;
		// In _IONBF mode, bufpos is used for pushbacks
		f->bufpos = -1;
		return 0;
	}
	if (mode != _IOLBF && mode != _IOFBF) {
		errno = EINVAL;
		return 1;
	}
	if (!buf) {
		buf = malloc(size);
		if (!buf) {
			return 1;
		}
		f->bufmalloc = 1;
	}
	f->bufpolicy = mode;
	f->bufsize = size;
	f->buffer = buf;
	return 0;
}