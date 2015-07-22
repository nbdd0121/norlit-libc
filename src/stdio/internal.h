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