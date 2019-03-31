/* function pointer
* RESULTS:
##################################################
定义函数指针:
	int (*fp)(int);
为函数指针赋值:
	fp = func;
用指针调用子函数:
	fp(8);
x^2 is 64.
func is at 0x400566.
main is at 0x400594.
##################################################
 */
#include <stdio.h>

int func(int i)
{
    int sum = i * i;
    printf("x^2 is %d.\n", sum);
    return sum;
}

void main()
{
    printf("定义函数指针: \n\tint (*fp)(int);\n");
    int (*fp)(int);
    printf("为函数指针赋值:\n\tfp = func;\n");
    fp = func;
    printf("用指针调用子函数:\n\tfp(8);\n");
    fp(8);
    printf("func is at %p.\n", func);
    printf("main is at %p.\n", main);
}
