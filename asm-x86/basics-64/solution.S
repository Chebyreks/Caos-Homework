    .intel_syntax noprefix
    .text
    .global very_important_function
    .global A

format_scanf:
  .string "%d"
format_printf:
  .string "%lld "

very_important_function:
    mov r9, 0

//NOT WORKING

loop:
    mov     rax, 0
    sub     rsp, 16
    mov     rsi, rax
    mov     rdi, format_scanf
    call    scanf
    add     rsp, 16
    imul    rax, [A+r9*4]
    mov     r10, rax


    sub     rsp, 16
    mov     rax, 0
    mov     rdi, format_scanf
    call    printf
    add     rsp, 16
    add     r9, 1
    cmp     r9, rdi
    jz      end
    jmp     loop

.end_loop:
    ret