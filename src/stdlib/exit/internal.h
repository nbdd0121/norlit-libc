#ifndef _NORLIT_LIBC_STDLIB_EXIT_INTERNAL_H
#define _NORLIT_LIBC_STDLIB_EXIT_INTERNAL_H

#define EXIT_REGISTER_COUNT 		32
#define QUICK_EXIT_REGISTER_COUNT	32

extern void (*exit_register[EXIT_REGISTER_COUNT])(void);
extern void (*quick_exit_register[QUICK_EXIT_REGISTER_COUNT])(void);

extern int exit_reg_count;
extern int quick_exit_reg_count;

#endif