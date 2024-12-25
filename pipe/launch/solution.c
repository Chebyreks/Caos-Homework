#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char* cmd = argv[1];
    char* input_file = argv[2];
    int pipefd[2];
    pid_t pid;
    pipe(pipefd);
    pid = fork();
    if (pid == 0) {
        int fd_in = open(input_file, O_RDONLY); 
        dup2(fd_in, STDIN_FILENO);
        close(fd_in);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        execlp("/bin/sh", "sh", "-c", cmd, NULL);
        exit(0);
    } else {
        close(pipefd[1]);
        char buffer[2048];
        ssize_t bytes_read;
        size_t total_bytes = 0;
        wait(NULL);
        while ((bytes_read = read(pipefd[0], buffer, 2048)) > 0) {
            total_bytes += bytes_read;
        }
        close(pipefd[0]);
        printf("%ld\n", total_bytes);
    }
    return 0;
}
