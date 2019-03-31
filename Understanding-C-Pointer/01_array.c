#include <stdio.h>

void main()
{
    int a[5] = {11, 12, 23, 34, 45};
    printf("定义数组:\n\tint a[5] = {11, 12, 23, 34, 45};\n");
    printf("[注意] 数组名代表了数组的首地址。\n");
    printf("a的首地址:\t%p\ta[0]的值:\t%d\n", a, *(a+0));
    printf("a[1]的地址:\t%p\ta[1]的值:\t%d\n", a+1, *(a+1));
    printf("a[2]的地址:\t%p\ta[2]的值:\t%d\n", a+2, *(a+2));
    printf("a[3]的地址:\t%p\ta[3]的值:\t%d\n", a+3, *(a+3));
    printf("a[4]的地址:\t%p\ta[4]的值:\t%d\n", a+4, *(a+4));
    printf("数组a占用内存:\t%ld bytes\n", sizeof(a));

    int * p;
    printf("定义指针:\n\tint * p;\n");
    p = a;
    printf("为指针赋值:\n\tp = a;\n");
    printf("[注意] a是地址常量，指针不是地址！指针是用于存储地址的变量。\n");
    printf("p+0指向的地址:\t%p\t存储的值:\t%d\n", p+0, *(p+0));
    printf("p+1指向的地址:\t%p\t存储的值:\t%d\n", p+1, *(p+1));
    printf("p+2指向的地址:\t%p\t存储的值:\t%d\n", p+2, *(p+2));
    printf("p+3指向的地址:\t%p\t存储的值:\t%d\n", p+3, *(p+3));
    printf("p+4指向的地址:\t%p\t存储的值:\t%d\n", p+4, *(p+4));

    printf("指针是用于存储地址的变量，指针也有地址:\n\t&p\n");
    printf("指针p的地址:\t%p\t存储的值:\t%p\n", &p, p);
    printf("指针p占用内存:\t%ld bytes\n", sizeof(p));
    printf("对a取址:\n\t&a\n");
    printf("a的首地址:\t%p\t&a:\t\t%p\n", a, &a);
    printf("[注意] a和&a是一样的!\n");

    printf("数组a的内存图如下:\n");
    printf("\t+----------------+\n");
    printf("\t+%16d+\n",*(p+4));
    printf("\t+----------------+ a+4:\t%p\n", p+4);
    printf("\t+%16d+\n",*(p+3));
    printf("\t+----------------+ a+3:\t%p\n", p+3);
    printf("\t+%16d+\n",*(p+2));
    printf("\t+----------------+ a+2:\t%p\n", p+2);
    printf("\t+%16d+\n",*(p+1));
    printf("\t+----------------+ a+1:\t%p\n", p+1);
    printf("\t+%16d+\n",*(p+0));
    printf("\t+----------------+ a:\t%p\n", p);
    printf("\t+%16p+\n",p);
    printf("\t+----------------+ p:\t%p\n", &p);




}


