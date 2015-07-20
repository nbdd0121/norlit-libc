#include "../internal.h"

size_t readFully(FILE* restrict f, char* restrict buf, size_t len) {
	size_t cntProcessed = 0;
	while (len) {
		size_t count = f->read(f, buf, len);
		if (count == 0) {
			return cntProcessed;
		}
		len -= count;
		cntProcessed += count;
		buf += count;
	}
	return cntProcessed;
}
