float log1pf(float x) {
	asm("fldln2; fxch; fyl2xp1":"=t"(x):"0"(x):"st(1)");
	return x;
}