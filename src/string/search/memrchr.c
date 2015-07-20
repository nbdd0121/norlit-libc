#include <string.h>

void *memrchr(const void *s, int c, size_t n) {
	unsigned char byte = (unsigned char)c;
	const unsigned char* start = s;
	for (const unsigned char* mem = s + n - 1; mem >= start; mem--) {
		if (*mem == byte) {
			return (void *)mem;
		}
	}
	return NULL;
}