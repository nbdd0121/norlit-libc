double log2(double x) {
	asm("fld1; fxch; fyl2x":"=t"(x):"0"(x));
	return x;
}