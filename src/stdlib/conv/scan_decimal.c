#include "internal.h"
#include <stdbool.h>

static inline int getdigit(char ch) {
	if (ch >= 'a' && ch <= 'z') return ch - 'a' + 10;
	if (ch >= 'A' && ch <= 'Z') return ch - 'A' + 10;
	if (ch >= '0' && ch <= '9') return ch - '0';
	return -1;
}

const char* scan_decimal(const char* str, size_t len, uint64_t* data, int* overflow, int base) {
	bool overflowFlag = false;
	size_t ptr = 0;
	uint64_t ret = *data;
	for (; ptr < len; ptr++) {
		int val = getdigit(str[ptr]);
		if (val >= 0 && val < base) {
			if (!overflowFlag) {
				uint64_t newVal = ret * base + val;
				if (newVal > ret) {
					ret = newVal;
				} else {
					overflowFlag = true;
				}
			}
			if (overflowFlag && overflow) {
				(*overflow)++;
			}
		} else {
			break;
		}
	}
	*data = ret;
	return str + ptr;
}