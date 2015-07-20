#include "../internal.h"

int readMode(FILE* f) {
	if (f->bufmode == BUFMODE_READ)return 0;
	if (f->bufmode != BUFMODE_READ) {
		if (fflush(f) == EOF) {
			return 1;
		}
	}
	f->bufmode = BUFMODE_READ;
	return 0;
}
