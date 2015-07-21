#include "../internal.h"
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>

typedef struct {
	char* buf;
	size_t size;
	int mode;
	off_t pos;
} memfile_t;

static size_t mem_read(FILE* f, char* buf, size_t len) {
	memfile_t* memf = f->additionalData;
	if ((memf->mode & O_ACCMODE) == O_WRONLY) {
		errno = EIO;
		f->flags |= FLAG_ERR;
		return 0;
	}
	size_t toRead = memf->size - (size_t)memf->pos;
	if (toRead > len) {
		toRead = len;
	}
	if (toRead == 0) {
		f->flags |= FLAG_EOF;
		return 0;
	}
	memcpy(buf, memf->buf + (size_t)memf->pos, toRead);
	memf->pos += toRead;
	return toRead;
}

static size_t mem_write(FILE* f, const char* buf, size_t len) {
	memfile_t* memf = f->additionalData;
	if ((memf->mode & O_ACCMODE) == O_RDONLY) {
		errno = EIO;
		f->flags |= FLAG_ERR;
		return 0;
	}
	size_t toWrite = memf->size - (size_t)memf->pos;
	if (memf->mode & O_APPEND) {
		memf->pos += strnlen(memf->buf + (size_t)memf->pos, toWrite);
		toWrite = memf->size - (size_t)memf->pos;
	}
	if (toWrite > len) {
		toWrite = len;
	}
	if (toWrite == 0) {
		errno = EFBIG;
		f->flags |= FLAG_ERR;
		return 0;
	}
	memcpy(memf->buf + (size_t)memf->pos, buf, toWrite);
	memf->pos += toWrite;
	return toWrite;
}

static off_t mem_seek(FILE* f, off_t off, int dir) {
	memfile_t* memf = f->additionalData;
	off_t destPos;
	if (dir == SEEK_SET) {
		destPos = off;
	} else if (dir == SEEK_CUR) {
		destPos = memf->pos + off;
	} else {
		destPos = memf->size + off;
	}
	if (destPos < 0 || destPos >= memf->size) {
		errno = EFBIG;
		return -1;
	}
	return memf->pos = destPos;
}

static int mem_close(FILE* f) {
	free(f->additionalData);
	return 0;
}

FILE *fmemopen(void *restrict buf, size_t size, const char *restrict mode) {
	int modeFlags = translateFlags(mode);
	if (modeFlags < 0) {
		errno = EINVAL;
		return NULL;
	}

	memfile_t* memf = malloc(sizeof(memfile_t));
	if (!memf) {
		return NULL;
	}

	FILE* f = allocFile();
	if (!f) {
		free(memf);
		return NULL;
	}

	f->read = mem_read;
	f->write = mem_write;
	f->seek = mem_seek;
	f->close = mem_close;

	f->bufmode = _IONBF;

	memf->buf = buf;
	memf->size = size;
	memf->mode = modeFlags;
	memf->pos = 0;

	f->additionalData = memf;
	return f;
}