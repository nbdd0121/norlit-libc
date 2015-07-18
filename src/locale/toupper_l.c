#include <ctype.h>
#include <assert.h>

int toupper_l(int c, locale_t loc) {
	if (c < 0x80) {
		if (c >= 'a' && c <= 'z') {
			return c - 'a' + 'A';
		}
		return c;
	}
	assert(0); // Unicode not yet supported
}