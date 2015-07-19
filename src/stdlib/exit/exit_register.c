#include "internal.h"

__attribute__((visibility("hidden")))
void (*exit_register[EXIT_REGISTER_COUNT])(void);

__attribute__((visibility("hidden")))
void (*quick_exit_register[QUICK_EXIT_REGISTER_COUNT])(void);

__attribute__((visibility("hidden")))
int exit_reg_count = 0;

__attribute__((visibility("hidden")))
int quick_exit_reg_count = 0;