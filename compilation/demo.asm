; 定义数据段，这是一个伪操作，用于告诉汇编器定义一块内存空间
section .data

; 定义数据段中的变量，这也是一个伪操作，所有对该变量的引用，都会被汇编器编译为内存地址
; DB 是伪指令，用于告诉汇编器，当前伪操作的每个操作数占用一个字节
; 0AH 用于写入一个换行符
STR_HELLO DB "Hello World!", 0AH

; 计算字符串的长度
; equ 伪指令，表示操作数是一个表达式
; $ 应该是当前变量的地址
; 由于数据段的内存是连续的，当前变量地址 - 上一个变量地址 = 上一个变量的长度
STRLEN equ $ - STR_HELLO

; 定义代码段，用于保存下面所有的汇编指令
section .text

; 定义程序入口，必须是“_start”
global _start
_start:
    ; 将变量 STRLEN 和 STR_HELLO 的地址分别放入寄存器 edx 和 ecx
    mov edx, STRLEN
    mov ecx, STR_HELLO

    ; 设置即将调用的 Linux 系统子功能号，4 表示 sys_write
    mov eax, 4
    ; 调用 Linux 的中断程序，开始执行指定的 Linux 子功能，当前进程暂停执行，由用户态转为内核态
    int 0x80

    ; 设置 Linux 系统子功能，1 表示 sys_exit
    mov eax, 1
    ; 设置进程的退出码
    mov ebx, 0
    ; 调用 Linux 的中断程序
    int 0x80
