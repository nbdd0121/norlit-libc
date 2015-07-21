#include "../internal.h"
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>

int translateFlags(const char *mode) {
	int flags = 0;
	switch (mode[0]) {
		case 'r':
			flags = O_RDONLY;
			break;
		case 'w':
			flags |= O_WRONLY | O_CREAT | O_TRUNC;
			break;
		case 'a':
			flags |= O_WRONLY | O_CREAT | O_APPEND;
			break;
		default:
			return -1;
	}

	bool b = false;
	for (int i = 1; mode[i]; i++) {
		switch (mode[i]) {
			case '+':
				if ((flags & O_ACCMODE) == O_RDWR)
					return -1;
				flags = (flags & ~O_ACCMODE) | O_RDWR;
				break;
			case 'b':
				if (b)
					return -1;
				b = true;
				break;
			case 'x':
				if ((flags & O_EXCL) || mode[0] != 'w')
					return -1;
				flags |= O_EXCL;
				break;
			default:
				return -1;
		}
	}

	return flags;
}