#include "../internal.h"

#include <string.h>
#include <errno.h>

size_t fread(void *restrict buf, size_t size, size_t nmemb, FILE *restrict f) {
	// If the stream is already in error state, just return error
	if (f->flags & (FLAG_ERR | FLAG_EOF)) {
		errno = EIO; // TODO
		return 0;
	}
	size_t totalSize = nmemb * size;
	if (!totalSize) {
		return nmemb;
	}
	size_t count;
	switch (f->bufpolicy) {
		case _IOLBF:
		case _IOFBF:
			count = readBuffer(f, buf, totalSize);
			break;
		case 0:
		case _IONBF:
			count = readFully(f, buf, totalSize);
			break;
	}
	return count == totalSize ? nmemb : count / size;
}