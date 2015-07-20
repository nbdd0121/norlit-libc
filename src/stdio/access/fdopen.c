#include "../internal.h"
#include <string.h>
#include <stdlib.h>
#include <errno.h>

static size_t fd_read(FILE* f, char* buf, size_t len) {
	ssize_t count = read(f->fildes, buf, len);
	if (count == -1) {
		f->flags |= FLAG_ERR;
		return 0;
	} else if (count == 0) {
		f->flags |= FLAG_EOF;
		return 0;
	}
	return count;
}

static size_t fd_write(FILE* f, const char* buf, size_t len) {
	ssize_t count = write(f->fildes, buf, len);
	if (count == -1) {
		f->flags |= FLAG_ERR;
		return 0;
	}
	return count;
}

static off_t fd_seek(FILE* f, off_t off, int dir) {
	return lseek(f->fildes, off, dir);
}

FILE *fdopen(int fildes, const char *mode) {
	if (!strchr("rwa", mode[0])) {
		errno = EINVAL;
		return NULL;
	}

	FILE* f = malloc(sizeof(FILE));
	if (!f) {
		return NULL;
	}

	memset(f, 0, sizeof(FILE));

	f->read = fd_read;
	f->write = fd_write;
	f->seek = fd_seek;
	f->fildes = fildes;

	return f;
}