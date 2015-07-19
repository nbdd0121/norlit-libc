#include <string.h>

char *stpcpy(char * restrict s1, const char * restrict s2) {
	char *dst = s1;
	const char *src = s2;
	for (; *src; dst++, src++) {
		*dst = *src;
	}
	*dst = 0;
	return dst;
}