#include <sys/syscall.h>  
    .intel_syntax noprefix
    .text
    .global _start

//NOT WORKING

_start:
    sub rsp, 64
    push 0

read:

    mov rax, SYS_read
    mov rdi, 0
    mov rsi, rsp
    mov rdx, 64

    syscall

    cmp rax, 0
    je write
    push rsi
    push rax
    jmp read

write:
    pop rax
    cmp rax, 0
    je end
    pop rsi
    mov rdx, rax
    mov rax, SYS_write
    mov rdi, 1
    syscall

    
    jmp write

end:
    add rsp, 64
    mov rax, SYS_exit
    mov rdi, 0
    syscall
