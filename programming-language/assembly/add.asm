; 从 C 调用 nasm 汇编函数的演示，函数调用在 c-demo.c 文件中
global add
add:
    push ebp
    mov ebp, esp
    mov edx, [ebp + 8]
    mov eax, [ebp + 12]
    add eax, edx
    pop ebp
    ret
