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

    unsigned long long s = 0;
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

        unsigned long long expPart = 0;
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