#include <string.h>

void *memccpy(void * restrict s1, const void * restrict s2, int c, size_t n) {
	if (n) {
		unsigned char byte = (unsigned char)c;
		unsigned char *dst = s1;
		const unsigned char *src = s2;
		size_t i;
		for (i = 0; *src != byte && i < n; i++, dst++, src++) {
			*dst = *src;
		}
		if (i < n) {
			*dst = c;
			return dst + 1;
		}
	}
	return NULL;
}