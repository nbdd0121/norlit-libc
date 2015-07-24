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
#include <errno.h>

size_t fread(void *restrict buf, size_t size, size_t nmemb, FILE *restrict f) {
	checkFile(f);

	// If the stream is already in error state, just return error
	if (f->flags & (FLAG_ERR | FLAG_EOF)) {
		errno = EIO; // TODO
		return 0;
	}
	size_t totalSize = nmemb * size;
	if (!totalSize) {
		return nmemb;
	}
	size_t count = 0;
	switch (f->bufpolicy) {
		case _IOLBF:
		case _IOFBF:
			count = readBuffer(f, buf, totalSize);
			break;
		case _IONBF:
			// f->bufpos is used for pushback
			if (f->bufpos != -1) {
				*(unsigned char*)buf = f->bufpos;
				f->bufpos = -1;
				if (totalSize > 1) {
					count = readFully(f, buf + 1, totalSize - 1) + 1;
				} else {
					count = 1;
				}
			} else {
				count = readFully(f, buf, totalSize);
			}
			break;
	}
	return count == totalSize ? nmemb : count / size;
}