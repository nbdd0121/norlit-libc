#include "../internal.h"

#include <string.h>
#include <errno.h>

size_t fwrite(const void *restrict buf, size_t size, size_t nmemb, FILE *restrict f) {
	checkFile(f);

	// If the stream is already in error state, just return error
	if (f->flags & FLAG_ERR) {
		errno = EIO; // TODO
		return 0;
	}
	size_t writeSize = nmemb * size;
	if (!writeSize) {
		return nmemb;
	}
	size_t count = 0;
	switch (f->bufpolicy) {
		case _IOLBF: {
			const char* endptr = memrchr(buf, '\n', writeSize);
			// If no \n, write everything to buffer
			if (!endptr) {
				count = writeBuffer(f, buf, writeSize);
				break;
			}
			size_t writeCount = endptr - (char*)buf + 1;
			count = writeBuffer(f, buf, writeCount);
			if (count != writeCount) break;
			if (writeFlush(f)) break;
			count += writeBuffer(f, buf + writeCount, writeSize - writeCount);
			break;
		}
		case _IOFBF:
			count = writeBuffer(f, buf, writeSize);
			break;
		case _IONBF:
			count = writeFully(f, buf, writeSize);
			break;
	}
	return count == writeSize ? nmemb : count / size;
}