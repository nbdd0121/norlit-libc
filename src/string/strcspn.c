#include <string.h>

size_t strcspn(const char *s1, const char *s2) {
	size_t count;
	for (count = 0; *s1; count++, s1++) {
		char ch = *s1;
		for (const char* search = s2; *search; search++) {
			if (ch == *search) {
				return count;
			}
		}
	}
	return count;
}