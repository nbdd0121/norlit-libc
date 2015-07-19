#include <string.h>

void *memchr(const void *s, int c, size_t n) {
	unsigned char byte = (unsigned char)c;
	const unsigned char* mem = s;
	for (const unsigned char* end = s + n; mem < end; mem++) {
		if (*mem == byte) {
			return (void *)mem;
		}
	}
	return NULL;
}