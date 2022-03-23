#include "project2.h"

// compare two rgb structs for logical equality
int rgb_eq(struct rgb c1, struct rgb c2)
{
    if (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b) {
        return 1;
    }  
    return 0;
}

// check if image is all gray pixels
int img_grayscale(struct image *img)
{
    for (int i = 0; i < img->w * img->h; i++) {
        unsigned char red = img->pixels[i].r;
        unsigned char green = img->pixels[i].g;
        unsigned char blue = img->pixels[i].b;
        if (red != green || red != blue || green != blue) {
            return 0;
        }
    }
    return 1;
}

void skip_bytes(int n, FILE *f) {
    for (int i = 0; i < n; i++) {
        getc(f);
    }
}

int bytes_to_int(int bytes, FILE *f) {
    int i = 0;
    for (int j = bytes-1; j >= 0; j--) {
        i = i | (getc(f)<<(8*j));
    }
    return i;
}

unsigned int bytes_to_int_putchar(int bytes) {
    unsigned int i = 0;
    for (int j = bytes-1; j >= 0; j--) {
        int c = getchar();
        i = i | (c<<(8*j));
        putchar((char)c);
    }
    return i;
}

void formatted_int(char *str, int n) {
    printf("  \"%s\" : %d,\n", str, n);
}

void formatted_str(char *str1, char *str2) {
    printf("  \"%s\" : %s,\n", str1, str2);
}

void formatted_bool(char *str, int n) {
    if (n == 0) {
        printf("  \"%s\" : false,\n", str);
    }
    else {
        printf("  \"%s\" : true,\n", str);
    }
}

void write_bytes(unsigned int n) {
    for (int i = 0; i < n; i++) {
        char c = (char)getchar();
        putchar(c);
    }
}

void write_time() {
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
    for (int i = 0; i < 6; i++) {
        getchar();
    }
}

void write_string() {
    char c;
    while ((c = (char)getchar()) != '\0') {
        putchar(c);
    }
    putchar('\0');
}
