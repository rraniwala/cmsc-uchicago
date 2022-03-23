#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include "project2.h"

void start_p3_file() {
    printf("P3\n");
}

void get_to_size() {
    for (int i = 0; i < 10; i++) {
        int n = getchar();
    }
}

void write_size() {
    for (int i = 0; i < 2; i++) {
        int n = getchar();
        int j = getchar();
        n = n<<8;
        n = n | j;
        printf("%d ", n);
    }
    printf("\n");
    printf("%d\n", 255);
}

void get_to_grayscale() {
    for (int i = 0; i < 4; i++) {
        int n = getchar();
    }
}

int grayscale() {
    if ((getchar() & 2) == 2) {
        return 1;
    }
    return 0;
}

void get_to_runs() {
    for (int i = 0; i < 3; i++) {
        int n = getchar();
    }
    while (getchar() != '\0') {

    }
}

void write_rgb(int grayscale) {
    unsigned int runs = 0;
    for (int i = 3; i >= 0; i--) {
        int n = getchar();
        runs = runs | (n<<(8*i));
    }
    unsigned int run_arr[runs];    
    
    for (int i = 0; i < runs; i++) {
        unsigned int run_nums = 0;
        for (int j = 3; j >= 0; j--) {
            int n = getchar();
            run_nums = run_nums | (n<<(8*j));
        }
        run_arr[i] = run_nums;
    }
    if (grayscale) {
        for (int i = 0; i < runs; i++) {
            int gray = getchar();
            for (int j = 0; j < run_arr[i]; j++) {
                printf("%d %d %d ", gray, gray, gray);
            }
        }
    }

    else {
        for (int i = 0; i < runs; i++) {
            int r = getchar();
            int g = getchar();
            int b = getchar();
            for (int j = 0; j < run_arr[i]; j++) {
                printf("%d %d %d ", r, g, b);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    start_p3_file();
    get_to_size();
    write_size();
    get_to_grayscale();
    int n = grayscale();
    get_to_runs();
    write_rgb(n);
    return 0;
}
