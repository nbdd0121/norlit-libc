#include <stdio.h>

FILE** __get_std_streams(void) {
	static FILE* stdstreams[3] = {};
	if (!stdstreams[0]) {
		stdstreams[0] = fdopen(0, "r");
		setvbuf(stdstreams[0], NULL, _IOLBF, BUFSIZ);
		stdstreams[1] = fdopen(1, "w");
		setvbuf(stdstreams[1], NULL, _IOLBF, BUFSIZ);
		stdstreams[2] = fdopen(2, "w");
		setvbuf(stdstreams[2], NULL, _IONBF, 0);
	}
	return stdstreams;
}