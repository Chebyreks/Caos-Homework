#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <endian.h>

int main(int argc, char* argv[]) {
    char* input_filename = argv[1];
    int input = open(input_filename, O_RDONLY);
    if (input == -1) {
        return 1;
    }
    int32_t buffer;
    uint32_t pointer_buffer;
    ssize_t bytes_read;
    int number;
    char number_str[20];
    int length;
    uint32_t pointer;
    while (1) {
        bytes_read = read(input, &buffer, sizeof(int32_t));
        if (bytes_read <= 0) {
            break;
        }
        number = le32toh(buffer);
        sprintf(number_str, "%d", number);
        write(1, &number_str, strlen(number_str));
        write(1, &" ", 1);
        bytes_read = read(input, &pointer_buffer, sizeof(uint32_t));
        pointer = le32toh(pointer_buffer);
        if (pointer == 0) {
            break;
        }
        lseek(input, pointer, SEEK_SET);
    }
    close(input);
    return 0;
}