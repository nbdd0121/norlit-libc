#include <ctype.h>
#include <assert.h>

int tolower_l(int c, locale_t loc) {
	if (c < 0x80) {
		if (c >= 'A' && c <= 'Z') {
			return c - 'A' + 'a';
		}
		return c;
	}
	assert(0); // Unicode not yet supported
}