#include <ctype.h>
#include <assert.h>

int isupper_l(int c, locale_t loc) {
	if (c < 0x80) {
		return c >= 'A' && c <= 'Z';
	}
	assert(0); // Unicode not yet supported
}