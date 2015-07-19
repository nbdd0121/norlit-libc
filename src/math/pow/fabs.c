double fabs(double x) {
	asm("fabs":"=t"(x):"0"(x));
	return x;
}