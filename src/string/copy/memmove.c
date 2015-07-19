#include <string.h>

void *memmove(void *s1, const void *s2, size_t n) {
	char *dst = s1;
	const char *src = s2;
	if (dst < src || dst > src + n) {
		for (size_t i = 0; i < n; i++, dst++, src++) {
			*dst = *src;
		}
	} else {
		dst += n;
		src += n;
		for (size_t i = 0; i < n; i++, dst--, src--) {
			*dst = *src;
		}
	}
	return s1;
}