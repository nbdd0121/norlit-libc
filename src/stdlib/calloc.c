#include <errno.h>
#include "blockalloc.h"

void *calloc(size_t nmemb, size_t size) {
	void* ret = allocator_calloc(allocator_get_global(), nmemb, size);
	if (!ret) {
		errno = ENOMEM;
	}
	return ret;
}