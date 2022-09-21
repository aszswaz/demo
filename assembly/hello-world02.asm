global _start

section .data
message: db "Hello World", 10

section .text
_start:
    ; syscall for write
    mov rax, 1
    ; file handle 1 is stdout
    mov rdi, 1
    ; address of string to output
    mov rsi, message
    ; number of bytes
    mov rdx, 13
    ; invoke operating system to do the write
    syscall

    ; system call for exit
    mov rax, 60
    ; exit code 0
    mov rdi, 0
    ; invoke operating system to exit
    syscall
