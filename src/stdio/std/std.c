#include "../internal.h"

FILE** __get_std_streams(void) {
	static FILE* stdstreams[3] = {};
	if (!stdstreams[0]) {
		stdstreams[0] = fdopen(0, "r");
		stdstreams[0]->bufmode = _IOLBF;
		stdstreams[1] = fdopen(1, "w");
		stdstreams[1]->bufmode = _IOLBF;
		stdstreams[2] = fdopen(2, "w");
		stdstreams[2]->bufmode = _IONBF;
	}
	return stdstreams;
}