#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <endian.h>
#include <sys/stat.h>

int main() {
    char filename[128]; // Adjust size as needed
    struct stat st;
    int total_size = 0;
    char buffer = '0';
    int i = 0;
    int fd = open("test.txt", O_RDONLY);
    int bytes_read = 1;
    char filename_str[20];
    while (bytes_read != 0) {
        while (1) {
            bytes_read = read(fd, &buffer, sizeof(char));
            if (bytes_read == 0) {
                break;
            } else if (buffer == '\n') {
                break;
            }
            filename[i] = buffer;
            i++;
        }
        stat(filename, &st);
        if (S_ISREG(st.st_mode)) {
            total_size += st.st_size;
        }
        i = 0;
        buffer = '0';
    }
    int out = open("ans.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    char str[10];
    sprintf(str, "%d", total_size);
    write(out, str, strlen(str));
    close(out);
    close(fd);
}