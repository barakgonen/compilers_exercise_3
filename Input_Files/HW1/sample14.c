#include <stdio.h>

void main() {
    float a;
    int b;
    double e;
    int x;
    float f;
    f=0;
    x=1;
    b=1;
    a = 5;
    e = a--;
    printf("%.2f\n",e);
    printf("%d\n",b++);
    printf("%.2f\n",--a);
    printf("%.2f\n",-e);
    a=1;
    if (a--)
        printf("%d\n",x++);
    else
        printf("%d\n",++x);
    if (--a)
        printf("%d\n",++x);

    a=1;
    b=1;
    if(a==b)
        printf("%.2f\n",a);
    if(a==1)
        printf("%.2f\n",a+a);
    if(0==a)
        printf("%.2f\n",a);
    if(a!=b)
        printf("%.2f\n",a);
    if(a>=b)
        printf("%.2f\n",a*4);
    while (a<=2)
        printf("%.2f\n",++a);

    a=1;
    printf("%.2f\n",1+a);

	return;
}