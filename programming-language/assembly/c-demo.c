#include <stdio.h>

/**
 * 从 C 调用 nasm 汇编函数的演示，函数的实现在 add.asm 文件中
 */

int add(int, int);

int main() {
    printf("%d\n", add(5, 6));
    return 0;
}
