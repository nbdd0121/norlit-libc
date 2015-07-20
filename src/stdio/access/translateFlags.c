#include "../internal.h"
#include <string.h>
#include <fcntl.h>

int translateFlags(const char *mode) {
	int flags;
	if (strchr(mode, '+')) {
		flags = O_RDWR;
	}
	switch (mode[0]) {
		case 'r':
			if (!flags)
				flags = O_RDONLY;
			break;
		case 'w':
			if (!flags)
				flags = O_WRONLY;
			flags |= O_CREAT | O_TRUNC;
			if (strchr(mode, 'x'))
				flags |= O_EXCL;
			break;
		case 'a':
			if (!flags)
				flags = O_WRONLY;
			flags |= O_CREAT | O_APPEND;
			break;
		default:
			return -1;
	}
	return flags;
}