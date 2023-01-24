; 64 位的 printf 使用寄存器 rdi、rsi、rdx、rcx、r8、r9 传递参数

global main
extern printf, exit

section .data
FMT db "%s", 10, 0
MESSAGE db "Hello World"

section .text
main:
    push rbp

    mov rdi, FMT
    mov rsi, MESSAGE
    call printf

    mov rdi, 0
    call exit
