#include "../internal.h"
#include <stdlib.h>

void freeFile(FILE* f) {
	if (f->bufmalloc) {
		free(f->buffer);
	}
	list_remove(&f->list);
	free(f);
}