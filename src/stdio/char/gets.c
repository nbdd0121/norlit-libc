#include <stdio.h>
#include <limits.h>

char *gets(char *s) {
	return fgets(s, INT_MAX, stdin);
}
