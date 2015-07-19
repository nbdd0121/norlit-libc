#include "internal.h"

__attribute__((visibility("internal")))
void (*exit_register[EXIT_REGISTER_COUNT])(void);

__attribute__((visibility("internal")))
void (*quick_exit_register[QUICK_EXIT_REGISTER_COUNT])(void);

__attribute__((visibility("internal")))
int exit_reg_count = 0;

__attribute__((visibility("internal")))
int quick_exit_reg_count = 0;