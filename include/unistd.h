#ifndef _NORLIT_LIBC_UNISTD_H
#define _NORLIT_LIBC_UNISTD_H

#define __need_off_t
#define __need_size_t
#define __need_ssize_t
#include <sys/types.h>

extern char** environ;

int          close(int);
_Noreturn
void         _exit(int);
off_t        lseek(int, off_t, int);
ssize_t      read(int, void *, size_t);
ssize_t      write(int, const void *, size_t);

#endif