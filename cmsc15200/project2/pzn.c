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
    int grayscale = getchar();
    putchar((char)(grayscale));
    write_bytes(3);
    write_string();
    unsigned int runs = bytes_to_int_putchar(4);
    for (int i = 0; i < 4; i++) {
        write_bytes(runs);
    }
    if ((grayscale & 2) == 2) {
        for (int i = 0; i < runs; i++) {
            int g = 255 - getchar();
            putchar((char)(g));
        }
    }
    else {
        for (int i = 0; i < runs; i++) {
            int r = 255-getchar();
            int g = 255-getchar();
            int b = 255-getchar();
            putchar((char)r);
            putchar((char)g);
            putchar((char)b);
        }
    }
    return 0;
}
