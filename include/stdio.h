#ifndef _NORLIT_LIBC_STDIO_H
#define _NORLIT_LIBC_STDIO_H

#define __need_size_t
#define __need_NULL
#include <stddef.h>

#include <stdarg.h>

#define __need_ssize_t
#define __need_off_t
#include <sys/types.h>

struct _FILE;
typedef struct _FILE FILE;

typedef uint64_t fpos_t;

#define BUFSIZ 4096
// L_ctermid
// L_tmpnam

// 0 is reserved for undefined
#define _IOFBF 1
#define _IOLBF 2
#define _IONBF 3

#define SEEK_CUR 0
#define SEEK_END 1
#define SEEK_SET 2

// TODO: These three need to be fixed
#define FILENAME_MAX 0xFFFF
#define FOPEN_MAX    0xFFFF
#define TMP_MAX      0xFFFF

#define EOF (-1)

// P_tmpdir

FILE** __get_std_streams(void);

#define stdin  ((FILE*)__get_std_streams()[0])
#define stdout ((FILE*)__get_std_streams()[1])
#define stderr ((FILE*)__get_std_streams()[2])

void     clearerr(FILE *);
int      fclose(FILE *);
int      feof(FILE *);
int      ferror(FILE *);
int      fflush(FILE *);
int      fgetc(FILE *);
int      fgetpos(FILE *restrict, fpos_t *restrict);
char    *fgets(char *restrict, int, FILE *restrict);
FILE    *fopen(const char *restrict, const char *restrict);
int      fprintf(FILE *restrict, const char *restrict, ...);
int      fputc(int, FILE *);
int      fputs(const char *restrict, FILE *restrict);
size_t   fread(void *restrict, size_t, size_t, FILE *restrict);
FILE    *freopen(const char *restrict, const char *restrict,
                 FILE *restrict);
int      fscanf(FILE *restrict, const char *restrict, ...);
int      fseek(FILE *, long, int);
int      fsetpos(FILE *, const fpos_t *);
long     ftell(FILE *);
size_t   fwrite(const void *restrict, size_t, size_t, FILE *restrict);
int      getc(FILE *);
int      getchar(void);
char    *gets(char *);
void     perror(const char *);
int      printf(const char *restrict, ...);
int      putc(int, FILE *);
int      putchar(int);
int      puts(const char *);
int      remove(const char *);
int      rename(const char *, const char *);
void     rewind(FILE *);
int      scanf(const char *restrict, ...);
void     setbuf(FILE *restrict, char *restrict);
int      setvbuf(FILE *restrict, char *restrict, int, size_t);
int      snprintf(char *restrict, size_t, const char *restrict, ...);
int      sprintf(char *restrict, const char *restrict, ...);
int      sscanf(const char *restrict, const char *restrict, ...);
FILE    *tmpfile(void);
char    *tmpnam(char *);
int      ungetc(int, FILE *);
int      vfprintf(FILE *restrict, const char *restrict, va_list);
int      vfscanf(FILE *restrict, const char *restrict, va_list);
int      vprintf(const char *restrict, va_list);
int      vscanf(const char *restrict, va_list);
int      vsnprintf(char *restrict, size_t, const char *restrict,
                   va_list);
int      vsprintf(char *restrict, const char *restrict, va_list);
int      vsscanf(const char *restrict, const char *restrict, va_list);

// CX Extension
char    *ctermid(char *);
int      dprintf(int, const char *restrict, ...);
FILE    *fdopen(int, const char *);
int      fileno(FILE *);
void     flockfile(FILE *);
FILE    *fmemopen(void *restrict, size_t, const char *restrict);
int      fseeko(FILE *, off_t, int);
off_t    ftello(FILE *);
int      ftrylockfile(FILE *);
void     funlockfile(FILE *);
int      getc_unlocked(FILE *);
int      getchar_unlocked(void);
ssize_t  getdelim(char **restrict, size_t *restrict, int,
                  FILE *restrict);
ssize_t  getline(char **restrict, size_t *restrict, FILE *restrict);
FILE    *open_memstream(char **, size_t *);
int      pclose(FILE *);
FILE    *popen(const char *, const char *);
int      putc_unlocked(int, FILE *);
int      putchar_unlocked(int);
int      renameat(int, const char *, int, const char *);
int      vdprintf(int, const char *restrict, va_list);

// Obsolete XSI Extension
char    *tempnam(const char *, const char *);

#endif