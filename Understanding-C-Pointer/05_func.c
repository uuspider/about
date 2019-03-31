/* function pointer
* RESULTS:
##################################################
声明函数指针:
	int (*fp)(int, int);
为函数指针赋值:
	fp = func;
用指针调用子函数:
	fp(8, 9);
x * y is 72.
func is at 0x4007c8.
main is at 0x4005d6.
参数中含有函数指针的函数称为回调函数。
定义回调函数:
	int call(int (*fp)(int x, int y))
	{
		fp(5, 6);
	}
调用回调函数:
	call(func);
x * y is 30.
内存图如下:
	|                |V栈区
	+----------------+ main
 fp |        0x4007c8|
	+----------------+ &fp: 	0x7fff3158dd80
	:                :
	+----------------+ func
  i |             8/5|
	+----------------+
  j |             9/6|
	+----------------+
	:                :
	+----------------+ call
 fp |        0x4007c8|
	+----------------+ &fp: 	0x7fff3158dd80
	:                :
	+----------------+
	:                :
	+----------------+ call: 	0x4007f9
	:                :
	+----------------+ func: 	0x4007c8
	:                :
	+----------------+ main: 	0x4005d6
	|                |^代码区

##################################################
 */
#include <stdio.h>

int func(int, int);
int call(int (*fp)(int, int)); //回调函数

void main()
{
    printf("声明函数指针: \n\tint (*fp)(int, int);\n");
    int (*fp)(int, int);
    printf("为函数指针赋值:\n\tfp = func;\n");
    fp = func;
    printf("用指针调用子函数:\n\tfp(8, 9);\n");
    fp(8, 9);
    printf("func is at %p.\n", func);
    printf("main is at %p.\n", main);

    printf("参数中含有函数指针的函数称为回调函数。\n");
    printf("定义回调函数: \n\tint call(int (*fp)(int x, int y))\n\t{\n\t\tfp(5, 6);\n\t}\n");
    printf("调用回调函数: \n\tcall(func);\n");
    call(func);

    printf("内存图如下:\n");
    printf("\t|                |V栈区\n");
    printf("\t+----------------+ main\n");
    printf("     fp |%16p|\n", fp);
    printf("\t+----------------+ &fp: \t%p\n", &fp);
    printf("\t:                :\n");
    printf("\t+----------------+ func\n");
    printf("      i |             8/5|\n");
    printf("\t+----------------+\n");
    printf("      j |             9/6|\n");
    printf("\t+----------------+\n");
    printf("\t:                :\n");
    printf("\t+----------------+ call\n");
    printf("     fp |%16p|\n", fp);
    printf("\t+----------------+ &fp: \t%p\n", &fp);
    printf("\t:                :\n");
    printf("\t+----------------+\n");
    printf("\t:                :\n");
    printf("\t+----------------+ call: \t%p\n", call);
    printf("\t:                :\n");
    printf("\t+----------------+ func: \t%p\n", func);
    printf("\t:                :\n");
    printf("\t+----------------+ main: \t%p\n", main);
    printf("\t|                |^代码区\n");
}

int func(int i, int j)
{
    int sum = i * j;
    printf("x * y is %d.\n", sum);
    return sum;
}

int call(int (*fp)(int, int))
{
    fp(5, 6);
}
