#include "../internal.h"
#include <string.h>
#include <stdlib.h>
#include <errno.h>

FILE *freopen(const char *restrict filename, const char *restrict mode, FILE* restrict f) {
	// Force close old FILE*
	fflush(f);
	f->close(f);

	if (!filename) {
		freeFile(f);
		errno = ENOSYS;
		return NULL;
	}

	FILE* newfile = fopen(filename, mode);
	if (!newfile) {
		freeFile(f);
		return NULL;
	}

	moveFile(f, newfile);
	return f;
}