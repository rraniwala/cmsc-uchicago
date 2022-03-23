#include <stdio.h>
#include <stdlib.h>                                                         
#include <string.h>                                                         
#include <time.h>
#include <stdint.h>
#include "project2.h"
 
int main(int argc, char *argv[]) {
    write_bytes(4);
    write_time();
    int width1 = getchar();
    int width2 = getchar();
    width1 *= 256;
    int width = (width1 + width2) * 2;
    putchar((char)(width>>8));
    putchar((char)(width&255));
    write_bytes(6);
    int grayscale = getchar();
    putchar((char)(grayscale));
    write_bytes(3);
    write_string();
    unsigned int runs = bytes_to_int_putchar(4);
    for (int i = 0; i < runs; i++) {
        unsigned int run = 0;
        for (int j = 3; j >= 0; j--) {
            int c = getchar();
            run = run | (c<<(8*j));
        }
        run = run * 2;
        putchar((char)(run>>24));
        putchar((char)((run>>16)&255));
        putchar((char)((run>>8)&255));
        putchar((char)(run&255));
    }
    
    if ((grayscale & 2) == 2) {
        for (int i = 0; i < runs; i++) {
            int g = getchar();
            putchar((char)(g));
        }
    }
    else {
        for (int i = 0; i < runs; i++) {
            int r = getchar();
            int g = getchar();
            int b = getchar();
            putchar((char)r);
            putchar((char)g);
            putchar((char)b);
        }
    }
    return 0;
}
