#include <string.h>

size_t strspn(const char *s1, const char *s2) {
	size_t count;
	for (count = 0; *s1; count++, s1++) {
		char ch = *s1;
		const char* search;
		for (search = s2; *search; search++) {
			if (ch == *search) {
				break;
			}
		}
		if (!*search) {
			return count;
		}
	}
	return count;
}