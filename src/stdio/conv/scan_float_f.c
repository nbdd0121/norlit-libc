#include "internal.h"
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>

int scan_float_f(FILE* f, double* data) {
    bool sign = false;

    int len = 0;
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

    if (scan_string_f(f, "INF")) {
        len += 3;
        if (scan_string_f(f, "INITY")) {
            len += 5;
        }
        *data = sign ? -INFINITY : INFINITY;
        return len;
    }

    if (scan_string_f(f, "NAN")) {
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
    if (scan_string_f(f, "0X")) {
        len += 2;
        base = 16;
    }

    unsigned long long s = 0;
    int n = 0;
    int k = 0;

    if (scan_string_f(f, ".")) {
        len ++;
        len += scan_decimal_f(f, &s, &k, NULL, base);
        if (!k) {
            *data = 0;
            return len;
        }
    } else {
        len += scan_decimal_f(f, &s, NULL, &k, base);
        if (scan_string_f(f, ".")) {
            len++;
            len += scan_decimal_f(f, &s, &k, NULL, base);
        }
    }
    /* Exponential part */
    if (scan_string_f(f, base == 16 ? "P" : "E")) {
        len++;
        bool sign = false;

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
        len += scan_decimal_f(f, &expPart, &expPartLength, NULL, 10);
        if (expPart > 1000) expPart = 1000;

        n = (sign ? -1 : 1) * (int)expPart;
    }

    while (s > UINT64_MAX) {
        s >>= 1;
    }

    *data = (base == 16 ? assemble_double_hex : assemble_double)((uint64_t)s, n, k);
    return len;
}