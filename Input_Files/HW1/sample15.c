#include <stdio.h>

void main() {
    double x = 1;
    float a;
    float y = 7.7;
    float b;
    printf("%f\n", x);
    printf("%f\n", y);
    x = ++y;
    printf("%f\n", x);
    printf("%f\n", y);
    x = ++x;
    printf("%f\n", x);
    printf("%f\n", y);
    x = y++;
    printf("%f\n", x);
    printf("%f\n", y);
    x = x++;
    printf("%f\n", x);
    printf("%f\n", y);
    b = 1;
    a = 15 * b;
    printf("%f\n", a);
    a = b * 15;
    printf("%f\n", a);
    a = 1 * 15;
    printf("%f\n", a);
    b = 1.1 * 15.5;
    printf("%f\n", b);
    a = b * 5;
    printf("%f\n", a);
    printf("%f\n", b);
    b *= a;
    printf("%f\n", b);
    printf("%f\n", a);
    b = 5 * b;
    printf("%f\n", b);
    printf("%f\n", a);
    b = a * 5;
    printf("%f\n", b);
    a = 12;
    b = 24.5;
    b *= a;
    printf("%f\n", b);
    printf("%f\n", a);
    a *= b;
    printf("%f\n", b);
    printf("%f\n", a);
    if (a <= b)
        printf("%f\n", a * 4);
    if (a >= b)
        printf("%f\n", a * 4);
    printf("%f\n", b);
    printf("%f\n", a);
    if (a >= b)
        printf("%f\n", a * b);
    if (a >= b)
        printf("%f\n", b * a);
    if (a >= b)
        printf("%f\n", 4 * a);
    printf("%f\n", x);
    x = y++;
    printf("%f\n", y);
    printf("%f\n", x);
    printf("%f\n", y);
    b=1;
    printf("%f\n",b++);
    printf("%f\n", b);
    printf("%f\n",++b);
    printf("%f\n",b);
    printf("%f\n",--a);
    printf("%f\n", a);
    printf("%f\n",a--);
    printf("%f\n", a);
    b = b * -1.1;
    printf("%f\n", b);
    b = 1.5;
    b = -2.5 * b;
    printf("%f\n", b);
    x *= (b*-213) + 16;
    printf("%f\n", b);
    b = (-b) * (-(-b));
    printf("%f\n", b);
    b = 1;
    b -= -b/(-234.4);
    printf("%f\n", b);
    x = 10;
    b = -2;
    x+=x/b+12;
    printf("%f\n", x);
    printf("%f\n", b);
    b/=(-123/x)-1000;
    printf("%f\n",b);
    b/=(b*-12)/(-11);
    printf("%f\n",b);
    printf("%f\n",x);
    b/=x++;
    printf("%f\n",b);
    printf("%f\n",x);
    return;
}
