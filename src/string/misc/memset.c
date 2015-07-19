#include <string.h>

void *memset(void *s, int c, size_t n) {
	unsigned char byte = (unsigned char)c;
	unsigned char* mem = s;
	for (unsigned char* end = s + n; mem < end; mem++) {
		*mem = byte;
	}
	return s;
}