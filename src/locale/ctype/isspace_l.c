#include <ctype.h>
#include <assert.h>

int isspace_l(int c, locale_t loc) {
	return c == ' ' || (unsigned)c - '\t' < 5;
}