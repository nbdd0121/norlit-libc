#include "../internal.h"
#include <stdlib.h>

int fclose(FILE* f) {
	fflush(f);
	if (f->close(f)) {
		return EOF;
	}
	if (f->bufmalloc) {
		free(f->buffer);
	}
	free(f);
	return 0;
}