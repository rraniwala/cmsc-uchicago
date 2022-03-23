#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strlist.h"

strlist *strlist_new(char *w, strlist *n) {
    strlist *new_list = (strlist *)malloc(sizeof(strlist));
    if (new_list == NULL) {
        fprintf(stderr, "malloc failed on stlist_new\n");
        exit(1);
    }
    char *copy_w = strdup(w);
    new_list->word = copy_w;
    new_list->next = n;
    return new_list;
}

void strlist_free(strlist *lst) {
    if (lst == NULL) {
        return;
    }
    strlist_free(lst->next);
    free(lst->word);
    free(lst);
}

void strlist_write(FILE *f, strlist *lst) {
    for (strlist *current = lst; current != NULL; current = current->next) {
        fprintf(f, "%s\n", current->word);
    }
}

strlist *strlist_from_file(FILE *f) {
    strlist *new_list = NULL;

    char w[10];

    while (fscanf(f, "%s", w) != EOF) {
        strlist *temp = new_list;
        new_list = strlist_new(w, temp);
    }
    return new_list;
}

unsigned int strlist_len(strlist *lst) {
    unsigned int count = 0;
    for (strlist *current = lst; current != NULL; current = current->next) {
        count ++;
    }
    return count;
}

unsigned int strlist_count(int(*test)(char *), strlist *lst) {
    unsigned int count = 0;
    for (strlist *current = lst; current != NULL; current = current->next) {
        if ((*test)(current->word)) {
            count ++;
        }
    }
    return count;
}
