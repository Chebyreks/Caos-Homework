#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_WORDS 255
#define WORD_SIZE 4096

int main() {
    int pipefd[2];
    pid_t pid;
    int word_count = 0;
    char word[WORD_SIZE];
    pipe(pipefd);
    while (word_count < MAX_WORDS) {
        pid = fork();
        if (pid == 0) {
            close(pipefd[0]);
            while(scanf("%s", word) == 1){
                 write(pipefd[1], "1", 1);
            }
            close(pipefd[1]);
            exit(0);
        } else {
            close(pipefd[1]); 
            char buf[1];
            while (read(pipefd[0], buf, 1) > 0){
                if (buf[0] == '1') {
                    word_count++;
                }
            }
            close(pipefd[0]);
            break;
        }
    }
    close(pipefd[0]);
    close(pipefd[1]);
    printf("%d\n", word_count);
    return 0;
}
