; 未初始化的内存必须放在节 .bss 当中
section .bss
; 定义一块未初始化的内存
CACHE: resb 10
CACHE_LEN: equ $ - CACHE
BUFFER: resb 8192

section .data
MESSAGE: db "Hello World", 10
MESSAGE_LEN: equ $ - MESSAGE

section .text

; 打印内存中的内容
print:
    push ebp
    mov ebp, esp

    mov edx, [esp + 8]
    mov ecx, [esp + 12]
    mov eax, 4
    int 0x80

    leave
    ret

global _start
_start:
    push ebp
    mov ebp, esp

    ; 向指定的内存地址写入一些数据，[...] 表示操作数是一个内存地址
    ; byte 表示写入内存的数据大小是一个字节
    mov byte [CACHE], 97
    mov byte [CACHE + 1], 'a'
    mov byte [CACHE + 2], 10
    push CACHE
    push CACHE_LEN
    call print
    add esp, 8

    ; 通过减法，将一个字母转为大写字母
    mov eax, [CACHE]
    sub eax, 32
    mov [CACHE], eax
    push CACHE
    push CACHE_LEN
    call print
    add esp, 8

    ; 通过 movsb 指令族复制内存
    ; 设置源内存地址，段寄存器是 DS
    mov esi, MESSAGE
    ; 设置源内存地址，段寄存器是 ES
    mov edi, BUFFER
    ; 设置要复制的内存大小
    mov ecx, MESSAGE_LEN
    ; 开始复制内存
    ; rep 是重复执行指定的指令，重复次数通过 ecx 指定
    ; movsb 是每次复制一个字节，并且 esi 自动加 1
    rep movsb
    push BUFFER
    push MESSAGE_LEN
    call print
    add esp, 8

    ; 退出程序
    mov eax, 1
    mov ebx, 0
    int 0x80
