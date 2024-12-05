#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    char* input_filename = argv[1];
    char* output_digits_filename = argv[2];
    char* output_other_filename = argv[3];
    int input = open(input_filename, O_RDONLY);
    if (input == -1) {
        return 1;
    }
    int output_digits = open(output_digits_filename, O_WRONLY | O_CREAT, 0644);
    if (output_digits == -1) {
        close(input);
        return 2;
    }
        int output_other = open(output_other_filename, O_WRONLY | O_CREAT, 0644);
    if (output_other == -1) {
        close(input);
        close(output_digits);
        return 2;
    }
    char symbol;
    ssize_t bytes_read = read(input, &symbol, 1);
    while (bytes_read > 0) {
        if (bytes_read == -1) {
            return 3;
        }
        if (symbol == '0' || symbol == '1' ||
        symbol == '2'|| symbol == '3' ||
        symbol == '4' || symbol == '5' ||
        symbol == '6' || symbol == '7' ||
        symbol == '8' || symbol == '9') {
            if (write(output_digits, &symbol, 1) == -1) {
                return 3;
            }
        } else {
            if (write(output_other, &symbol, 1) == -1) {
                return 3;
            }
        }
        bytes_read = read(input, &symbol, 1);
    }
    close(input);
    close(output_digits);
    close(output_other);
}