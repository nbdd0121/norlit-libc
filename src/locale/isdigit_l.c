#include <ctype.h>
#include <assert.h>

int isdigit_l(int c, locale_t loc) {
	if (c < 0x80) {
		return c >= '0' && c <= '9';
	}
	assert(0); // Unicode not yet supported
}