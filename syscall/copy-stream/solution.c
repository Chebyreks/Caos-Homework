extern long syscall(long number, ...);

void _start(void) {
    char buffer[16];
    long amount_to_read = 16;
    int is_working = 1;
    while (is_working) {
        int amount_read = syscall(0, 0, buffer, amount_to_read);
        if (amount_read == 0) {
            is_working = 0;
        } else {
            syscall(1, 1, buffer, amount_read);
        }
    }
    syscall(60);
}