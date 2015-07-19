#include <ctype.h>
#include <assert.h>

int toupper_l(int c, locale_t loc) {
	if (c >= 'a' && c <= 'z') {
		return c - 'a' + 'A';
	}
	return c;
}