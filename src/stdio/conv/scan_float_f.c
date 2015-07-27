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
#include <ctype.h>
#include <math.h>
#include <assert.h>

int scan_float_f(FILE* f, int maxlen, double* data) {
    bool sign = false;

    int len = 0;
    if (len >= maxlen) return len;

    int ch = fgetc(f);
    switch (ch) {
        case '-':
            sign = true;
        case '+':
            len++;
            break;
        default:
            ungetc(ch, f);
            break;
    }

    if (scan_string_f(f, maxlen - len, "INF")) {
        len += 3;
        if (scan_string_f(f, maxlen - len, "INITY")) {
            len += 5;
        }
        *data = sign ? -INFINITY : INFINITY;
        return len;
    }

    if (scan_string_f(f, maxlen - len, "NAN")) {
        len += 3;
        ch = fgetc(f);
        if (ch == '(') {
            assert(0);
        }
        *data = NAN;
        ungetc(ch, f);
        return len;
    }

    int base = 10;
    if (scan_string_f(f, maxlen - len, "0X")) {
        len += 2;
        base = 16;
    }

    uintmax_t s = 0;
    int n = 0;
    int k = 0;

    if (scan_string_f(f, maxlen - len, ".")) {
        len ++;
        len += scan_decimal_f(f, maxlen - len, &s, &k, NULL, base);
        if (!k) {
            *data = 0;
            return len;
        }
    } else {
        len += scan_decimal_f(f, maxlen - len, &s, NULL, &k, base);
        if (scan_string_f(f, maxlen - len, ".")) {
            len++;
            len += scan_decimal_f(f, maxlen - len, &s, &k, NULL, base);
        }
    }
    /* Exponential part */
    if (scan_string_f(f, maxlen - len, base == 16 ? "P" : "E")) {
        len++;
        bool sign = false;

        if (len >= maxlen) goto assemble;
        ch = fgetc(f);
        if (ch == '+') {
            len++;
        } else if (ch == '-') {
            len++;
            sign = true;
        } else {
            ungetc(ch, f);
        }

        uintmax_t expPart = 0;
        int expPartLength = 0;
        len += scan_decimal_f(f, maxlen - len, &expPart, &expPartLength, NULL, 10);
        if (expPart > 1000) expPart = 1000;

        n = (sign ? -1 : 1) * (int)expPart;
    }

assemble:
    while (s > UINT64_MAX) {
        s >>= 1;
    }

    *data = (base == 16 ? assemble_double_hex : assemble_double)((uint64_t)s, n, k);
    return len;
}