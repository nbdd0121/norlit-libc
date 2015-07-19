long double logbl(long double x) {
	asm("fxtract;fstp %%st":"=t"(x):"0"(x));
	return x;
}