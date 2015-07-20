#include <stdio.h>
#include <string.h>
#include <errno.h>

void perror(const char* s) {
	fputs(s, stderr);
	fputs(": ", stderr);
	fputs(strerror(errno), stderr);
	fputc('\n', stderr);
}