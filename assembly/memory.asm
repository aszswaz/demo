; 未初始化的内存必须放在节 .bss 当中
section .bss
; 定义一块未初始化的内存
CACHE: resb 10

section .text

; 打印内存中的内容
print:
    mov edx, [esp + 8]
    mov ecx, [esp + 4]
    mov eax, 4
    int 0x80
    ret

global _start
_start:
    ; 向指定的内存地址写入一些数据，[...] 表示操作数是一个内存地址
    ; byte 表示写入内存的数据大小是一个字节
    mov byte [CACHE], 97
    mov byte [CACHE + 1], 'a'
    mov byte [CACHE + 2], 10
    push 10
    push CACHE
    call print

    ; 通过减法，将一个字母转为大写字母
    mov eax, [CACHE]
    sub eax, 32
    mov [CACHE], eax
    push 10
    push CACHE
    call print

    ; 退出程序
    mov eax, 1
    mov ebx, 0
    int 0x80
