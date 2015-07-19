#include <errno.h>
#include "blockalloc.h"
#include <norlit/util/log2.h>

int posix_memalign(void **memptr, size_t alignment, size_t size) {
	if ((1 << log2_int(alignment)) != alignment) {
		return EINVAL;
	}
	*memptr = allocator_aligned_alloc(allocator_get_global(), alignment, size);
	if (!*memptr) {
		return ENOMEM;
	}
	return 0;
}
