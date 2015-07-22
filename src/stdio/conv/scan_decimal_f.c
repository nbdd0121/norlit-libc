#include "internal.h"
#include <stdbool.h>

static inline int getdigit(char ch) {
	if (ch >= 'a' && ch <= 'z') return ch - 'a' + 10;
	if (ch >= 'A' && ch <= 'Z') return ch - 'A' + 10;
	if (ch >= '0' && ch <= '9') return ch - '0';
	return -1;
}

int scan_decimal_f(FILE* f, unsigned long long* data, int* len, int* overflow, int base) {
	bool overflowFlag = false;
	int overflowDigits = 0;
	int processedLen = 0;
	unsigned long long value = *data;
	while (1) {
		int ch = fgetc(f);
		int digit = getdigit(ch);
		if (digit >= 0 && digit < base) {
			if (!overflowFlag) {
				unsigned long long newVal;
				if (__builtin_umulll_overflow(value, base, &newVal) ||
				        __builtin_uaddll_overflow(newVal, digit, &newVal)) {
					overflowFlag = true;
				} else {
					value = newVal;
					processedLen++;
				}
			}
			if (overflowFlag) {
				overflowDigits++;
			}
		} else {
			ungetc(ch, f);
			break;
		}
	}
	*data = value;
	if (len)
		*len += processedLen;
	if (overflow)
		*overflow = overflowDigits;
	return processedLen + overflowDigits;
}