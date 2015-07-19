#include <ctype.h>
#include <assert.h>

int isupper_l(int c, locale_t loc) {
	return c >= 'A' && c <= 'Z';
}