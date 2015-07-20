#include "../internal.h"

int feof(FILE *stream) {
	return stream->flags & FLAG_EOF;
}