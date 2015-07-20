#include <stdio.h>
#include <unistd.h>

struct _FILE {
	size_t (*read) (FILE*, char*, size_t);
	size_t (*write)(FILE*, const char*, size_t);
	off_t  (*seek) (FILE*, off_t, int);
	int    (*close)(FILE*);
	int      fildes;
	int      flags;

	unsigned bufpolicy: 2;
	unsigned bufmode  : 2;
	unsigned bufmalloc: 1;

	int		 bufsize;
	int      bufpos;

	char    *buffer;
};

#define BUFMODE_WRITE 1
#define BUFMODE_READ  2

#define FLAG_EOF 1
#define FLAG_ERR 2

#define strong_alias(name, aliasname) __typeof(name) aliasname __attribute__((alias(#name)))