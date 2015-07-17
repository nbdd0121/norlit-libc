#include <string.h>

char *strncat(char * restrict s1, const char * restrict s2, size_t n) {
	if (n) {
		strncpy(s1 + strlen(s1), s2, n);
	}
	return s1;
}
