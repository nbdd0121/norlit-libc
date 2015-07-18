long double fabsl(long double x) {
	asm("fabs":"=t"(x):"0"(x));
	return x;
}