#include <stdio.h>

void main() {

    // we have a bug with initialization in 1 line  but it looks like it's not important since it does not appear in
    // other input files
    int a;
    int b, c;
    double dA, dB, dC;
    a = 5;
    a -= 0;
    a += 0;
    a /= 1;
    a /= 0;
    a *= 1;
    a *= 14-12;

    return;
}

