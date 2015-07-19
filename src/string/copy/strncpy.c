#include <string.h>

char *strncpy(char * restrict s1, const char * restrict s2, size_t n) {
	if (n) {
		char *dst = s1;
		const char *src = s2;
		size_t i;
		for (i = 0; *src && i < n; i++, dst++, src++) {
			*dst = *src;
		}
		if (i < n) {
			*dst = 0;
		}
	}
	return s1;
}