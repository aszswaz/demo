section .bss
resb 64

; 自定义数据段，未使用“传统”的数据段 .data
section maindata
; 在数据段中存放一个字符串，OA 是一个换行符
strHello db "Hello World!", 0AH
STRLEN equ $ - strHello

; 自定义代码段，未使用“传统”的代码段 .txt
section maintext
; 声明此函数在别的文件中
extern print

; 声明程序入口，只能是 _start
global _start

_start:
    ; 传入参数，字符串的长度
    push STRLEN
    ; 传入参数，待打印的字符串
    push strHello
    ; 调用外部函数
    call print
    ; 函数调用完毕，继续执行
    ; 设置程序返回值（exit code）
    mov ebx, 0
    ; 设置系统子功能调用号，1: sys_exit
    mov eax, 1
    ; 触发中断，执行系统调用
    int 0x80
