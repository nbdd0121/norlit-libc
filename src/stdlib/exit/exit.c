#include "internal.h"
#include <unistd.h>

void exit(int status) {
	for (int i = exit_reg_count - 1; i >= 0 ; i--) {
		exit_register[i]();
	}
	_exit(status);
}