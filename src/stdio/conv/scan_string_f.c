#include "internal.h"
#include <ctype.h>
#include <string.h>

int scan_string_f(FILE* f, int maxlen, char* str) {
    int len = strlen(str);
    if (len > maxlen) return 0;
    char buf[len];
    int i;
    for (i = 0; i < len; i++) {
        int ch = fgetc(f);
        if (ch < 0) {
            i--;
            break;
        }
        buf[i] = ch;
        if (toupper(ch) != str[i]) {
            break;
        }
    }
    if (i == len) return len;
    for (int j = i; j >= 0; j--) {
        ungetc(buf[j], f);
    }
    return 0;
}

