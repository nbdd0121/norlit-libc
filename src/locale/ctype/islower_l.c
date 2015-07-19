#include <ctype.h>
#include <assert.h>

int islower_l(int c, locale_t loc) {
	return c >= 'a' && c <= 'z';
}