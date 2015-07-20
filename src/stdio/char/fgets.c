#include "../internal.h"

char *fgets(char *restrict s, int size, FILE *restrict f) {
	for (int i = 0; i < size - 1; i++) {
		int ch = fgetc(f);
		if (ch == EOF) {
			s[i] = 0;
			if (i == 0) return NULL;
			return s;
		}
		s[i] = ch;
		if (ch == '\n') {
			s[i + 1] = 0;
			return s;
		}
	}
	s[size - 1] = 0;
	return s;
}
