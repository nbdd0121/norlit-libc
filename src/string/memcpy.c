#include <string.h>

void *memcpy(void * restrict s1, const void * restrict s2, size_t n) {
	char *dst = s1;
	const char *src = s2;
	for (size_t i = 0; i < n; i++, dst++, src++) {
		*dst = *src;
	}
	return s1;
}