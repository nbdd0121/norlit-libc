float sinf(float x) {
	asm("fsin":"=t"(x):"0"(x));
	return x;
}