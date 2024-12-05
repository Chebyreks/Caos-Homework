#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <endian.h>
#include <sys/stat.h>

void normalize_path(char* path) {
    char* ans = path;

    if (*path == '/') {
        *ans = *path;
        ans++;
        path++;
    }

    while (*path) {
        if (*path == '/' && *(path + 1) == '/') {
            path++;
            continue;
        }

        if (*path == '.' && *(path + 1) == '/' ) {
            path += 2;
            continue;
        }

        if (*path == '/' && *(path + 1) == '.' && *(path + 2) == '.') {
            ans--;
            while (*ans != '/') {
                ans--;
            }
            path += 3;
        }

        *ans = *path;
        ans++;
        path++;
    }
    *ans = '\0';
}