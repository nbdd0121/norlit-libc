/*
 * Copyright (c) 2015, Gary Guo 
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met: 
 * 
 *  * Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer. 
 *  * Redistributions in binary form must reproduce the above copyright 
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the distribution. 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND ANY 
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR ANY 
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY 
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH 
 * DAMAGE. 
 */

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