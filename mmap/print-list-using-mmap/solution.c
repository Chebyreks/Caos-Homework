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
    int size = st.st_size;

    int32_t buffer;
    uint32_t pointer_buffer;
    ssize_t bytes_read;
    int pointer_next;
    int number;
    char number_str[20];
    int length;
    uint32_t* pointer = mmap(NULL, size, PROT_READ, MAP_PRIVATE, input, 0);

    for (int i = 1; i < size;) {
        number = le32toh(*(pointer + i - 1));
        sprintf(number_str, "%d", number);
        write(1, &number_str, strlen(number_str));
        write(1, &" ", 1);
        pointer_next = le32toh(*(pointer + i));
        if (pointer_next == 0) {
            break;
        }
        i = (pointer_next / 4) + 1;
    }
    close(input);
    munmap(pointer, size);
}