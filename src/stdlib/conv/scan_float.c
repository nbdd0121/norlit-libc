#include "internal.h"
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>

const char* scan_float(const char* ptr, double* data) {
    bool sign = false;

    switch (*ptr) {
        case '-':
            sign = true;
        case '+':
            ptr++;
            break;
    }

    if (toupper(ptr[0]) == 'I' && toupper(ptr[1]) == 'N' && toupper(ptr[2]) == 'F') {
        ptr += 3;
        if (toupper(ptr[0]) == 'N' && toupper(ptr[1]) == 'I' && toupper(ptr[2]) == 'T' && toupper(ptr[3]) == 'Y') {
            ptr += 4;
        }
        *data = sign ? -INFINITY : INFINITY;
        return ptr;
    }

    if (toupper(ptr[0]) == 'N' && toupper(ptr[1]) == 'A' && toupper(ptr[2]) == 'N') {
        ptr += 3;
        if (ptr[0] == '(') {
            assert(0);
        }
        *data = NAN;
        return ptr;
    }

    int base = 10;
    if (ptr[0] == '0' && toupper(ptr[1]) == 'X') {
        ptr += 2;
        base = 16;
    }

    unsigned long long s = 0;
    int n = 0;
    int k = 0;

    char ch = *ptr;
    if (ch == '.') {
        ptr++;
        ptr = scan_decimal(ptr, &s, &k, NULL, base);
        if (!k) {
            *data = 0;
            return ptr;
        }
    } else {
        ptr = scan_decimal(ptr, &s, NULL, &k, base);
        if (*ptr == '.') {
            ptr++;
            ptr = scan_decimal(ptr, &s, &k, NULL, base);
        }
    }
    /* Exponential part */
    if (toupper(*ptr) == (base == 16 ? 'P' : 'E')) {
        const char* beforeExp = ptr;

        ptr++;
        bool sign = false;

        if (*ptr == '+') {
            ptr++;
        } else if (*ptr == '-') {
            sign = true;
            ptr++;
        }

        unsigned long long expPart = 0;
        int expPartLength = 0;
        ptr = scan_decimal(ptr, &expPart, &expPartLength, NULL, 10);
        if (expPart > 1000) expPart = 1000;

        if (!expPartLength) {
            ptr = beforeExp;
        }

        n = (sign ? -1 : 1) * (int)expPart;
    }

    while (s > UINT64_MAX) {
        s >>= 1;
    }

    *data = (base == 16 ? assemble_double_hex : assemble_double)((uint64_t)s, n, k);
    return ptr;
}