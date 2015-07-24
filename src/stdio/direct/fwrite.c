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