; 导出 print，供其他模块使用
global print

; 自定义代码段
section .text
print:
    ; 创建栈帧
    ; 备份上一层函数的堆栈地址
    push ebp
    ; 将 ebp 更新为当前对战地址
    mov ebp, esp

    ; 字符串长度
    mov edx,[ebp+8]
    ; 设置要输出的字符串
    mov ecx,[ebp+12]

    ; 设置系统子功能号，4:sys_write
    mov eax, 4
    ; 开始系统调用
    int 0x80

    ; 即将离开函数，销毁栈帧
    ; 跳过局部变量的空间（如果有）
    ; mov esp, ebp
    ; pop ebp
    ; 上述两条指令可以使用 leave 代替
    leave
    ret
