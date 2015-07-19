#include <string.h>

char *strpbrk(const char *s1, const char *s2) {
	for (; *s1; s1++) {
		char ch = *s1;
		for (const char* search = s2; *search; search++) {
			if (ch == *search) {
				return (char *)s1;
			}
		}
	}
	return NULL;
}