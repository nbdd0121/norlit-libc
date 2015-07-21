#include "../internal.h"
#include <stdlib.h>
#include <string.h>

void moveFile(FILE* dst, FILE* src) {
	if (dst->bufmalloc) {
		free(dst->buffer);
	}
	list_remove(&dst->list);
	list_remove(&src->list);
	memcpy(dst, src, sizeof(FILE));
	list_add(&allFiles, &dst->list);
	free(src);
}