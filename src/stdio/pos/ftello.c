#include "../internal.h"

off_t ftello(FILE* f) {
	off_t pos = f->seek(f, 0, SEEK_CUR);
	if (pos < 0) return -1;

	if (f->bufpolicy != _IONBF) {
		if (f->bufmode == BUFMODE_READ) {
			pos -= f->buflim - f->bufpos;
		} else if (f->bufmode == BUFMODE_WRITE) {
			pos += f->bufpos;
		}
	} else if (f->bufpos != -1) {
		pos--;
	}

	return pos;
}