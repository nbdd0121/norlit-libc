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
#include <limits.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>

typedef struct {
	char* buf;
	size_t size;
} memfile_t;

static size_t sn_write(FILE *f, const char *buf, size_t len) {
	memfile_t* memf = f->additionalData;
	size_t toWrite = len > memf->size ? memf->size : len;
	memcpy(memf->buf, buf, toWrite);
	memf->buf += toWrite;
	memf->size -= toWrite;
	return len;
}

int vsnprintf(char *restrict s, size_t n, const char *restrict fmt, va_list ap) {
	memfile_t memf = {.buf = s, .size = n};
	FILE f = { .write = sn_write, .bufpolicy = _IONBF, .additionalData = &memf};
	int ret = vfprintf(&f, fmt, ap);
	if (ret < 0) {
		return ret;
	}
	if ((size_t)ret < n) {
		s[ret] = 0;
	} else {
		s[n - 1] = 0;
	}
	return ret;
}