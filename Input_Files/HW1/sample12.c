#include <stdio.h>

void main() {
	int x = 1;
	float y = 1.1;
	double z = 1.12345678;

	x = x || y;
	printf("%d\n", x);
	y = x || (z || y);
	printf("%f\n", y);
	z = (x || y) || (z || x);
	printf("%f\n", z);
	x = x && y;
	printf("%d\n", x);
	y = y && x;
	x = x == y;
	printf("%f\n", y);
	x = x == y;
	printf("%d\n", x);
	y = x != (z || y);
	printf("%f\n", y);
	z = !(x || y) == (z && x);
	printf("%f\n", z);
	z = !((x || y) == (z && x));
	printf("%f\n", z);
	x = x != y;
	printf("%d\n", x);
	y = x != (z == y);
	printf("%f\n", y);
	z = (x != y) != (z != x);
	printf("%f\n", z);
	x = x > y;
	printf("%d\n", x);
	y = x < (z > y);
	printf("%f\n", y);
	z = (x != y) > (z != x);
	printf("%f\n", z);
	x = x < y;
	printf("%d\n", x);
	y = x < (z < y);
	printf("%f\n", y);
	z = (x < y) > (z < x);
	printf("%f\n", z);
	x = x < y;
	printf("%d\n", x);
	printf("%f\n", x);
	y = x < (z <= y);
	printf("%f\n", y);
	z = (x <= y) > (z <= x);
	printf("%f\n", z);
	x = x <= y;
	printf("%d\n", x);
	y = x < (z <= y);
	printf("%f\n", y);
	z = (x <= y) >= (z < x);
	printf("%f\n", z);
    printf("%f\n", y);
	x = y++;
	printf("%f\n", x);
    printf("%f\n", y);
	x += 1;
	printf("%d\n", x);
	x++;
	printf("%d\n", x);
	++x;
	printf("%d\n", x);
	y = y++;
	printf("%f\n", y);
	y++;
	printf("%f\n", y);
	++y;
	printf("%f\n", y);
	z = z++;
	printf("%f\n", z);
	z++;
	printf("%f\n", z);
	++z;
	printf("%f\n", z);
	x = x--;
	printf("%d\n", x);
	x--;
	printf("%d\n", x);
	--x;
	x -= 2;
	printf("%d\n", x);
	printf("%d\n", x);
	y = y--;
	printf("%f\n", y);
	y--;
	printf("%f\n", y);
	--y;
	printf("%f\n", y);
	z = z--;
	printf("%f\n", z);
	z--;
	printf("%f\n", z);
	--z;
	printf("%f\n", z);
	return;
}