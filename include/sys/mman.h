#ifndef _NORLIT_SYS_MMAN_H
#define _NORLIT_SYS_MMAN_H

#include <sys/types.h>

#define PROT_NONE   0
#define PROT_READ   1
#define PROT_WRITE  2
#define PROT_EXEC   4

#define MAP_PRIVATE 0x0000

void  *mmap(void *, size_t, int, int, int, off_t);
int    munmap(void *, size_t);

#endif