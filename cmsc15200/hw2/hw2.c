#include <stdio.h>
#include <stdint.h>
#include <math.h>
int dow(int month, int day, int year) {
    month --;
    int adj = 0;
    int leap_year = floor(year/4);
    if (year%4 == 0) {
        adj --;
    }
    int month_adjustment[12] = {1+adj, 4+adj, 4, 0, 2, 5, 0, 3, 6, 1, 4, 6};
    int n = (year - 1900) + month_adjustment[month] + day + leap_year;
    return n % 7;
}

void show_month(unsigned int m, unsigned int y, char *sep) {
    char *month = "";
    int days = 0;
    switch (m) {
        case 1: 
            month = "Jan";
            days = 31;
            break;
        case 2: 
            month = "Feb";
            if (y%4 == 0 && (y%100 != 0 || y%400 == 0)){
                days = 29;
            }
            else {
                days = 28;
            }
            break;
        case 3: 
            month = "Mar";
            days = 31;
            break;
        case 4: 
            month = "Apr";
            days = 30;
            break;
        case 5: 
            month = "May";
            days = 31;
            break;
        case 6: 
            month = "Jun";
            days = 30;
            break;
        case 7: 
            month = "Jul";
            days = 31;
            break;
        case 8: 
            month = "Aug";
            days = 31;
            break;
        case 9: 
            month = "Sep";
            days = 30;
            break;
        case 10: 
            month = "Oct";
            days = 31;
            break;  
        case 11: 
            month = "Nov";
            days = 30;
            break;
        case 12: 
            month = "Dec";
            days = 31;
            break;
    }
    
    for (int i = 1; i <= days; i++) {
        int dow_int = dow((int)m, i,(int)y);
        char *day = "";
        switch (dow_int) {
            case 0: 
                day = "Sun";
                break;
            case 1: 
                day = "Mon";
                break;
            case 2: 
                day = "Tue";
                break;
            case 3: 
                day = "Wed";
                break;
            case 4: 
                day = "Thu";
                break;
            case 5: 
                day = "Fri";
                break;
            case 6: 
                day = "Sat";
                break;
        }

        if (dow_int == 0) {
            printf("%s\n", sep);
        }
        printf("%s %s %d, %d\n", day, month, i, y);
    }
}

void grid(unsigned int n_rows, unsigned int n_cols) {
    if (n_rows == 0 || n_cols == 0) {
        return;
    }

    for (int i = 0; i < 2*n_rows + 1; i++) {
        for (int j = 0; j < 2*n_cols + 1; j++) {
            if (i%2 == 0) {
                if (j%2 == 0) {
                    printf("+");
                }
                else {
                    printf("-");
                }
            }
            else {
                if (j%2 == 0) {
                    printf("|");
                }
                else {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
}

unsigned char red (uint32_t color) {
    return color>>24;
}

unsigned char green (uint32_t color) {
    return (color>>16) & 255;
}

unsigned char blue (uint32_t color) {
    return (color>>8) & 255;
}

double luminance(uint32_t color) {
    return 0.2126*red(color) + 0.7152*green(color) + 0.0722*blue(color);
}

int brighter (uint32_t color1, uint32_t color2) {
    return (luminance(color1) > luminance(color2));
}

int dimmer (uint32_t color1, uint32_t color2) {
    return (luminance(color1) < luminance(color2));
}

uint32_t helper_rgb_to_color(unsigned char red, unsigned char green, unsigned char blue) {
    uint32_t final_number = 0;
    final_number += red;
    final_number = final_number<<8;
    final_number += green;
    final_number = final_number<<8;
    final_number += blue;
    final_number = final_number<<8;
    return final_number;

}
uint32_t rgb_negate(uint32_t color) {
    return helper_rgb_to_color(255-red(color), 255-green(color), 255-blue(color));
}

uint32_t rgb_mid(uint32_t color1, uint32_t color2) {
    unsigned char mid_red = floor((red(color1)+red(color2))/2);
    unsigned char mid_green = floor((green(color1)+green(color2))/2);
    unsigned char mid_blue = floor((blue(color1)+blue(color2))/2);
    return helper_rgb_to_color(mid_red, mid_green, mid_blue);
}

uint32_t make_gray(unsigned char g) {
    return helper_rgb_to_color(g, g, g);
}

int is_gray(uint32_t color) {
    if (red(color) == blue(color) && red(color) == green(color)) {
        return 1;
    }
    else {
        return 0;
    }
}

void show_rgb_triple(uint32_t color) {
    printf("(%d,%d,%d)\n", red(color), green(color), blue(color));
}

void show_hex_color(uint32_t color) {
    printf("#%X\n", color);
}


int main() {
    show_month(1, 2022, "===");
    show_month(2, 2022, "=====");
    show_month(3, 2022, "---");
    show_month(4, 2022, "mmmmm");
    grid(4, 6);
    grid(0, 5);
    grid(7, 0);
    grid(7, 11);
    grid(9, 24);
    uint32_t color1 = 0xFF800400;
    uint32_t color2 = 0xFC934500;
    uint32_t color3 = 0x24457A00;
    uint32_t color4 = 4286579712;
    show_rgb_triple(color1);
    show_rgb_triple(color2);
    show_rgb_triple(color3);
    show_hex_color(color4);
    printf("Luminances: %f, %f\n", luminance(color1), luminance(color2));
    printf("Is Color 1 brighter than color 2? %d\n", brighter(color1, color2));
    printf("So then which is dimmer? %d\n", dimmer(color1, color2));
    show_rgb_triple(rgb_negate(color1));
    show_rgb_triple(rgb_negate(color2));
    show_rgb_triple(rgb_negate(color3));
    show_rgb_triple(rgb_mid(color1, color2));
    show_rgb_triple(rgb_mid(color1, color3));
    show_rgb_triple(rgb_mid(color2, color3));
    show_rgb_triple(make_gray(127));
    show_rgb_triple(make_gray(12));
    show_rgb_triple(make_gray(237));
    printf("Grey is grey: %d\n", is_gray(make_gray(127)));
    printf("Not gray is not gray: %d\n", is_gray(color1));
    return 0;
}
