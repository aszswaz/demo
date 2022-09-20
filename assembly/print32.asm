section .text
mov eax, 0x10
jmp $

; 自定义数据段
section printdata
num db 3

; 自定义代码段
section printtext

; 导出 print，供其他模块使用
global print

print:
    ; 字符串长度
    mov edx,[esp+8]
    ; 设置要输出的字符串
    mov ecx,[esp+4]

    mov ebx, 1
    ; 设置系统子功能号，4:sys_write
    mov eax, 4
    ; 开始系统调用
    int 0x80
    ret
