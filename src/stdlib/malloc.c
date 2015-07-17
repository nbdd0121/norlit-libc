#include <assert.h>
#include <errno.h>
#include "blockalloc.h"

__attribute__((visibility("hidden")))
allocator_t* allocator_get_global() {
	static allocator_t* allocator = NULL;
	if (!allocator) {
		allocator = allocator_create();
		assert(allocator);
	}
	return allocator;
}

void *malloc(size_t size) {
	void* ret = allocator_malloc(allocator_get_global(), size);
	if (!ret) {
		errno = ENOMEM;
	}
	return ret;
}