#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strlist.h"

int main() {
    FILE *f = fopen("words.txt", "r");
    strlist *wordle_answers = strlist_from_file(f);
    fclose(f);
    strlist_write(stdout, wordle_answers);
    strlist_free(wordle_answers);
    
    return 0;
}
