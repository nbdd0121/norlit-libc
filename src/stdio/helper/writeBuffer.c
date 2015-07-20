#include "../internal.h"
#include <string.h>

size_t writeBuffer(FILE* restrict f, const char* restrict buf, size_t size) {
	if (writeMode(f)) return 0;

	// If we run out of buffer space
	if (f->bufpos + size > f->bufsize) {
		if (f->bufpos != 0 && writeFlush(f)) return 0;
		// If we cannot write to buffer fully
		if (size > f->bufsize) {
			return writeFully(f, buf, size);
		}
	}
	// Just copy to buffer
	memcpy(f->buffer + f->bufpos, buf, size);
	f->bufpos += size;
	return size;
}
