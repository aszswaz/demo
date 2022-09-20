; 内存读写操作演示

section .bss
CACHE resb 10

section .text
global _start
_start:
    mov byte [CACHE], 97
    mov byte [CACHE + 1], 'a'
    mov byte [CACHE + 2], 10

    ; 打印内存
    mov edx, 10
    mov ecx, CACHE
    mov eax, 4
    int 0x80

    ; 退出程序
    mov eax, 1
    mov ebx, 0
    int 0x80
