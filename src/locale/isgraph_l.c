#include <ctype.h>
#include <assert.h>

int isgraph_l(int c, locale_t loc) {
	if (c < 0x80) {
		return !iscntrl_l(c, loc) && c != ' ';
	}
	assert(0); // Unicode not yet supported
}