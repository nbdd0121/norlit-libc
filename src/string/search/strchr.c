#include <string.h>

char *strchr(const char *s, int c) {
	char byte = (char)c;
	for (; *s; s++) {
		if (*s == byte) {
			return (char *)s;
		}
	}
	if (!byte)
		return (char *)s;
	return NULL;
}