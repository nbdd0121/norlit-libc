#include "../internal.h"
#include <limits.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>

size_t s_read(FILE *f, char *buf, size_t len) {
	char* mbuf = f->additionalData;
	size_t toRead = strnlen(mbuf, len);
	if (toRead == 0) {
		f->flags |= FLAG_EOF;
		return 0;
	}
	memcpy(buf, mbuf, toRead);
	mbuf += toRead;
	f->additionalData = mbuf;
	return toRead;
}

int vsscanf(const char *restrict s, const char *restrict fmt, va_list ap) {
	FILE f = { .read = s_read, .bufpolicy = _IONBF, .bufpos = -1, .flags = 0, .additionalData = (void*)s};
	return vfscanf(&f, fmt, ap);
}