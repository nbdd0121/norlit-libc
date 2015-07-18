#include <ctype.h>
#include <assert.h>

int isblank_l(int c, locale_t loc) {
	if (c < 0x80) {
		return c == ' ' || c == '\t';
	}
	assert(0); // Unicode not yet supported
}