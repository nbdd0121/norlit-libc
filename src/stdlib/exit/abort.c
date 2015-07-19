#include <signal.h>

void abort(void) {
	raise(SIGABRT);
	raise(SIGKILL);
	while (1);
}