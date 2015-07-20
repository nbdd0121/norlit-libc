#include "../internal.h"

void clearerr(FILE *stream) {
	stream->flags &= ~(FLAG_ERR | FLAG_EOF);
}