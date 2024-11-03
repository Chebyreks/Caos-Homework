#include <sys/syscall.h>  
    .intel_syntax noprefix
    .text
    .global _start

_start:
    sub rsp, 16

read:
    mov rax, SYS_read
    mov rdi, 0
    mov rsi, rsp
    mov rdx, 16
    syscall
    
    cmp rax, 0
    je end

    mov rdx, rax
    mov rax, SYS_write
    mov rdi, 1
    mov rsi, rsp
    syscall

    jmp read

end:
    add rsp, 16
    mov rax, SYS_exit
    mov rdi, 0
    syscall
