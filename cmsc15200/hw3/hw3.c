#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint32_t pdate;

pdate new_date(unsigned int m, unsigned int d, unsigned int y) {
    pdate final_date = 0;
    final_date += y;
    final_date = final_date<<8;
    final_date += m;
    final_date = final_date<<8;
    final_date += d;
    return final_date;
}

void unpack(pdate pd, unsigned int *m, unsigned int *d, unsigned int *y) {
    *d = pd & 255;
    pd = pd>>8;
    *m = pd & 255;
    pd = pd>>8;
    *y = pd;
}

void show_date(pdate pd) {
    unsigned int m = 0;
    unsigned int d = 0;
    unsigned int y = 0;
    unpack(pd, &m, &d, &y);
    if (d < 10){
        if (m < 10) {
            printf("0%d-0%d-%d\n", d, m, y);
        }
        else {
            printf("0%d-%d-%d\n", d, m, y);
        }
    }
    else if (m < 10){
        printf("%d-0%d-%d\n", d, m, y);
    }
    else {
        printf("%d-%d-%d\n", d, m, y);
    }
}

int valid_pdate(pdate pd) {
    unsigned int m = 0;
    unsigned int d = 0;
    unsigned int y = 0;
    unsigned int max_days = 0;
    unpack(pd, &m, &d, &y);
    switch (m) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            max_days = 31;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            max_days = 30;
            break;
        case 2:
            if (y%4 == 0 && (y%100 != 0 || y%400 == 0)) {
                max_days = 29;
            }
            else {
                max_days = 28;
            }
            break;
        default:
            return 0;
    }
    if (d > max_days || d < 1) {
        return 0;
    }
    if (y < 1900 || y > 2099) {
        return 0;
    }
    return 1;
}   

pdate yesterday(pdate pd) {
    unsigned int m = 0;
    unsigned int d = 0;
    unsigned int y = 0;
    unsigned int max_days = 0;
    unpack(pd, &m, &d, &y);
    switch (m-1) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 0:
            max_days = 31;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            max_days = 30;
            break;
        case 2:
            if (y%4 == 0 && (y%100 != 0 || y%400 == 0)) {
                max_days = 29;
            }
            else {
                max_days = 28;
            }
            break;
    }
    if (d-1==0) {
        if(m-1==0){
            return new_date(12, max_days, y-1);
        }
        return new_date(m-1, max_days, y);
    }
    return new_date(m, d-1, y);
}

pdate tomorrow(pdate pd) {
    unsigned int m = 0;
    unsigned int d = 0;
    unsigned int y = 0;
    unsigned int max_days = 0;
    unpack(pd, &m, &d, &y);
    switch (m) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            max_days = 31;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            max_days = 30;
            break;
        case 2:
            if (y%4 == 0 && (y%100 != 0 || y%400 == 0)) {
                max_days = 29;
            }
            else {
                max_days = 28;
            }
            break;
    }
    if (d==max_days) {
        if(m==12){
            return new_date(1, 1, y+1);
        }
        return new_date(m+1, 1, y);
    }
    return new_date(m, d+1, y);
}

pdate *date_span(pdate pd1, pdate pd2, unsigned int *length) {
    if (pd2 < pd1) {
        *length = 0;
        return NULL;
    }
    unsigned int days_in_between = 1;
    pdate first_day = pd1;
    while (tomorrow(first_day) != pd2) {
        days_in_between ++;
        first_day = tomorrow(first_day);
    }
    *length = days_in_between + 1;
    pdate *date_arr = (pdate *)malloc(*length * 4);
    if (date_arr == NULL) {
        fprintf(stderr, "Allocation failed\n");
        exit(1);
    }
    date_arr[0] = pd1;    
    for (int i = 1; i < *length; i++) {
        date_arr[i] = tomorrow(pd1);
        pd1 = tomorrow(pd1);
    }
    return date_arr;
}

