global main
extern printf, exit

section .data
FORMAT: db "%s", 10, 0
EQUAL_MSG: db "eax == ebx", 0
LESS_MSG: db "eax < ebx", 0
GREATER_MSG: db "eax > ebx", 0
ELSE_MSG: db "None of the conditions were hit.", 0

section .text
main:
    push ebp

    mov eax, -100
    mov ebx, -1
    ; cmp 是比较指令，它将目标操作数减去源操作数，并根据结果，修改 Flags 寄存器。它不会修改任何操作数，即便该操作数是寄存器或内存地址
    cmp eax, ebx

    ; eax == ebx 时转移
    je equal
    ; eax < ebx 时转移
    jl less
    ; eax > ebx 时转移
    ja greater
    ; 所有条件都不满足时，进行无条件转移
    jmp else

equal:
    push EQUAL_MSG
    push FORMAT
    call printf
    add esp, 8
    jmp end

less:
    push LESS_MSG
    push FORMAT
    call printf
    add esp, 8
    jmp end

greater:
    push GREATER_MSG
    push FORMAT
    call printf
    add esp, 8
    jmp end

else:
    push ELSE_MSG
    push FORMAT
    call printf
    add esp, 8
    jmp end

end:
    push 0
    call exit
