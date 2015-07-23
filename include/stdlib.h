#ifndef _NORLIT_LIBC_STDLIB_H
#define _NORLIT_LIBC_STDLIB_H

#define __need_size_t
#define __need_wchar_t
#define __need_NULL
#include <stddef.h>

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0
#define RAND_MAX     0x7FFFFFFF

#define MB_CUR_MAX      ((size_t)4)

#include <norlit/header/start.h>
typedef struct {
	int quot;
	int rem;
} div_t;

typedef struct {
	long quot;
	long rem;
} ldiv_t;

typedef struct {
	long long quot;
	long long rem;
} lldiv_t;

// CX Extensions
// Not Implemented yet <sys/wait.h>

_Noreturn
void          _Exit(int);
_Noreturn
void          abort(void);
int           abs(int);
void         *aligned_alloc(size_t, size_t);
int           atexit(void (*)(void));
int           at_quick_exit(void (*func)(void));
double        atof(const char *);
int           atoi(const char *);
long          atol(const char *);
long long     atoll(const char *);
void         *bsearch(const void *, const void *, size_t, size_t, int (*)(const void *, const void *));
void         *calloc(size_t, size_t);
div_t         div(int, int);
_Noreturn
void          exit(int);
void          free(void *);
char         *getenv(const char *);
long          labs(long);
ldiv_t        ldiv(long, long);
long long     llabs(long long);
lldiv_t       lldiv(long long, long long);
void         *malloc(size_t);
int           mblen(const char *, size_t);
size_t        mbstowcs(wchar_t *__restrict, const char *__restrict, size_t);
int           mbtowc(wchar_t *__restrict, const char *__restrict, size_t);
void          qsort(void *, size_t, size_t, int (*)(const void *, const void *));
_Noreturn
void          quick_exit(int status);
int           rand(void);
void         *realloc(void *, size_t);
void          srand(unsigned);
double        strtod(const char *__restrict, char **__restrict);
float         strtof(const char *__restrict, char **__restrict);
long          strtol(const char *__restrict, char **__restrict, int);
long double   strtold(const char *__restrict, char **__restrict);
long long     strtoll(const char *__restrict, char **__restrict, int);
unsigned long strtoul(const char *__restrict, char **__restrict, int);
unsigned long long strtoull(const char *__restrict, char **__restrict, int);
int           system(const char *);
size_t        wcstombs(char *__restrict, const wchar_t *__restrict, size_t);
int           wctomb(char *, wchar_t);

// XSI Extensions
long          a64l(const char *);
double        drand48(void);
double        erand48(unsigned short [3]);
int           grantpt(int);
char         *initstate(unsigned, char *, size_t);
long          jrand48(unsigned short [3]);
char         *l64a(long);
void          lcong48(unsigned short [7]);
long          lrand48(void);
long          mrand48(void);
long          nrand48(unsigned short [3]);
int           posix_openpt(int);
char         *ptsname(int);
int           putenv(char *);
long          random(void);
char         *realpath(const char *__restrict, char *__restrict);
unsigned short *seed48(unsigned short [3]);
void          setkey(const char *);
char         *setstate(char *);
void          srand48(long);
void          srandom(unsigned);

// CX Extensions
int           getsubopt(char **, char *const *, char **);
char         *mkdtemp(char *);
int           mkstemp(char *);
int           setenv(const char *, const char *, int);

// Obselete CX Extensions
int           rand_r(unsigned *);

// ADV Extensions
int           posix_memalign(void **, size_t, size_t);
#include <norlit/header/end.h>

#endif