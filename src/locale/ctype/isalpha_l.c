#include <ctype.h>
#include <assert.h>

int isalpha_l(int c, locale_t loc) {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}