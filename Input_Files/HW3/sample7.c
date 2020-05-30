#include <stdio.h>

void main() {
    int a;
    double b;
    a = 7;
    printf("%d\n", a);
    b = 8.0;
    printf("%f\n", b);
    a = 0;
    printf("%d\n", a);
    a = 1;
    printf("%d\n", a);
    b = 1.6;
    printf("%f\n", b);

    // =
    a = 2 + (2 - 4);
    printf("%d\n", a);
    a = 2 + (5 + 7);
    printf("%d\n", a);

    // -=
    a -= 1;
    printf("%d\n", a);
    a -= 2;
    printf("%d\n", a);
    a -= -23;
    printf("%d\n", a);
    a -= 0;
    printf("%d\n", a);
    a -= -2;
    printf("%d\n", a);
    a -= -78;
    printf("%d\n", a);
    a -= 11 + 3 - (9 + 32) - (2 + 3 + 3);
    printf("%d\n", a);
    a -= (4+(12-(3 * 1) + (4 * (2 / 2)))) * 0;
    printf("%d\n", a);
    a -= 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 +1 +1 -8 +1 -6 +1 +1;
    printf("%d\n", a);
    a -= 5 * (12-(3+8)*4);
    printf("%d\n", a);
    a -= 9 + (-1 * (13 - 4));
    printf("%d\n", a);
    a -= 2 - (5 + 7);
    printf("%d\n", a);

    // +=
    a = 2 + (2 - 4);
    printf("%d\n", a);
    a = 2 + (5 + 7);
    printf("%d\n", a);
    a += 1;
    printf("%d\n", a);
    a += 2;
    printf("%d\n", a);
    a = 9;
    printf("%d\n", a);
    a += -2;
    printf("%d\n", a);
    a += 0;
    printf("%d\n", a);
    printf("%d\n", a);
    a += 59;
    printf("%d\n", a);
    a += 1 + 1 + 1 + 1 + 1 + 1 - 1 + 1 + 1 +1 +1 -8 +1 -6 +1 +1 -1 + 3;
    printf("%d\n", a);

//     /=
    a = 4;
    printf("%d\n", a);
    a /= 1;
    printf("%d\n", a);
    a /= 1 + 1 + 1 + 1 + 1 + 1 - 1 + 1 + 1 +1 +1 -8 +1 -6 +1 +1 -1 + 3 + 1;
    printf("%d\n", a);
    a /= 2;
    printf("%d\n", a);
    a = 36;
    a /= (12 + 4 + 2);
    printf("%d\n", a);
    a = 25;
    a /= (3 * 2 -1);
    printf("%d\n", a);
    a = 8;
    a /= 2;
    printf("%d\n", a);
    a = 9;
    a /= 3;
    printf("%d\n", a);
    a = 8;
    a /= -2;
    printf("%d\n", a);
    b /= (1+2+3+4+5) / (1+2);
    printf("%f\n", b);
    a = 100;
    a/= (1+2+3+4+5) / (1+2);
    printf("%d\n", a);
    a /= ((1+2+3+4+5) / (1+2));
    printf("%d\n", a);

    // *=
    a *= 1;
    printf("%d\n", a);
    a *= 1 + 1 + 1 + 1 + 1 + 1 - 1 + 1 + 1 +1 +1 -8 +1 -6 +1 +1 -1 + 3 + 1;
    printf("%d\n", a);
    a *= 1 + 1 + 1 + 1 + 1 + 1 - 1 + 1 + 1 +1 +1 -8 +1 -6 +1 +1 -1 + 3 + 1 - 1;
    printf("%d\n", a);
    a *= 2;
    printf("%d\n", a);
    a = 9;
    printf("%d\n", a);
    a *= -2;
    printf("%d\n", a);
    a *= -1;
    printf("%d\n", a);
    a *= 0;
    printf("%d\n", a);
    a = 15;
    a *= 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 +1 +1 -8 +1 -6 +1 +1;
    printf("%d\n", a);
    a = 16;
    a *= 1+1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 +1 +1 -8 +1 -6 +1 +1;
    printf("%d\n", a);

    // +
    a = 1 + 1;
    printf("%d\n", a);
    a = 1 + 0;
    printf("%d\n", a);
    a = 0 + 1;
    printf("%d\n", a);
    a = 0 + 2;
    printf("%d\n", a);
    a = 1 + (1 + 0);
    printf("%d\n", a);
    a = a + 11;
    printf("%d\n", a);
    a = 11 + a;
    printf("%d\n", a);

    // -
    a = 5 - 1;
    printf("%d\n", a);
    a = 1 - 0;
    printf("%d\n", a);
    a = 0 - 1;
    printf("%d\n", a);
    a = 1 + (1 + -1) -1;
    printf("%d\n", a);
    a += 1 + (1 + -1) -1;
    a *= 1 + (1 + -1) -1;
    a -= 1 + (1 + -1) -1;
    printf("%d\n", a);
    b = 340 - 2*a;
    printf("%f\n", b);
    b = 340 - 2*a*0;
    printf("%f\n", b);

    // /
    a = 5 / 1;
    printf("%d\n", a);
    a = (1+2+3+4+5) / (1+2);
    printf("%d\n", a);
    a = 1 / 1;
    printf("%d\n", a);

    a = 0 / 456;
    printf("%d\n", a);
    a = (1+1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 +1 +1 -8 +1 -6 +1 +1 -1) / 456;
    printf("%d\n", a);
    a = 0 / 1 + (1 + -1) -1;
    printf("%d\n", a);

    // *
    a = 5 * 1;
    printf("%d\n", a);
    a = 1 * 1;
    printf("%d\n", a);
    a = 0 * 456;
    printf("%d\n", a);
    a = 456 * 0;
    printf("%d\n", a);
    a = 8 * (1 + (1 + -1) -1);
    printf("%d\n", a);

    // &&
    a = (1 && 1) || (0 && 1);
    printf("%d\n", a);
    a = 0 && 1;
    printf("%d\n", a);
    a = 1 && 0;
    printf("%d\n", a);
    a = (1&&1) && 0;
    printf("%d\n", a);
    a = 0 && (1&&1);
    printf("%d\n", a);
    a = 1 && 1;
    printf("%d\n", a);
    b = 1;
    a = b && 1;
    printf("%d\n", a);

    // ||
    a = 1 || 0;
    printf("%d\n", a);
    a = 1 || 1;
    printf("%d\n", a);
    a = 0 || 1;
    printf("%d\n", a);
    a = 0 || 0;
    printf("%d\n", a);
    a = (1 || 1) && (0 && 0);
    printf("%d\n", a);
    a = (1 || 0) || (1 && 1);
    printf("%d\n", a);
    a = (1 && 0) || (1 || 1);
    printf("%d\n", a);

    // ==
    printf("%d\n", 1 == 1);
    printf("%d\n", 1 == 2);
    a = 1;
    b = 2;
    printf("%d\n", a == 1);
    printf("%d\n", 2 == b);

    // >
    printf("%d\n", 1 > 2);
    printf("%d\n", 2 > 1);
    printf("%d\n", a > 1);
    printf("%d\n", 1 > a);
    printf("%d\n", b > a);
    printf("%d\n", a > b);
    // <
    printf("%d\n", 1 < 2);
    printf("%d\n", 2 < 1);
    printf("%d\n", a < 1);
    printf("%d\n", 1 < a);
    printf("%d\n", b < a);
    printf("%d\n", a < b);

    // <=
    printf("%d\n", 1 <= 2);
    printf("%d\n", 2 <= 1);
    printf("%d\n", 2 <= 2);
    printf("%d\n", a <= 1);
    printf("%d\n", 1 <= a);
    printf("%d\n", b <= a);
    printf("%d\n", a <= b);
    // >=
    printf("%d\n", 1 >= 2);
    printf("%d\n", 2 >= 1);
    printf("%d\n", 2 >= 2);
    printf("%d\n", a >= 1);
    printf("%d\n", 1 >= a);
    printf("%d\n", b >= a);
    printf("%d\n", a >= b);

    // !=
    printf("%d\n", 1 != 1);
    printf("%d\n", 1 != 2);
    a = 1;
    b = 2;
    printf("%d\n", a != 1);
    printf("%d\n", 2 != b);
    return;
}

