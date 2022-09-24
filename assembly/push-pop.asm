; 打印每次 push 后 esp 减少的值

global main
extern printf, exit

section .bss
CACHE01 resb 4
CACHE02 resb 4
CACHE03 resb 4
CACHE04 resb 4
CACHE05 resb 4

section .data
RBP_FMT db "ebp: %p", 10, 0
RSP_FMT db "esp: %p", 10, 0
CACHE01_FMT db "CACHE01: %p", 10, 0
CACHE02_FMT db "CACHE02: %p", 10, 0
CACHE03_FMT db "CACHE03: %p", 10, 0
CACHE04_FMT db "CACHE04: %p", 10, 0
CACHE05_FMT db "CACHE05: %p", 10, 0

section .text
main:
    push ebp
    mov [CACHE01], esp

    mov eax, esp
    push eax
    mov [CACHE02], esp
    push RBP_FMT
    mov [CACHE03], esp
    call printf

    mov eax, esp
    push eax
    mov [CACHE04], esp
    push RSP_FMT
    mov [CACHE05], esp
    call printf

    mov eax, [CACHE01]
    push eax
    push CACHE01_FMT
    call printf

    mov eax, [CACHE02]
    push eax
    push CACHE02_FMT
    call printf

    mov eax, [CACHE03]
    push eax
    push CACHE03_FMT
    call printf

    mov eax, [CACHE04]
    push eax
    push CACHE04_FMT
    call printf

    mov eax, [CACHE05]
    push eax
    push CACHE05_FMT
    call printf

    push 0
    call exit
