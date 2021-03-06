/* array as parameter deliver to function
 * REAULT:
####################################################################
Size of a in main is 20 bytes. 这是系统分配给数组的内存容量。
Size of a in func is  8 bytes. 这是数组首地址，也就是指针的长度，编译器会发出警告:
	warning: ‘sizeof’ on array function parameter ‘a’ will return size of ‘int *’ [-Wsizeof-array-argument]
*(a + 0) is 1
*(a + 1) is 2
*(a + 2) is 3
*(a + 3) is 4
*(a + 4) is 5
[注意] 数组作为子函数参数时，实际传递的都是地址，应该使用指针接收。
如:"int func(int a[5])"等同于"int func(int *a)."
####################################################################
 * ex: 练习数组指针
#include <stdio.h>

int func(int (*a)[3], int (*b)[2])
{
    int i = 0;
    int j = 0;
    for (i = 0; i < 2; i++)
        for (j = 0; j < 3; j++)
            b[j][i] = a[i][j];
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 2; j++)
            printf("%d\t", b[i][j]);
        printf("\n");
    }
}

int main() 
{
    int a[2][3] = { 1, 3, 5, 4, 6, 8 };
    int b[3][2] = {0};

    func(a, b);
}
####################################################################
 * ex: 练习向main传递参数
#include <stdio.h>

main(int ac, char *av[])
{
    int i;
    for (i = 1; i < ac; i++)
        printf("%s%s", av[i], (i < ac-1)?" ":"\n");
    return 0;
}
####################################################################
 */
#include <stdio.h>

int func(int a[5])
{
    printf("Size of a in func is  %ld bytes. 这是数组首地址，也就是指针的长度，编译器会发出警告:\n", sizeof(a));
    printf("\twarning: ‘sizeof’ on array function parameter ‘a’ will return size of ‘int *’ [-Wsizeof-array-argument]\n");
    int i = 0;
    for (i = 5; i > 0; i--)
        *(a + i -1) = i;
}

int main() 
{
    int a[5];
    printf("Size of a in main is %ld bytes. 这是系统分配给数组的内存容量。\n", sizeof(a));

    func(a);

    int i =0;
    for (i = 0; i < 5; i++)
        printf("*(a + %d) is %d\n", i, *(a + i));

    printf("[注意] 数组作为子函数参数时，实际传递的都是地址，应该使用指针接收。\n如:\"int func(int a[5])\"等同于\"int func(int *a).\"\n");
}
    
