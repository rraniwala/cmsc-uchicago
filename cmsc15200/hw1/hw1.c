#include <stdio.h>
#include <math.h>
int luhn(unsigned long int num) {
    int check_digit = num % 10;
    int toggle = 0;
    int sum = 0;
    num /= 10;
    while (num > 0) {
        int current_digit = num%10;
        if (toggle%2 ==  0) {
            sum += (current_digit*2 / 10 + current_digit*2 % 10);
        }
        else {
            sum += current_digit;
        }
        num /= 10;
        toggle ++;
    }
    
    if ((10 - sum%10)%10 == check_digit) {
        return 1;
    }
    else {
        return 0;
    }
}
double area_pipe(double inner_r, double length, double thickness) {
    double ends = 2* M_PI*(pow(thickness+inner_r, 2)-pow(inner_r, 2));
    double outer_wall = 2*M_PI*(inner_r+thickness)*length;
    return ends + outer_wall;
}

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
int gcd (int a, int b) {
    if (b > a) {
        int c = a;
        a = b;
        b = c;
    }
    if (b == 0){
        return a;
    }
    
    return gcd(b, a % b);
}

int main() 
{
   printf("The gcd of  %d and %d is %d.\n", 7, 77, gcd(7, 77));
   printf("The gcd of  %d and %d is %d.\n", 110, 10, gcd(110, 10));
   printf("The gcd of  %d and %d is %d.\n", 35, 100, gcd(35, 100));
   printf("The gcd of  %d and %d is %d.\n", 91, 31, gcd(91, 31));
   printf("The SA of a pipe %d, %d, %d is %f.\n", 5, 7, 3, area_pipe(5, 7, 3));
   printf("The SA of a pipe %d, %d, %d is %f.\n", 8, 9, 2, area_pipe(8, 9, 2));
   printf("The SA of a pipe %d, %d, %d is %f.\n", 3, 4, 1, area_pipe(3, 4, 1));
   printf("The date %d/%d/%d is a %d.\n", 1, 17, 2022,  dow(1, 17, 2022));
   printf("The date %d/%d/%d is a %d.\n", 1, 18, 2022,  dow(1, 18, 2022));
   printf("The date %d/%d/%d is a %d.\n", 1, 19, 2022,  dow(1, 19, 2022));
   printf("The date %d/%d/%d is a %d.\n", 1, 20, 2022,  dow(1, 20, 2022));
   printf("The date %d/%d/%d is a %d.\n", 1, 21, 2022,  dow(1, 21, 2022));
   printf("The date %d/%d/%d is a %d.\n", 1, 22, 2022,  dow(1, 22, 2022));
   printf("The date %d/%d/%d is a %d.\n", 1, 23, 2022,  dow(1, 23, 2022));
   printf("%ld is a Luhn Number: %d.\n", 8974765482, luhn(8974765482));
   printf("%ld is a Luhn Number: %d.\n", 5101301520, luhn(5101301520));
   printf("%ld is a Luhn Number: %d.\n", 7294184051, luhn(7294184051));
   printf("%ld is a Luhn Number: %d.\n", 5466150801, luhn(5466150801));
   printf("%ld is a Luhn Number: %d.\n", 2964749168, luhn(2964749168));
   printf("%ld is a Luhn Number: %d.\n", 8974765489, luhn(8974765489));
   printf("%ld is a Luhn Number: %d.\n", 5101301523, luhn(5101301523));
   printf("%ld is a Luhn Number: %d.\n", 7294184056, luhn(7294184056));
   printf("%ld is a Luhn Number: %d.\n", 2964749167, luhn(2964749167));
   printf("%ld is a Luhn Number: %d.\n", 5466150809, luhn(5466150809));
   return 0;
}


