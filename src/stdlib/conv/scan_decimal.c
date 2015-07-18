#include "internal.h"
#include <stdbool.h>

static inline int getdigit(char ch) {
	if (ch >= 'a' && ch <= 'z') return ch - 'a' + 10;
	if (ch >= 'A' && ch <= 'Z') return ch - 'A' + 10;
	if (ch >= '0' && ch <= '9') return ch - '0';
	return -1;
}

const char* scan_decimal(const char* str, uint64_t* data, int* len, int* overflow, int base) {
	bool overflowFlag = false;
	int overflowDigits = 0;
	uint64_t value = *data;
	const char* ptr = str;
	for (; *ptr; ptr++) {
		int digit = getdigit(*ptr);
		if (digit >= 0 && digit < base) {
			if (!overflowFlag) {
				uint64_t newVal;
				if (__builtin_umulll_overflow(value, base, &newVal) ||
				        __builtin_uaddll_overflow(newVal, digit, &newVal)) {
					overflowFlag = true;
				} else {
					value = newVal;
				}
			}
			if (overflowFlag) {
				overflowDigits++;
			}
		} else {
			break;
		}
	}
	*data = value;
	if (len)
		*len += ptr - str - overflowDigits;
	if (overflow)
		*overflow = overflowDigits;
	return ptr;
}