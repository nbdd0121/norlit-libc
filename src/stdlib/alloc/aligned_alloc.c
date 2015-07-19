#include <errno.h>
#include "blockalloc.h"
#include <norlit/util/log2.h>

void *aligned_alloc(size_t alignment, size_t size) {
	if ((1 << log2_int(alignment)) != alignment) {
		errno = EINVAL;
		return NULL;
	}
	void* ret = allocator_aligned_alloc(allocator_get_global(), alignment, size);
	if (!ret) {
		errno = ENOMEM;
	}
	return ret;
}
