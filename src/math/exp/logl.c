long double logl(long double x) {
	asm("fldln2; fxch; fyl2x":"=t"(x):"0"(x):"st(1)");
	return x;
}