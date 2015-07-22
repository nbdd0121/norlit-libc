#include "../internal.h"
#include <string.h>

size_t readBuffer(FILE* restrict f, char* restrict buf, size_t size) {
	if (readMode(f)) return 0;

	size_t totalCount = 0;
	while (size) {
		// If something remains in the buffer
		if (f->bufpos < f->buflim) {
			size_t bufremain = f->buflim - f->bufpos;
			// If buffer has more than we need
			if (bufremain > size) {
				memcpy(buf, f->buffer + f->bufpos, size);
				f->bufpos += size;
				return size + totalCount;
			}
			memcpy(buf, f->buffer + f->bufpos, bufremain);
			totalCount += bufremain;
			buf += bufremain;
			size -= bufremain;
			f->bufpos += bufremain;
		}
		if (size > f->bufsize) {
			return totalCount + readFully(f, buf, size);
		}
		if (readRefill(f)) {
			return totalCount;
		}
	}
	return totalCount;
}
