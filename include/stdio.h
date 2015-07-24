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

#ifndef _NORLIT_LIBC_STDIO_H
#define _NORLIT_LIBC_STDIO_H

#define __need_FILE
#define __need_size_t
#define __need_va_list
#include <norlit/alltypes.h>

#define __need_NULL
#include <stddef.h>

#define __need_ssize_t
#define __need_off_t
#include <sys/types.h>

typedef off_t fpos_t;

#define BUFSIZ 4096
// L_ctermid
// L_tmpnam

// 0 is reserved for undefined
#define _IOFBF 1
#define _IOLBF 2
#define _IONBF 3

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

// TODO: These three need to be fixed
#define FILENAME_MAX 0xFFFF
#define FOPEN_MAX    0xFFFF
#define TMP_MAX      0xFFFF

#define EOF (-1)

// P_tmpdir

#define stdin  ((FILE*)__get_std_streams()[0])
#define stdout ((FILE*)__get_std_streams()[1])
#define stderr ((FILE*)__get_std_streams()[2])

#include <norlit/header/start.h>
FILE** __get_std_streams(void);

void     clearerr(FILE *);
int      fclose(FILE *);
int      feof(FILE *);
int      ferror(FILE *);
int      fflush(FILE *);
int      fgetc(FILE *);
int      fgetpos(FILE *__restrict, fpos_t *__restrict);
char    *fgets(char *__restrict, int, FILE *__restrict);
FILE    *fopen(const char *__restrict, const char *__restrict);
int      fprintf(FILE *__restrict, const char *__restrict, ...);
int      fputc(int, FILE *);
int      fputs(const char *__restrict, FILE *__restrict);
size_t   fread(void *__restrict, size_t, size_t, FILE *__restrict);
FILE    *freopen(const char *__restrict, const char *__restrict,
                 FILE *__restrict);
int      fscanf(FILE *__restrict, const char *__restrict, ...);
int      fseek(FILE *, long, int);
int      fsetpos(FILE *, const fpos_t *);
long     ftell(FILE *);
size_t   fwrite(const void *__restrict, size_t, size_t, FILE *__restrict);
int      getc(FILE *);
int      getchar(void);
char    *gets(char *);
void     perror(const char *);
int      printf(const char *__restrict, ...);
int      putc(int, FILE *);
int      putchar(int);
int      puts(const char *);
int      remove(const char *);
int      rename(const char *, const char *);
void     rewind(FILE *);
int      scanf(const char *__restrict, ...);
void     setbuf(FILE *__restrict, char *__restrict);
int      setvbuf(FILE *__restrict, char *__restrict, int, size_t);
int      snprintf(char *__restrict, size_t, const char *__restrict, ...);
int      sprintf(char *__restrict, const char *__restrict, ...);
int      sscanf(const char *__restrict, const char *__restrict, ...);
FILE    *tmpfile(void);
char    *tmpnam(char *);
int      ungetc(int, FILE *);
int      vfprintf(FILE *__restrict, const char *__restrict, va_list);
int      vfscanf(FILE *__restrict, const char *__restrict, va_list);
int      vprintf(const char *__restrict, va_list);
int      vscanf(const char *__restrict, va_list);
int      vsnprintf(char *__restrict, size_t, const char *__restrict,
                   va_list);
int      vsprintf(char *__restrict, const char *__restrict, va_list);
int      vsscanf(const char *__restrict, const char *__restrict, va_list);

// CX Extension
char    *ctermid(char *);
int      dprintf(int, const char *__restrict, ...);
FILE    *fdopen(int, const char *);
int      fileno(FILE *);
void     flockfile(FILE *);
FILE    *fmemopen(void *__restrict, size_t, const char *__restrict);
int      fseeko(FILE *, off_t, int);
off_t    ftello(FILE *);
int      ftrylockfile(FILE *);
void     funlockfile(FILE *);
int      getc_unlocked(FILE *);
int      getchar_unlocked(void);
ssize_t  getdelim(char **__restrict, size_t *__restrict, int,
                  FILE *__restrict);
ssize_t  getline(char **__restrict, size_t *__restrict, FILE *__restrict);
FILE    *open_memstream(char **, size_t *);
int      pclose(FILE *);
FILE    *popen(const char *, const char *);
int      putc_unlocked(int, FILE *);
int      putchar_unlocked(int);
int      renameat(int, const char *, int, const char *);
int      vdprintf(int, const char *__restrict, va_list);

// Obsolete XSI Extension
char    *tempnam(const char *, const char *);
#include <norlit/header/end.h>

#endif