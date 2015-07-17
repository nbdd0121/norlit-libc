#include <string.h>

char *strcpy(char * restrict s1, const char * restrict s2) {
	char *dst = s1;
	const char *src = s2;
	for (; *src; dst++, src++) {
		*dst = *src;
	}
	*dst = 0;
	return s1;
}