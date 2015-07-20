#include "../internal.h"
#include <errno.h>
#include <fcntl.h>
#include <assert.h>

FILE *fopen(const char *restrict filename, const char *restrict mode) {
	int flags = translateFlags(mode);
	if (flags == -1) {
		errno = EINVAL;
		return NULL;
	}

	int fd = open(filename, flags, 0);
	if (fd == -1)return 0;

	FILE* f = fdopen(fd, mode);
	if (!f) {
		assert(0);
	}

	return f;
}