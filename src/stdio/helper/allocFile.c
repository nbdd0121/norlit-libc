#include "../internal.h"
#include <stdlib.h>
#include <string.h>

list_t allFiles = {&allFiles, &allFiles};

FILE* allocFile(void) {
	FILE* f = malloc(sizeof(FILE));
	if (!f) {
		return NULL;
	}
	memset(f, 0, sizeof(FILE));
	list_add(&allFiles, &f->list);
	return f;
}