#include "internal.h"
#include <limits.h>
#include <string.h>

#include "../../stdio/internal.h"
#include "../../stdio/conv/internal.h"

const char* scan_float(const char* ptr, double* data) {
    ptr = scan_space(ptr);
    FILE f = { .read = s_read, .bufpolicy = _IONBF, .bufpos = -1, .flags = 0, .additionalData = (void*)ptr};
    return ptr + scan_float_f(&f, INT_MAX, data);
}