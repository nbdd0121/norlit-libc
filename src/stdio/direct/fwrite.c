#include "../internal.h"

#include <string.h>
#include <errno.h>
#include <assert.h>

static int writeMode(FILE* f) {
	if (f->bufmode == BUFMODE_WRITE)return 0;
	if (f->bufmode != BUFMODE_WRITE) {
		if (fflush(f) == EOF) {
			return 1;
		}
	}
	f->bufmode = BUFMODE_WRITE;
	return 0;
}

static int flushWrite(FILE* f) {
	if (fflush(f) == EOF) return 1;
	f->bufmode = BUFMODE_WRITE;
	return 0;
}

static int bufferedWrite(const void *restrict buf, size_t size, FILE *restrict f) {
	if (writeMode(f)) return 0;

	// If we run out of buffer space
	if (f->bufpos + size > f->bufsize) {
		if (flushWrite(f)) return 0;
		// If we cannot write to buffer fully
		if (size > f->bufsize) {
			return f->write(f, buf, size);
		}
	}
	// Just copy to buffer
	memcpy(f->buffer + f->bufpos, buf, size);
	f->bufpos += size;
	return size;
}

size_t fwrite(const void *restrict buf, size_t size, size_t nmemb, FILE *restrict f) {
	// If the stream is already in error state, just return error
	if (f->flags & FLAG_ERR) {
		errno = EIO; // TODO
		return 0;
	}
	size_t writeSize = nmemb * size;
	if (!writeSize) {
		return nmemb;
	}
	size_t count;
	switch (f->bufpolicy) {
		case _IOLBF: {
			const char* endptr = memrchr(buf, '\n', writeSize);
			// If no \n, write everything to buffer
			if (!endptr) {
				count = bufferedWrite(buf, writeSize, f);
				break;
			}
			size_t writeCount = endptr - (char*)buf + 1;
			count = bufferedWrite(buf, writeCount, f);
			if (count != writeCount) break;
			if (flushWrite(f)) break;
			count += bufferedWrite(buf + writeCount, writeSize - writeCount, f);
			break;
		}
		case 0:
			setvbuf(f, NULL, _IOFBF, BUFSIZ);
		case _IOFBF:
			count = bufferedWrite(buf, writeSize, f);
			break;
		case _IONBF:
			count = f->write(f, buf, writeSize);
			break;
	}
	return count == writeSize ? nmemb : count / size;
}