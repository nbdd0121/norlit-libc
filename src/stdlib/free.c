#include "blockalloc.h"

void free(void *ptr) {
	allocator_free(allocator_get_global(), ptr);
}