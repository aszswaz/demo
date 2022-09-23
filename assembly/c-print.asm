; 从 nasm 汇编调用 C 的 printf 函数

global main
extern printf, exit

section .text
main:
    push MESSAGE
    push FORMAT
    call printf

    push 0
    call exit

FORMAT: db "%s", 10, 0
MESSAGE: db "Hello World", 0
