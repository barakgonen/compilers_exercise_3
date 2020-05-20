#include <stdio.h>

int a;
void main() {
	int b = 1111;
	int c = 2222;
	int d = 3333;
	int e = 4444;
	a = 5555;
	a -= b;
	c +=b;
	d *= a;
	e /= b;

	printf("%d\n", a);
	printf("%d\n", c);
	printf("%d\n", d);
	printf("%d\n", e);
	printf("%d\n", b);
	return;
}