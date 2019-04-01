/* string.c
 * 以字符串练习函数指针、回调函数等
 * 字符串是一个以\0结束的数组
 * 字符串等常量存储在常量区
 * 变量存储在栈区
 * 函数存储在代码区
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int count(char *, int *, int *, int *);
int call(int (*)(char *, int *, int *, int *), char *, int *, int *, int *);

int main(int ac, char *av[])
{
    if (ac == 1) {
        printf("请在命令行后输入字符串，用单引号括起来\n");
        exit(0);
    }

    char *p = av[1];
    int number = 0;
    int letter = 0;
    int symbol = 0;

    call(count, p, &number, &letter, &symbol);
    printf("number: %d\tletter: %d\tsymbol: %d\n", number, letter, symbol);
}

int count(char *p, int *n, int *l, int *s)
{
    for (; *p != '\0'; p++) {
        if ((*p >= 65) && (*p <=90))
            (*l)++;
        else if ((*p >= 97) && (*p <= 122))
            (*l)++;
        else if ((*p >= 48) && (*p <= 57))
            (*n)++;
        else
            (*s)++;
    }
}

int call(int (*fp)(char *, int *, int *, int *), char *p, int *n, int *l, int *s)
{
    fp(p, n, l, s);
}

