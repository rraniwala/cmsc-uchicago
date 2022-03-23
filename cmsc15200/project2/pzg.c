#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include "project2.h"

int main(int argc, char *argv[]) {
    write_bytes(4);
    write_time();
    write_bytes(8);
    putchar((char)3);
    int grayscale = getchar();
    write_bytes(3);
    write_string();
    unsigned int runs = bytes_to_int_putchar(4);
    for (int i = 0; i < 4; i++) {
        write_bytes(runs);
    }
    if ((grayscale & 2) == 2) {
        write_bytes(runs);
    }
    else {
        for (int i = 0; i < runs; i++) {
            int r = getchar();
            int g = getchar();
            int b = getchar();
            int gray = r*0.2126 + g*0.7152 + b*0.0722;
            putchar((char)gray);
        }
    }
    return 0;
}
