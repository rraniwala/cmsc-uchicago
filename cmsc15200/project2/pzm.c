#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include "project2.h"

int main(int argc, char *argv[]) {
    if (argv[1]) {
        FILE *f = fopen(argv[1], "r");
        printf("{\n");
        formatted_str("filename", argv[1]);
        skip_bytes(4, f);
        int time = bytes_to_int(2, f);
        int date = bytes_to_int(4, f);
        formatted_int("date", date);
        formatted_int("time", time);
        formatted_int("width", bytes_to_int(2, f));
        formatted_int("height", bytes_to_int(2, f));
        skip_bytes(4, f);
        int byte_18 = getc(f);
        int rle = byte_18 & 1;
        int grayscale = byte_18 & 2;
        formatted_bool("grayscale", grayscale);
        formatted_bool("rle", rle);
        skip_bytes(3, f);
        printf("  \"description\" : \"");
        char c;
        while ((c = (char)getc(f)) != '\0') {
            printf("%c", c);
        }
        printf("\",\n");
        int runs = bytes_to_int(4, f);
        formatted_int("runs", runs);
        formatted_int("run-bytes", runs*4);
        if (grayscale) {
            formatted_int("pixel-bytes", runs);
        }
        else {
            formatted_int("pixel-bytes", runs*3);
        }
        printf("}\n");
        fclose(f);
    }
    else {
        fprintf(stderr, "File name not given");
        exit(1);
    }
    return 0;
}
