#include <errno.h>
#include "blockalloc.h"

void *realloc(void *ptr, size_t size) {
	void* ret = allocator_realloc(allocator_get_global(), ptr, size);
	if (!ret) {
		errno = ENOMEM;
	}
	return ret;
}