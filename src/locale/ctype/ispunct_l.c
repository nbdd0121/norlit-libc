#include <ctype.h>
#include <assert.h>

int ispunct_l(int c, locale_t loc) {
	return isgraph_l(c, loc) && !isalnum_l(c, loc);
}