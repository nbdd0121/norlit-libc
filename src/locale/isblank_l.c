#include <ctype.h>
#include <assert.h>

int isblank_l(int c, locale_t loc) {
	return c == ' ' || c == '\t';
}