#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct fraction {
  int num;
  int denom;
};

typedef struct fraction frac;

frac *frac_new(int num, int denom) {
    frac *c = (frac *) malloc(sizeof(frac));
    if (denom == 0) {
        fprintf(stderr, "frac_new: denom = 0\n");
    }
    c->num = num;
    c-> denom = denom;
    if (num == 0) {
        c->num = 0;
        c->denom = 1;
    }
    else {
        if (abs(denom) % abs(num) == 0) {
            denom = denom / num;
            num = 1;
        }
        else {
            for (int i = abs(num) / 2; i > 0; i--) {
                if (num % i == 0 && denom % i == 0) {
                    num = num / i;
                    denom = denom / i;
                    break;
                }
            }
        } 
        if (denom < 0) {
            num *= -1;
            denom *= -1;
        }
        c-> num = num;
        c-> denom = denom;
    }
    return c;
}

frac *frac_add(frac *q, frac *r) {
    int denom = q->denom * r->denom;
    int num = q->num * r->denom + r->num * q->denom;
    return frac_new(num, denom);
}

frac *frac_mult(frac *q, frac *r) {
    return frac_new(q->num*r->num, q->denom*r->denom);
}

frac *frac_raise(frac *r, unsigned int power) {
    if (power == 0) {
        return frac_new(1, 1);
    }
    int num = r-> num;
    int denom = r-> denom;
    for (int i = 0; i < power - 1; i++){
        num *= r->num;
        denom *= r->denom;
    }
    return frac_new(num, denom);
}

int frac_eq(frac *q, frac *r) {
    frac *f1 = frac_new(q->num, q->denom);
    frac *f2 = frac_new(r->num, r->denom);
    if ((f1->num == f2->num) && (f1->denom == f2->denom)) {
        return 1;
    }
    return 0;
}

char *frac_tos(frac *r) {
    int count = 1;
    int num = r-> num;
    int denom = r-> denom;
    if (num < 0) {
        count++;
        num *= -1;
    }
    if (num == 0) {
        count++;
    }
    else { 
        while (num > 0) {
            count++;
            num /= 10;
        }
    }
    while (denom > 0) {
        count++;
        denom /= 10;
    }
    char *fracstr = (char *) malloc(count * sizeof(char));
    num = r-> num;
    denom = r-> denom;
    int i = count - 1;
    if (num < 0) {
        fracstr[0] = '-';
        num *= -1;
    }
    printf("%d\n", denom);
    while (denom > 0) {
        fracstr[i] = (denom % 10) + '0';
        denom /= 10;
        i--;
    }
    fracstr[i] = '/';
    i--;
    if (num == 0) {
        fracstr[i] = 0 + '0';
    }
    else {
        while (num > 0) {
            fracstr[i] = (num % 10) + '0';
            num /= 10;
            i--;
        }
    }
    return fracstr; 
}

int main() {
    frac *f1 = frac_new(3, 9);
    frac *f2 = frac_new(4, -10);
    frac *f3 = frac_new(0, 7);
    frac *f4 = frac_new(9, 5);
    frac *f5 = frac_new(-5, 11);
    frac *f6 = frac_new(-18, -12);
    frac *f7 = frac_add(f1, f6);
    frac *f8 = frac_add(f3, f5);
    frac *f9 = frac_add(f4, f2);
    frac *f10 = frac_mult(f1, f2);
    frac *f11 = frac_mult(f3, f6);
    frac *f12 = frac_mult(f1, f6);
    frac *f13 = frac_raise(f1, 1);
    frac *f14 = frac_raise(f2, 0);
    frac *f15 = frac_raise(f4, 4);
    char *s1 = frac_tos(f1);
    char *s2 = frac_tos(f2);
    char *s3 = frac_tos(f3);
    char *s4 = frac_tos(f4);
    char *s5 = frac_tos(f5);
    char *s6 = frac_tos(f6);
    char *s7 = frac_tos(f7);
    char *s8 = frac_tos(f8);
    char *s9 = frac_tos(f9);
    char *s10 = frac_tos(f10);
    char *s11 = frac_tos(f11);
    char *s12 = frac_tos(f12);
    char *s13 = frac_tos(f13);
    char *s14 = frac_tos(f14);
    char *s15 = frac_tos(f15);
    printf("%d, %d\n", f3->num, f3->denom);
    printf("%s, %s, %s, %s, %s, %s\n", s1, s2, s3, s4, s5, s6);
    printf("%s, %s, %s\n", s7, s8, s9);
    printf("%s, %s, %s\n", s10, s11, s12);
    printf("%s, %s, %s\n", s13, s14, s15);
    printf("%d, %d\n", frac_eq(f1, f2), frac_eq(f3, f11));
    return 1;
}
