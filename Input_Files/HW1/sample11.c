#include <stdio.h>


void main() {
    double a;
    int b;
    double e;
    int x;
    double f;
    f = 0;
    x = 1;
    b = 1;

    a = 1;
    printf("%f\n", a);
    printf("%f\n", a--);
    printf("%f\n", a);
    a = 5;

    printf("%f\n", a);
    e = a--; // if e = 4, a= 5, after this line, e = 5, a =4
    printf("%f\n", e);
    printf("%f\n", a);


    printf("%d\n", b++);
    printf("%f\n", --a);
    printf("%f\n", -e);
    a = 1;
    if (a--)
        printf("%f\n", f);
    else
        printf("%d\n", b);
    if (--a)
        printf("%d\n", ++x);
    x--;
    printf("%d\n", x);
    x = (x == 5) ? (11) : (22);
    printf("%d\n", x);
    ++x;
    printf("%d\n", x);
    for (a = 1; a >= 1; x--) {
        for (a = 1; a > 0; --x) {
            if (a-- > 0)
                printf("%d\n", x);
            if (x)
                printf("%d\n", x);
        }
    }
    printf("%d\n", x);
    a = 35;
    b = 550;
    a += b;
    printf("%.2f\n", a);
    a -= b;
    printf("%.2f\n", a);
    a -= 2;
    printf("%.2f\n", a);
    a += 3;
    printf("%.2f\n", a);
    a = 10.23;
    b = 20;
    a -= 0.23;
    a *= b;
    printf("%.2f\n", a);
    a /= b;
    printf("%.2f\n", a);
    a = 4;
    f = 5;
    printf("%.2f\n", a + f);
    a = f - 3;
    printf("%.2f\n", a);
    a = 3 - f;
    printf("%.2f\n", a);
    a = f + f;
    printf("%.2f\n", a);
    a = 1 + f;
    printf("%.2f\n", a);
    a = a * a;
    printf("%.2f\n", a);
    a = a / a;
    printf("%.2f\n", a);
    a = 6 / a;
    printf("%.2f\n", a);
    a = a / 12;
    printf("%.2f\n", a);
    a = 2 * a;
    printf("%.2f\n", a);
    a = a * 4;
    printf("%.2f\n", a);
    b = 1;
    do {
        printf("%.2f\n", --a);
        if (a && b) {
            printf("%d\n", 555);
        }
    } while (a || 0);

    for (a = 1; a < 3; a++) {
        if (!b)
            printf("%d\n", 111);
        b -= b;
    }
    a = 1;
    b = 1;
    if (a == b)
        printf("%.2f\n", a);
    if (a == 1)
        printf("%.2f\n", a + a);
    if (0 == a)
        printf("%.2f\n", a);
    if (a != b)
        printf("%.2f\n", a);
    if (a >= b)
        printf("%.2f\n", a * 4);
    while (a <= 2)
        printf("%.2f\n", ++a);

    a = 1;
    printf("%.2f\n", +a);

    return;
}
