#include <ctype.h>
#include <assert.h>

int isdigit_l(int c, locale_t loc) {
	return c >= '0' && c <= '9';
}