float tanf(float x) {
	asm("fptan;fstp %%st":"=t"(x):"0"(x));
	return x;
}