#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
void process(int ind, int max) {
    if (ind > max) {
        return;
    }
    pid_t pid = fork();
    if (pid == 0) {
        if (ind > 1) {
            printf(" %d", ind);
        } else {
            printf("%d", ind); 
        }
        fflush(stdout);
        ind++;
        process(ind, max);
        exit(0);
    } else {
        wait(NULL);
    }
    return;
}

int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);
    process(1, n);
    printf("\n");
    return 0;
}

