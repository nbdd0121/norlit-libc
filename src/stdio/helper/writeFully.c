#include "../internal.h"

size_t writeFully(FILE* restrict f, const char* restrict buf, size_t len) {
	size_t cntProcessed = 0;
	while (len) {
		size_t count = f->write(f, buf, len);
		if (count == 0) {
			return cntProcessed;
		}
		len -= count;
		cntProcessed += count;
		buf += count;
	}
	return cntProcessed;
}
