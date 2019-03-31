#include <stdio.h>

int swap(int *a, int *b)
{
    int t = *a;
    printf("step 1: t = *a;\n");
    printf("*a is %d at %p\n", *a, a);
    printf("*b is %d at %p\n", *b, b);
    printf(" t is %d at %p\n", t, &t);
    *a = *b;
    printf("step 2: *a = *b;\n");
    printf("*a is %d at %p\n", *a, a);
    printf("*b is %d at %p\n", *b, b);
    printf(" t is %d at %p\n", t, &t);
    *b = t;
    printf("step 3: *b = t;\n");
    printf("*a is %d at %p\n", *a, a);
    printf("*b is %d at %p\n", *b, b);
    printf(" t is %d at %p\n", t, &t);
}

void main() 
{
    int x = 1;
    int y = 2;
    printf("Before swap:\n");
    printf(" x is %d at %p\n", x, &x);
    printf(" y is %d at %p\n", y, &y);
    printf("swap:\n");
    swap(&x, &y); //传地址
    printf("After swap:\n");
    printf(" x is %d at %p\n", x, &x);
    printf(" y is %d at %p\n", y, &y);
}
