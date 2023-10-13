#include <stdio.h>
#include <conio.h>

int main() {
    char ch;

    // 读取用户输入的按键，直到用户输入 ESC
    while ((ch = getch()) != 0x1B) {
        printf("code: %d\n", ch);
    }

    return 0;
}
