#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include "project2.h"

void record_colors(unsigned int *runs, unsigned int *run_arr, 
                    struct rgb *colors, int w, int h, int *grayscale) { 
    int r = 0;
    int g = 0;
    int b = 0;
    int i = 0;
    int run_arr_value = 1;
    scanf("%d", &r);
    scanf("%d", &g);
    scanf("%d", &b);
    struct rgb prev_color;
    prev_color.r = r;
    prev_color.g = g;
    prev_color.b = b;
    colors[i] = prev_color;
    while (scanf("%d", &r) != EOF) {
        scanf("%d", &g);
        scanf("%d", &b);
        struct rgb current_color;
        current_color.r = r;
        current_color.g = g;
        current_color.b = b;
        if (rgb_eq(prev_color, current_color)) {
            run_arr_value ++;
        }
        else {
            i++;
            *runs += 1;
            prev_color = current_color;
            colors[i] = current_color;
            run_arr[i-1] = run_arr_value;
            run_arr_value = 1; 
        }
    }
    run_arr[i] = run_arr_value;
    struct image img;
    img.w = *runs;
    img.h = 1;
    img.pixels = colors;
    *grayscale = img_grayscale(&img);
}

void start_pz_file() {
    putchar('P');
    putchar('Z');
    for (int i = 0; i < 2; i++) {
        putchar(' ');
    }
}

void write_time_date() {
    time_t rawtime;
    time(&rawtime);
    struct tm *t = localtime(&rawtime);
    int time = 0;
    time += t->tm_hour;
    time *= 100;
    time += t->tm_min;
    putchar((char)(time>>8));
    putchar((char)(time & 255));
    int date = 0;
    date += (t->tm_year+1900);
    date *= 100;
    date += (t->tm_mon+1);
    date *= 100;
    date += t->tm_mday;
    putchar((char)(date>>24));
    putchar((char)((date>>16)&255));
    putchar((char)((date>>8)&255));
    putchar((char)(date&255));
}

void write_size(int *w, int *h) {
    for (int i = 0; i < 2; i++) {
        getchar();
    }
    
    int n;
    scanf("%d", &n);
    *w = n;
    putchar((char)(n>>8));
    putchar((char)(n&255));

    scanf("%d", &n);
    *h = n;
    putchar((char)(n>>8));
    putchar((char)(n&255));
    for (int i = 0; i < 4; i++) {
        putchar(' ');
    }
    scanf("%d", &n);
}

void write_byte18(int grayscale) {
    int n = 1;
    if (grayscale) {
        n += 2;
    }
    putchar((char)n);
    for (int i = 0; i < 3; i++) {
        putchar(' ');
    }
}

void run_to_end(unsigned int runs, unsigned int *run_arr, 
                struct rgb *colors, int grayscale) {
    putchar((char)(runs>>24));
    putchar((char)(runs>>16)&255);
    putchar((char)(runs>>8)&255);
    putchar((char)runs&255);
    for (int i = 0; i < runs; i++) {
        putchar((char)(run_arr[i]>>24));
        putchar((char)(run_arr[i]>>16)&255);
        putchar((char)(run_arr[i]>>8)&255);
        putchar((char)run_arr[i]&255);       
    }
    if (grayscale) {
        for (int i = 0; i < runs; i++) {
            putchar((char)colors[i].r);
        }
    }
    else {
        for (int i = 0; i < runs; i++) {
            putchar((char)colors[i].r);
            putchar((char)colors[i].g);
            putchar((char)colors[i].b);
        }
    }
}

int main(int argc, char *argv[]) {
    start_pz_file();
    write_time_date();
    int w = 0;
    int h = 0;
    int grayscale = 0;
    unsigned int runs = 1;
    write_size(&w, &h);
    unsigned int run_arr[w*h];
    struct rgb colors[w*h];
    record_colors(&runs, run_arr, colors, w, h, &grayscale);
    write_byte18(grayscale);
    int i = 0;
    if (argv[1]) {
        while (argv[1][i] != '\0') {
            putchar(argv[1][i]);
            i++;
        }
    }
    putchar('\0');
    run_to_end(runs, run_arr, colors, grayscale);
    return 0;
}
