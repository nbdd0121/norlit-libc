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

static size_t fd_read(FILE* f, char* buf, size_t len) {
	ssize_t count = read(f->fildes, buf, len);
	if (count < 0) {
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
	if (count <= 0) {
		f->flags |= FLAG_ERR;
		return 0;
	}
	return count;
}

static off_t fd_seek(FILE* f, off_t off, int dir) {
	return lseek(f->fildes, off, dir);
}

static int fd_close(FILE* f) {
	return close(f->fildes);
}

FILE *fdopen(int fildes, const char *mode) {
	if (translateFlags(mode) < 0) {
		errno = EINVAL;
		return NULL;
	}

	FILE* f = allocFile();
	if (!f) {
		return NULL;
	}

	f->read = fd_read;
	f->write = fd_write;
	f->seek = fd_seek;
	f->close = fd_close;

	f->fildes = fildes;

	f->bufmode = _IOFBF;

	return f;
}