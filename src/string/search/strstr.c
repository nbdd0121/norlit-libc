#include <string.h>

char *strstr(const char *s1, const char *s2) {
	size_t len1 = strlen(s1);
	size_t len2 = strlen(s2);
	if (!len2)
		return (char*) s1;
	if (len1 < len2) {
		return NULL;
	}
	for (size_t i = 0; i <= len1 - len2; i++) {
		if (memcmp(s1 + i, s2, len2) == 0) {
			return (char*)s1 + i;
		}
	}
	return NULL;
}