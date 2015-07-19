long double cosl(long double x) {
	asm("fcos":"=t"(x):"0"(x));
	return x;
}