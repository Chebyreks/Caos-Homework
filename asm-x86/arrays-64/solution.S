    .intel_syntax noprefix
    .text
    .global sum

sum:
    mov     r9, 0
    jmp loop

loop:
    mov     r10, [rsi+r9*4]
    mov     r11, [rdx+r9*4]
    add     r10, r11
    mov     [rcx+r9*4], r10
    add     r9, 1
    cmp     r9, rdi
    jz      end
    jmp     loop

end:
    ret