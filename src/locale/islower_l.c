#include <ctype.h>
#include <assert.h>

int islower_l(int c, locale_t loc) {
	if (c < 0x80) {
		return c >= 'a' && c <= 'z';
	}
	assert(0); // Unicode not yet supported
}