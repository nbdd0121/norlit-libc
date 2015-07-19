float fabsf(float x) {
	asm("fabs":"=t"(x):"0"(x));
	return x;
}