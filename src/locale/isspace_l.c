#include <ctype.h>
#include <assert.h>

int isspace_l(int c, locale_t loc) {
	if (c < 0x80) {
		return c == ' ' || (unsigned)c - '\t' < 5;
	}
	assert(0); // Unicode not yet supported
}