#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void replace_character(char *str, char replacee, char replacer) {
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == replacee) {
            str[i] = replacer;
        }
    }   
}

char *remove_character(char *str, char c) {
    int i = 0;
    int j = 0;
    char *new_str = (char *)malloc(sizeof(char) * strlen(str)); 
    while (str[i] != '\0') {
        if (str[i] != c) {
            new_str[j] = str[i];
            j++;
        }
        i++;
    }
    return new_str;
}

int find_substring_location(char *str, char *sub) {
    int i = 0;
    int j = 0;
    while (str[i] != '\0') {
        if (sub[j] == '\0') {
            return i - strlen(sub);
        }
        else if (sub[j] != str[i]) {
            j = 0;
        }
        else {
            j++;
        }
        i++;
    }
    if (sub[j] == '\0') {
        return i - strlen(sub);
    }
    return -1; 
}

char *find_match(char *str, char *pattern) {
    char *copy = strndup(str, strlen(pattern));
    int i = 0;
    int j = 0;
    int backtrack = 0;
    while (pattern[backtrack] == '?') {
        backtrack ++;
    }
    while (str[i] != '\0') {
        if (pattern[j] == '\0') {
            return copy;
        }
        else if ((pattern[j] != '?') && (pattern[j] != str[i])) {
            j = 0;
            i -= backtrack;
        }
        else {
            copy[j] = str[i];
            j++;
        }
        i++;
    }
    if (pattern[j] == '\0') {
        return copy;
    }
    return NULL;
}

int main() {
    char s1[] = "Hello World!";
    replace_character(s1, 'o', '.');
    char s2[] = "Hello World!";
    char *s3 = remove_character(s2, 'l');
    printf("%s\n", s3);
    printf("%s\n", s1);
    char s4[] = "Hello World!";
    char s5[] = "u";
    printf("%d\n", find_substring_location(s4, s5));
    char s6[] = "Hello World!";
    char s7[] = "?llo??";
    char *s8 = find_match(s6, s7);
    printf("%s\n", s8);
    free(s3);
    free(s8);
    return 1;
}
