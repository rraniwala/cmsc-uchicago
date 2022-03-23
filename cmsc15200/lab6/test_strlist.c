#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strlist.h"

int main()
{
    strlist *strlist1 = strlist_new("Hi", NULL);
    strlist *strlist2 = strlist_new("there", strlist_new("Hi", NULL));
    FILE *f = fopen("tiny.txt", "r");
    strlist *strlist3 = strlist_from_file(f);
    fclose(f);
    printf("strlist_len(strlist1): %u\n", strlist_len(strlist1));
    strlist_write(stdout, strlist2);
    strlist_write(stdout, strlist3);
    strlist_free(strlist1);
    strlist_free(strlist2);
    strlist_free(strlist3);
}
