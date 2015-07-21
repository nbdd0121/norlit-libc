#include <stdio.h>

int printf(const char *restrict fmt, ...) {
	int ret;
	va_list ap;
	va_start(ap, fmt);
	ret = vprintf(fmt, ap);
	va_end(ap);
	return ret;
}