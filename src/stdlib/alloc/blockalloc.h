#ifndef _NORLIT_LIBC_STDLIB_BLOCKALLOC_H
#define _NORLIT_LIBC_STDLIB_BLOCKALLOC_H

#include <stddef.h>

typedef struct allocator_t allocator_t;

__attribute__((visibility("internal")))
allocator_t *allocator_create(void);
__attribute__((visibility("internal")))
void allocator_free(allocator_t *al, void *addr);
__attribute__((visibility("internal")))
void *allocator_malloc(allocator_t *al, size_t size);
__attribute__((visibility("internal")))
void *allocator_calloc(allocator_t *al, size_t nmemb, size_t size);
__attribute__((visibility("internal")))
void *allocator_realloc(allocator_t *al, void *addr, size_t size);
__attribute__((visibility("internal")))
void *allocator_aligned_alloc(allocator_t *al, size_t alignment, size_t size);

__attribute__((visibility("internal")))
allocator_t* allocator_get_global();

#endif