#include "../internal.h"

int ferror(FILE *stream) {
	return stream->flags & FLAG_ERR;
}