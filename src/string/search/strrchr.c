#include <string.h>

char *strrchr(const char *s, int c) {
	const char* occur = NULL;
	char byte = (char)c;
	for (; *s; s++) {
		if (*s == byte) {
			occur = s;
		}
	}
	if (!byte)
		return (char *)s;
	return (char*) occur;
}