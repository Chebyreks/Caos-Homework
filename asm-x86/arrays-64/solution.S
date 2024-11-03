    .intel_syntax noprefix
    .text
    .global sum

sum:
    mov     r9, 0
    jmp loop

loop:
    mov     eax, [rsi+r9*4]
    add     eax, [rdx+r9*4]
    mov     [rcx+r9*4], eax
    add     r9, 1
    cmp     r9, rdi
    jz      end
    jmp     loop

end:
    ret