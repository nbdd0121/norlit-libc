long double log1pl(long double x) {
	asm("fldln2; fxch; fyl2xp1":"=t"(x):"0"(x));
	return x;
}