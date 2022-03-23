#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include "project1.h"

void start_p3_file() {
    printf("P3\n");
}

void include_size() {
    int n;
    char consume;
    for (int i = 0; i < 2; i++) {
        scanf("%c", &consume);
    }   
    for (int i = 0; i < 2; i++) {
        scanf("%d", &n);
        printf("%d ", n);
    }
    printf("\n");
}

void include_maxRGB() {
    int n;
    scanf("%d", &n);
    printf("%d\n", n);
}

void write_rgb() {
    int n;
    scanf("%d", &n);
    while ((n = getchar()) != EOF) {
        printf("%d ", n);
    }

}

int main(int argc, char *argv[])
{
    start_p3_file();
    include_size();
    include_maxRGB();
    write_rgb();
    return 0;
}
