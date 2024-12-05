#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <endian.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main(int argc, char* argv[]) {
    char* input_filename = argv[1];
    int input = open(input_filename, O_RDONLY);
    if (input == -1) {
        return 1;
    }
    struct stat st;
    fstat(input, &st);
    char* str_search = argv[2];
    int len = strlen(str_search);
    int size = st.st_size;
    char position_str[50];
    char* pointer = mmap(NULL, size, PROT_READ, MAP_PRIVATE, input, 0);
    for (int i = 0; i < size - len + 1; i++) {
        if (strncmp(pointer + i, str_search, len) == 0) {
            sprintf(position_str, "%d", i);
            write(1, &position_str, strlen(position_str));
            write(1, &" ", 1);
        }
    }
    munmap(pointer, size);
    close(input);
}