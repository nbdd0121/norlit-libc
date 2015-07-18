long double sinl(long double x) {
	asm("fsin":"=t"(x):"0"(x));
	return x;
}