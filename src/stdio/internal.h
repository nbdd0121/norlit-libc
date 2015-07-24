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

#include <stdio.h>
#include <unistd.h>

#include <norlit/util/list.h>

struct _FILE {
	list_t   list;

	size_t (*read) (FILE*, char*, size_t);
	size_t (*write)(FILE*, const char*, size_t);
	off_t  (*seek) (FILE*, off_t, int);
	int    (*close)(FILE*);

	void    *additionalData;

	int      fildes;
	int      flags;

	unsigned bufpolicy: 2;
	// Additional usage: This is used to store default bufpolicy when bufpolicy == 0
	unsigned bufmode  : 2;
	unsigned bufmalloc: 1;

	size_t   bufsize;
	// Additional usage: This is used as pushback of _IONBF stream
	int      bufpos;
	int      buflim;
	char    *buffer;
};

#define BUFMODE_WRITE 1
#define BUFMODE_READ  2

#define FLAG_EOF 1
#define FLAG_ERR 2

#define strong_alias(name, aliasname) __typeof(name) aliasname __attribute__((alias(#name)))

__attribute__((visibility("internal")))
size_t writeFully(FILE* restrict f, const char* restrict buf, size_t len);

__attribute__((visibility("internal")))
int writeMode(FILE* f);

static inline int writeFlush(FILE* f) {
	if (fflush(f) == EOF) return 1;
	return writeMode(f);
}

__attribute__((visibility("internal")))
size_t writeBuffer(FILE* restrict f, const char* restrict buf, size_t len);

__attribute__((visibility("internal")))
size_t readFully(FILE* restrict, char* restrict, size_t);

__attribute__((visibility("internal")))
int readMode(FILE*);

static inline int readFlush(FILE* f) {
	if (fflush(f) == EOF) return 1;
	return readMode(f);
}

__attribute__((visibility("internal")))
size_t readBuffer(FILE* restrict f, char* restrict buf, size_t size);

__attribute__((visibility("internal")))
int readRefill(FILE* f);

__attribute__((visibility("internal")))
int translateFlags(const char *);

__attribute__((visibility("internal")))
extern list_t allFiles;

__attribute__((visibility("internal")))
FILE* allocFile(void);

__attribute__((visibility("internal")))
void freeFile(FILE*);

__attribute__((visibility("internal")))
void moveFile(FILE*, FILE*);

__attribute__((visibility("internal")))
int checkFile(FILE*);

__attribute__((visibility("internal")))
size_t s_read(FILE *f, char *buf, size_t len);