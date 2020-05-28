#include <stdio.h>

void main() {
    int a;
    double b;
    a = 7;
    printf("%d\n", a);
    a = 8.0;
    printf("%d\n", a);
    a = 0;
    printf("%d\n", a);
    a = 1;
    printf("%d\n", a);
    b = 1.6;
    printf("%f\n", b);
    a = 2 + (2 - 4);
    printf("%d\n", a);
    a = 2 + (5 + 7);
    printf("%d\n", a);
//    a -= 0;
//    a += 0;
//    a += 2 + (2 - 4); // should not write anything
//    a /= 1;
//    a /= 0;
//    a *= 1;
//    a *= 14-12;
//
//    a += (14 - 15) + (-1 + 2) / 1;

    return;
}

