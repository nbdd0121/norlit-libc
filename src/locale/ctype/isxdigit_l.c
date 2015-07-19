#include <ctype.h>
#include <assert.h>

int isxdigit_l(int c, locale_t loc) {
	return (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f') || (c >= '0' && c <= '9');
}