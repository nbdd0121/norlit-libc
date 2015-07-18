#include <stdlib.h>

void *bsearch(const void *key, const void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *)) {
	while (nmemb > 0) {
		size_t guessIndex = nmemb / 2;
		void* guess = (char*)base + size * guessIndex;
		int sign = compar(key, guess);
		if (sign == 0) {
			return guess;
		} else if (nmemb == 1) {
			break;
		} else if (sign < 0) {
			nmemb = guessIndex;
		} else {
			base = guess;
			nmemb -= guessIndex;
		}
	}
	return NULL;
}
