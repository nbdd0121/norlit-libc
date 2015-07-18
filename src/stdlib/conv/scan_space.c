#include "internal.h"
#include <ctype.h>

const char* scan_space(const char* str) {
	str--;
	while (isspace(*++str));
	return str;
}