float sqrtf(float x) {
	asm("fsqrt":"=t"(x):"0"(x));
	return x;
}