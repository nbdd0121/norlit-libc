#include <ctype.h>
#include <assert.h>

int tolower_l(int c, locale_t loc) {
	if (c >= 'A' && c <= 'Z') {
		return c - 'A' + 'a';
	}
	return c;
}