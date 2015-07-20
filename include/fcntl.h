#ifndef _NORLIT_LIBC_FCNTL_H
#define _NORLIT_LIBC_FCNTL_H

// This is a stub

int open(const char*, int, ...);

#define O_EXEC   0
#define O_RDONLY 1
#define O_RDWR   2
#define O_SEARCH 3
#define O_WRONLY 4

#define O_APPEND    8
#define O_CLOEXEC   16
#define O_CREAT     32
#define O_DIRECTORY 64
#define O_DSYNC     128
#define O_EXCL      256
#define O_NOCTTY    512
#define O_NOFOLLOW  1024
#define O_NONBLOCK  2048
#define O_RSYNC     0x1000
#define O_SYNC      0x2000
#define O_TRUNC     0x4000
#define O_TTY_INIT  0x8000

#endif
