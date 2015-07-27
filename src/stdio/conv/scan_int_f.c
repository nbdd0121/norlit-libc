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
#include <limits.h>
#include <errno.h>

int scan_int_f(FILE* f, int maxlen, int base, uintmax_t* ret, int* sign) {
	int len = 0;

	if (len >= maxlen) return len;
	int ch = fgetc(f);
	int neg = 0;
	if (ch == '-') {
		len++;
		neg = 1;
	} else if (ch != '+') {
		ungetc(ch, f);
	}

	if (base == 0) {
		if (scan_string_f(f, maxlen - len, "0")) {
			printf(")\n");
			len++;
			if (scan_string_f(f, maxlen - len, "X")) {
				len++;
				base = 16;
			} else {
				ungetc(ch, f);
				base = 8;
			}
		} else {
			base = 10;
		}
	} else if (base == 16) {
		if (scan_string_f(f, maxlen - len, "0X")) {
			len += 2;
		}
	} else if (base < 2 || base > 36) {
		*ret = 0;
		*sign = -EINVAL;
		return 0;
	}

	int overflow = 0;
	len += scan_decimal_f(f, maxlen - len, ret, NULL, &overflow, base);
	if (overflow) {
		*ret = neg;
		*sign = -ERANGE;
		return 0;
	}
	*sign = neg;
	return len;
}