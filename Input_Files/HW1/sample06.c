#include <stdio.h>

void main() {
	double a;
    double b;
	a = 5.5;
	b = 87;
	printf("%d\n", !5.18);
	printf("%d\n",(((a < 6.0) || (a > 7.0)) && (a == 6.0)) || 0);
	printf("%d\n",(((a <= 6.0) || (a >= 7.0)) && (a != 6.0)) || 8.8);
	printf("%.2f\n", - a);
	printf("%.2f\n", (((a + b) + 6.5) - 6.5) * 6.5 / 6.5);
    printf("%.2f\n", ((a + 6.5) - 6.5) * 6.5 / 6.5);
    printf("%.2f\n", ((a + 7.5) - 6.5) * 6.5 / 6.5);
    printf("%.2f\n", (a + (7.5 - 6.5)) * 6.5 / 6.5);
    printf("%.2f\n", (a + (8.5 - 6.5)) * 6.5 / 6.5);
    printf("%.2f\n", (a + (8.4 - 6.5)) * 6.5 / 6.5);
	return;
}