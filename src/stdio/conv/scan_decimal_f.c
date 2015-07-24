/*
 * Copyright (c) 2015, Gary Guo 
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met: 
 * 
 *  * Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer. 
 *  * Redistributions in binary form must reproduce the above copyright 
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the distribution. 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND ANY 
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR ANY 
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY 
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH 
 * DAMAGE. 
 */

#include "internal.h"
#include <stdbool.h>

static inline int getdigit(char ch) {
	if (ch >= 'a' && ch <= 'z') return ch - 'a' + 10;
	if (ch >= 'A' && ch <= 'Z') return ch - 'A' + 10;
	if (ch >= '0' && ch <= '9') return ch - '0';
	return -1;
}

int scan_decimal_f(FILE* f, int maxlen, unsigned long long* data, int* len, int* overflow, int base) {
	bool overflowFlag = false;
	int overflowDigits = 0;
	int processedLen = 0;
	unsigned long long value = *data;
	while (processedLen < maxlen) {
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
				}
			}
			if (overflowFlag) {
				overflowDigits++;
			}
			processedLen++;
		} else {
			ungetc(ch, f);
			break;
		}
	}
	*data = value;
	if (len)
		*len += processedLen - overflowDigits;
	if (overflow)
		*overflow = overflowDigits;
	return processedLen;
}