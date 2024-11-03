extern long syscall(long number, ...);

void _start(void) {
    const char msg[] = "Hello, World!\n";
    int msg_len = sizeof(msg) - 1;
    syscall(1, 1, msg, msg_len);
    syscall(60);
}