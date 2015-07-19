long double sqrtl(long double x) {
	asm("fsqrt":"=t"(x):"0"(x));
	return x;
}