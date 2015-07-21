#include "../internal.h"
#include <limits.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>

typedef struct {
	char* buf;
	size_t size;
} memfile_t;

static size_t sn_write(FILE *f, const char *buf, size_t len) {
	memfile_t* memf = f->additionalData;
	size_t toWrite = len > memf->size ? memf->size : len;
	memcpy(memf->buf, buf, toWrite);
	memf->buf += toWrite;
	memf->size -= toWrite;
	return len;
}

int vsnprintf(char *restrict s, size_t n, const char *restrict fmt, va_list ap) {
	memfile_t memf = {.buf = s, .size = n};
	FILE f = { .write = sn_write, .bufpolicy = _IONBF, .additionalData = &memf};
	int ret = vfprintf(&f, fmt, ap);
	if (ret < 0) {
		return ret;
	}
	if ((size_t)ret < n) {
		s[ret] = 0;
	} else {
		s[n - 1] = 0;
	}
	return ret;
}