#include <ctype.h>
#include <assert.h>

int isxdigit_l(int c, locale_t loc) {
	if (c < 0x80) {
		return (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f') || (c >= '0' && c <= '9');
	}
	assert(0); // Unicode not yet supported
}