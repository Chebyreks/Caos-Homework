#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    char* com1 = argv[1];
    char* com2 = argv[2];
    int pipefd[2];
    pid_t pid1, pid2;
    pipe(pipefd);   
    pid1 = fork(); 
    if (pid1 == 0) {
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        execlp("sh", "sh", "-c", com1, NULL);
        fflush(stdout);
        exit(0);
    } 
    pid2 = fork();  
    if (pid2 == 0) {
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[1]);
        execlp("sh", "sh", "-c", com2, NULL);
        fflush(stdout);
        exit(0);
    }
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return 0;
}