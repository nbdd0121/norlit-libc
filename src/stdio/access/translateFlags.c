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
#include <fcntl.h>
#include <stdbool.h>

int translateFlags(const char *mode) {
	int flags = 0;
	switch (mode[0]) {
		case 'r':
			flags = O_RDONLY;
			break;
		case 'w':
			flags |= O_WRONLY | O_CREAT | O_TRUNC;
			break;
		case 'a':
			flags |= O_WRONLY | O_CREAT | O_APPEND;
			break;
		default:
			return -1;
	}

	bool b = false;
	for (int i = 1; mode[i]; i++) {
		switch (mode[i]) {
			case '+':
				if ((flags & O_ACCMODE) == O_RDWR)
					return -1;
				flags = (flags & ~O_ACCMODE) | O_RDWR;
				break;
			case 'b':
				if (b)
					return -1;
				b = true;
				break;
			case 'x':
				if ((flags & O_EXCL) || mode[0] != 'w')
					return -1;
				flags |= O_EXCL;
				break;
			default:
				return -1;
		}
	}

	return flags;
}