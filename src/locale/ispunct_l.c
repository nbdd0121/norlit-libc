#include <ctype.h>
#include <assert.h>

int ispunct_l(int c, locale_t loc) {
	if (c < 0x80) {
		return isgraph_l(c, loc) && !isalnum_l(c, loc);
	}
	assert(0); // Unicode not yet supported
}