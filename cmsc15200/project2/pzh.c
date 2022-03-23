#include <stdio.h>
#include <stdlib.h>                                                         
#include <string.h>                                                         
#include <time.h>
#include <stdint.h>
#include "project2.h"

void write_pixels(struct rgb *pixels, int runs, int w, int h, int grayscale) {
    unsigned int run_arr[runs];
    int index = 0;
    for (int i = 0; i < runs; i++) {
        run_arr[i] = bytes_to_int(4, stdin);
    }
    for (int i = 0; i < runs; i++) {
        unsigned char r;    
        unsigned char g;
        unsigned char b;
        if (grayscale == 3) {
            r = (unsigned char)getchar();
            g = r;
            b = r;        
        }

        else {
            r = (unsigned char)getchar();
            g = (unsigned char)getchar();
            b = (unsigned char)getchar();
        }
        
        for (int j = 0; j < run_arr[i]; j++) {
            struct rgb current_pixel;
            current_pixel.r = r;
            current_pixel.g = g;
            current_pixel.b = b;
            pixels[index] = current_pixel;
            index ++;
        }
    }
}

void flip_pixels(struct rgb *pixels, int width, int height) {
    int index = 0;
    for (int i = 0; i < height; i++) {
        int start = index;
        for (int j = 0; j < width/2; j++) {
            struct rgb temp = pixels[index];
            pixels[index] = pixels[start+(width-j-1)];
            pixels[start+(width-j-1)] = temp;
            index++; 
        }
        if (width%2 == 1) {
            index += width/2+1;
        }
        else {
            index += width/2;
        }
    }
}

void record_colors(unsigned int *runs, unsigned int *run_arr, 
                    struct rgb *input, struct rgb *colors, int w, int h) { 
    int index = 0;
    int run_arr_value = 1;
    struct rgb prev_color = input[0];
    colors[index] = prev_color;
    for (int i = 1; i < w*h; i++) {
        struct rgb current_color = input[i];
        if (rgb_eq(prev_color, current_color)) {
            run_arr_value ++;
        }
        else {
            *runs += 1;
            index ++;
            prev_color = current_color;
            colors[index] = current_color;
            run_arr[index-1] = run_arr_value;
            run_arr_value = 1; 
        }
    }
    run_arr[index] = run_arr_value;
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
    if (grayscale == 3) {
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
    write_bytes(4);
    write_time();
    int width = bytes_to_int_putchar(2);
    int height = bytes_to_int_putchar(2);
    write_bytes(4);
    int grayscale = getchar();
    putchar((char)(grayscale));
    write_bytes(3);
    write_string();
    

    unsigned int runs = bytes_to_int(4, stdin);
    struct rgb pixels[width*height];
    write_pixels(pixels, runs, width, height, grayscale);
    
    flip_pixels(pixels, width, height);
    unsigned int run_num = 1;
    unsigned int run_arr[width*height];
    struct rgb colors[width*height];
    record_colors(&run_num, run_arr, pixels, colors, width, height);
    run_to_end(run_num, run_arr, colors, grayscale);
    return 0;
}
