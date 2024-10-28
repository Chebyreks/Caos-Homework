    .text
    .global sum

sum:
    mov     x3, #0
    mov     x4, #0
    b       loop

loop:
    ldr     x5, [x2, x4]
    add     x4, x4, #4
    add     x0, x0, x5
    add     x3, x3, #1
    cmp     x1, x3
    b.eq end

    b loop

end:
    ret