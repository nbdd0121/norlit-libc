#include <string.h>

size_t strxfrm_l(char *restrict s1, const char *restrict s2, size_t n, locale_t locale) {
	size_t len = strlen(s2);
	strncpy(s1, s2, n);
	return len;
}