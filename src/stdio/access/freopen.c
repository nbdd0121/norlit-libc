#include "../internal.h"
#include <string.h>
#include <stdlib.h>
#include <errno.h>

FILE *freopen(const char *restrict filename, const char *restrict mode, FILE* restrict f) {
	// Force close old FILE*
	fflush(f);
	f->close(f);
	if (f->bufmalloc) {
		free(f->buffer);
	}

	if (!filename) {
		free(f);
		errno = ENOSYS;
		return NULL;
	}

	FILE* newfile = fopen(filename, mode);
	if (!newfile) {
		free(f);
		return NULL;
	}

	memcpy(f, newfile, sizeof(FILE));
	free(newfile);
	return f;
}