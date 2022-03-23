#include "project1.h"

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