unsigned int date_distance(pdate *dates, unsigned int length) {
    unsigned int min_day = dates[0];
    unsigned int max_day = dates[0];
    for (int i = 0; i < length; i++) {
        if (dates[i] < min_day) {
            min_day = dates[i];
        }
        else if (dates[i] > max_day) {
            max_day = dates[i];
        }
    }
    unsigned int days_in_between = 1;
    while (tomorrow(min_day) != max_day) {
        days_in_between ++;
        min_day = tomorrow(min_day);
    }
    return days_in_between;
}

void swap(pdate *a, pdate *b) {
    int c = *a;
    *a = *b;
    *b = c;
}

void sort_asc(pdate *dates, unsigned int length) {
    for (int i = 0; i < length; i++) {
        pdate current_min = dates[i];
        unsigned int swap_index = i;
        for (int j = i; j < length; j++) {
            if (current_min > dates[j]) {
                current_min = dates[j];
                swap_index = j;
            }
        }
        swap(&dates[i], &dates[swap_index]);
    }
}

int main() {
    pdate date = new_date(2, 1, 2022);
    pdate invalid_date_1 = new_date(13, 22, 2022);
    pdate invalid_date_2 = new_date(2, 30, 2022);
    pdate invalid_date_3 = new_date(7, 35, 2022);
    pdate invalid_date_4 = new_date(2, 1, 2101);
    pdate yesterday_1 = new_date(1, 1, 2011);
    pdate yesterday_2 = new_date(12, 13, 2024);
    pdate yesterday_3 = new_date(4, 1, 2012);
    pdate tomorrow_1 = new_date(12, 31, 2022);
    pdate tomorrow_2 = new_date(4, 30, 2001);
    pdate tomorrow_3 = new_date(6, 5, 2045);
    pdate test_1 = new_date(2, 15, 2022);
    pdate test_2 = new_date(2, 1, 2020);
    pdate test_3 = new_date(3, 1, 2025);
    pdate test_4 = new_date(1, 11, 2024);
    pdate test_5 = new_date(1, 22, 2021);
    
    unsigned int length = 0;
    pdate *pdate_arr = date_span(yesterday_1, yesterday_3, &length);
    for (int i = 0; i < length; i++) {
        show_date(pdate_arr[i]);
    }
    printf("%d, %d\n", length, date_distance(pdate_arr, length));
    pdate dates[5] = {date, yesterday_1, yesterday_2, yesterday_3, tomorrow_1};
    sort_asc(dates, 5);
    pdate test_dates[5] = {test_1, test_2, test_3, test_4, test_5};
    printf("%d\n", date_distance(test_dates, 5));
    sort_asc(test_dates, 5);
    for (int i = 0; i < 5; i++) {
        show_date(dates[i]);
    }
    for (int i = 0; i < 5; i++) {
        show_date(test_dates[i]);
    }
    unsigned int m = 0;
    unsigned int d = 0;
    unsigned int y = 0;
    show_date(tomorrow(date));
    show_date(tomorrow(tomorrow_1));
    show_date(tomorrow(tomorrow_2));
    show_date(tomorrow(tomorrow_3));
    show_date(yesterday(date));
    show_date(yesterday(yesterday_1));
    show_date(yesterday(yesterday_2));
    show_date(yesterday(yesterday_3));
    printf("Valid date: %d\n", valid_pdate(date));
    printf("Valid date: %d\n", valid_pdate(invalid_date_1));
    printf("Valid date: %d\n", valid_pdate(invalid_date_2));
    printf("Valid date: %d\n", valid_pdate(invalid_date_3));
    printf("Valid date: %d\n", valid_pdate(invalid_date_4));
    unpack(date, &m, &d, &y);
    show_date(date);
    printf("\n");
    printf("Unpacking %X gives us %d/%d/%d\n", date, m, d, y);
    printf("The date Feb 1 2022 is %X\n", new_date(2, 1, 2022));
    return 0;
    
}
