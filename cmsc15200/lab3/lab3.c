#include <stdio.h>

int num_digits(int num) {
    int digits = 1;
    while (num > 9){
        num = num / 10;
        digits++;
    }
    return digits;
}

int minimum(int nums[], int len) {
    int min = nums[0];
    for (int i = 1; i < len; i++) {
        if (min > nums[i]) {
            min = nums[i];
        }
    }
    return min;
}

void swap(int *a, int *b) {
    int c = *a;
    *a = *b;
    *b = c;
}

int most_frequent_digit(int nums[], int len, int *freq) {
    *freq = 1;
    int digit = 0;
    int frequency[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < len; i++) {
        while (nums[i] > 9){
            frequency[nums[i]%10]++;
            nums[i] /= 10;
        }
        frequency[nums[i]]++;
    }

    int max = frequency[0];
    for (int i = 1; i < 9; i++) {
        if (max < frequency[i]){
            max = frequency[i];
            digit = i;
        }
        if (max == frequency[i] && i < digit) {
            digit = i;
        }
    }
    *freq = max;
    return digit;
}
int main() {
    printf("%d has %d digits\n", 1209408, num_digits(1209408));
    int len = 6;
    int arr[6] = {452, 4555, 6700, 355, 10, 0};
    printf("%d is the minimum of this array.\n",minimum(arr, len));
    int a = 17;
    int b = 19;
    printf("Currently, A is %d while B is %d\n", a, b);
    swap(&a, &b);
    printf("A is now %d, while B is %d\n", a, b);
    int f = 0;
    printf("Most frequent digit: %d, Frequency: %d\n", most_frequent_digit(arr, len, &f), f);     
    return 0;
}
