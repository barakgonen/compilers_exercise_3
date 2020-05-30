#include <stdio.h>

void main() {
    int x;
    int a;
    a = 5;

    x += ((5 + 3 - 2 * 7) * 0);
    x *= (15 - 14);
    x *= (15 - 15);
    x *= (a * 0);
    x += (2 > 1 ? 0 : 1);
     x = 0 / a;
//    x = 0 * a;          // MUST FIXME
//    x = a * 0;          // MUST FIXME
//    x = (13*2)==(2<4);
//    x = (a&&1)+(a&&0)+(a||1)+(a||0); // MUST FIXME
//    x = (0&&a) +(1&&a) +(1||a)+(0||a);// MUST FIXME
//    x=(a*1)+(0/b);// MUST FIXME
//    x=10+34;
//    X=10+(a*0?1:2);// MUST FIXME
//    x-=10-(a*0?1:10); // MUST FIXME
//    x-=10-(a<0?1:10);// MUST FIXME
//    x-=(10*2*3)-(a<0?1+2:10-1); // MUST FIXME
//    x/=(10*2*3)+(a/a)+(a-(3-2) * a); // MUST FIXME
//    a *= (5-5)*9;
    return;
}

