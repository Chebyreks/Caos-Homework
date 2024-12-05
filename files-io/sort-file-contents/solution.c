#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <endian.h>

int compare(const void *a, const void *b) {
    int32_t a1 = le32toh(a);
    int32_t b1 = le32toh(b);
    if (a1 > b1) {
        return 1;
    } else if (a1 < b1) {
        return -1;
    } else {
        return 0;
    }
}

int main(int argc, char* argv[]) {
    char* input_filename = argv[1];
    int input = open(input_filename, O_RDONLY);
    if (input == -1) {
        return 1;
    }

    //НЕ ДОДЕЛАЛ
    //НЕ ДОДЕЛАЛ
    //НЕ ДОДЕЛАЛ

    int chunksize = 256;
    int32_t buffer[chunksize];
    int32_t number_arr[chunksize];
    int currsize = 0;
    ssize_t bytes_read;
    char* name = "file";
    char* fact_name;
    char* name_arr[10];
    char* forprint[1024];
    int count = 0;
    while (1) {
        fact_name = name + count;
        int output = open(fact_name, O_WRONLY | O_CREAT, 0644);
        bytes_read = read(input, &buffer, sizeof(buffer));
        if (bytes_read == 0) {
            close(input);
            close(output);
            break;
        }
        qsort(buffer, bytes_read / sizeof(int32_t), sizeof(int32_t), compare);
        currsize += bytes_read;
        sprintf(forprint, "%d", buffer);
        write(output, buffer, bytes_read);
        name_arr[count] = fact_name;
        close(output);
        currsize = 0;
        count += 1;
    }
    int inputs_arr[count];
    int pointer_arr[count];
    for (int i = 0; i <= count; i++) {
        fact_name = name + count;
        inputs_arr[i] = open(fact_name, O_RDONLY);
        pointer_arr[i] = 0;
    }
    int32_t read_int;
    int32_t max = 2147483647;
    int count_end;
    while (1) {
        for (int i = 0; i <= count; i++) {
            bytes_read = read(input, &read_int, sizeof(int32_t));
            if (bytes_read == 0) {
                count_end += 1;
            }
        }
        if (count_end == count) {
            break;
        }
        count_end = 0;
    }
    for (int i = 0; i <= count; i++) {
        close(inputs_arr[i]);
    }
    close(input);
}