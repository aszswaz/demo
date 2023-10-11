global main
extern printf, exit

section .data
FMT01 db "2 * 8 = %d", 10, 0

section .text
main:
    push rbp
    mov rbp, rsp

    mov rax, 0
    mov rbx, 0

    mov al, 2
    mov bl, 8
    mul bl

    mov rdi, FMT01
    mov rsi, rax
    call printf

    mov rdi, 0
    call exit
