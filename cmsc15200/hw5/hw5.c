#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* === data definitions === */

typedef struct ilist_node ilist;

struct ilist_node {
  int first;
  ilist *rest;
};

// convention: NULL means empty list

typedef struct itree_node itree;

struct itree_node {
  int root;
  itree *lsub;
  itree *rsub;
};

// convention: NULL means empty tree

/* === operations (forward declarations) === */

// build a new ilist from int and pointer
ilist *ilist_new(int f, ilist *r);

// free the whole ilist, assuming everything is heap allocated and safe to free
// (not shared)
void ilist_free(ilist *ns);

// use Haskell-style notation to write a list
// in the form "1:3:7:nil"
// - that is, put colons between numbers, and "nil" at the end
// - if newline is false, don't write a newline at end, otherwise do
// - note that the FILE* argument can be stdout or stderr
void ilist_write(FILE *f, ilist *ns, int newline);

// allocate a whole new list, with the same numbers
// in the same order (this is a "copy constructor")
ilist *ilist_dup(ilist *ns);

// if arr is NULL, return NULL, otherwise
// build a list with the same numbers in the
// same order as the given array
ilist *ilist_from_array(int *arr, unsigned int len);

// build a new tree from a root value and two subtrees
itree *itree_new(int root, itree *lsub, itree *rsub);

// free the whole itree, assuming everything is heap allocated and safe to free
// (not shared)
void itree_free(itree *t);

// write a parenthesized tree of the form "(root [lsub] [rsub])"
// with a period "." for each empty tree
// - for example, the tree with root 1 and two empty subtrees
//   should be written "(1 . .)"
// - note that the FILE* argument can be stdout or stderr
void itree_write(FILE *f, itree *t);

// allocate a whole new tree, with the same numbers
// in the same positions (another "copy constructor")
itree *itree_dup(itree *t);

// compute the sum of all ints in the list
int ilist_sum(ilist *ns);

// compute the sum of all ints in the tree
int itree_sum(itree *t);

// compute the length of the list
unsigned int ilist_len(ilist *ns);

// count the number of nodes in the tree
unsigned int itree_size(itree *t);

// the height of the empty tree is 0;
// the height of a nonempty tree is the length
// of the longest path from root to leaf
unsigned int itree_height(itree *t); 

// build the list of all the ints in a tree,
// moving from left to right
ilist *inorder(itree *t);

// build the list of all in the ints at leaf position
// in the tree, moving from left to right
ilist *leaves(itree *t);

// this is like ilist_write above, but must produce
// a heap-allocated string and return it (no newline)
char *ilist_tos(ilist *ns);

// test if the two lists have the same ints in the same order
// (and are the same length)
int ilist_eq(ilist *ms, ilist *ns);

// look for an int in the list that passes the test;
// if found, return a pointer to its node, if not found,
// return NULL
ilist *ilist_find(int(*test)(int), ilist *ns); 

// count the number of ints in the list that pass the test
unsigned int ilist_count(int(*test)(int), ilist *ns);

// if n is 0, return NULL, otherwise
// build a list f(0), f(1), ... f(n-1)
// - for example, assuming a function "sqr",
//   ilist_build(4, sqr) --> 0:1:4:9:nil
ilist *ilist_build(unsigned int n, int(*f)(int));

/* === complete the operations specified above === */

/* your code here... */

ilist *ilist_new(int f, ilist *r) {
    ilist *new_list = (ilist *)malloc(sizeof(ilist));
    if(new_list == NULL) {
        fprintf(stderr, "malloc failed on ilist_new\n");
        exit(1); 
    }
    new_list->first = f;
    new_list->rest = r;
    return new_list;
}

void ilist_free(ilist *ns) {
    if (ns == NULL) {
        return;
    }
    ilist_free(ns->rest);
    free(ns);
}

void ilist_write(FILE *f, ilist *ns, int newline) { 
    for (ilist *current = ns; current != NULL; current = current->rest) {
        fprintf(f, "%d:", current->first);
    }
    fprintf(f, "nil");
    if (newline != 0) {
        fprintf(f, "\n");
    }
}

ilist *ilist_dup(ilist *ns) {
    ilist *new_list = (ilist *)malloc(sizeof(ilist));
    if (new_list == NULL) {
        fprintf(stderr, "malloc failed on ilist_dup\n");
        exit(1);
    }
    if (ns == NULL) {
        return NULL;
    }
    ilist *temp = new_list;
    for (ilist *current = ns; current != NULL; current = current->rest){
        temp->first = current->first;
        if (current->rest != NULL) {
            temp->rest = (ilist *)malloc(sizeof(ilist));
            if (temp->rest == NULL) {
                fprintf(stderr, "malloc failed on ilist_from_array\n");
                exit(1);
            }
        }
        temp = temp->rest;    
    }
    temp = NULL;
    return new_list;
}

ilist *ilist_from_array(int *arr, unsigned int len) {
    if (len == 0) {
        return NULL;
    }
    ilist *new_list = (ilist *)malloc(sizeof(ilist));
    if (new_list == NULL) {
        fprintf(stderr, "malloc failed on ilist_from_array\n");
        exit(1);
    }
    
    ilist *temp = new_list;
    for (int i = 0; i < len; i++) {
        temp->first = arr[i];
        if (i < len-1) {
        temp->rest = (ilist *)malloc(sizeof(ilist));
            if (temp->rest == NULL) {
                fprintf(stderr, "malloc failed on ilist_from_array\n");
                exit(1);
            }
        }
        temp = temp->rest;
    }
    temp = NULL;
    return new_list;
}

itree *itree_new(int root, itree *lsub, itree *rsub) {
    itree *new_tree = (itree *)malloc(sizeof(itree));
    if (new_tree == NULL) {
        fprintf(stderr, "malloc failed on itree_new\n");
        exit(1);
    }
    new_tree->root = root;
    new_tree->lsub = lsub;
    new_tree->rsub = rsub;
    return new_tree;
}

void itree_free(itree *t) {
    if (t == NULL) {
        return;
    }
    itree_free(t->lsub);
    itree_free(t->rsub);
    free(t);
}

void itree_write(FILE *f, itree *t) {
    if (t == NULL) {
        fprintf(f, ".");
        return;
    }
    fprintf(f, "(%d ", t->root);
    if (t->lsub == NULL) {
        fprintf(f, ". ");
    }
    else {
        itree_write(f, t->lsub);
    }
    if (t->rsub == NULL) {
        fprintf(f, ".)");
    }
    else {
        fprintf(f, " ");
        itree_write(f, t->rsub);
        fprintf(f, ")");
    }
}

itree *itree_dup(itree *t) {
    itree *new_tree = (itree *)malloc(sizeof(itree));
    if (new_tree == NULL) {
        fprintf(stderr, "malloc failed on itree_dup\n");
        exit(1);
    }
    if (t == NULL) {
        return NULL;
    }
    new_tree->root = t->root;
    if (t->lsub != NULL) {
        new_tree->lsub = itree_dup(t->lsub);
    }
    if (t->rsub != NULL) {
        new_tree->rsub = itree_dup(t->rsub);
    }
    return new_tree;
}

int ilist_sum(ilist *ns) {
    ilist *temp = ns;
    int sum = 0;
    while (temp != NULL) {
        sum += temp->first;
        temp = temp->rest;
    }
    return sum;
}

int itree_sum (itree *t) {
    if (t == NULL) {
        return 0;
    }
    return t->root + itree_sum(t->lsub) + itree_sum(t->rsub);
}

unsigned int ilist_len(ilist *ns) {
    ilist *temp = ns;
    int count = 0;
    while (temp != NULL) {
        count++;
        temp = temp->rest;
    }
    return count;
}

unsigned int itree_size(itree *t) {
    if (t == NULL) {
        return 0;
    }
    if (t->lsub == NULL && t->rsub == NULL) {
        return 1;
    }
    return 1 + itree_size(t->lsub) + itree_size(t->rsub);
}

unsigned int max(unsigned int a, unsigned int b) {
    if (a>=b) {
        return a;
    }
    return b;
}

unsigned int itree_height(itree *t) {
    if (t == NULL) {
        return 0;
    }
    if (t->lsub == NULL && t->rsub == NULL) {
        return 1;
    }
    return 1 + max(itree_height(t->lsub), itree_height(t->rsub));
}

ilist *connect(ilist *ms, ilist *ns) {
    if (ms==NULL) {
        return ns;
    }
    ilist *curr = ms;
    while (curr->rest != NULL) {
        curr = curr->rest;
    }
    curr->rest = ns;
    return ms;
}

ilist *inorder(itree *t) {
    if (t == NULL) {
        return NULL;
    }

    ilist *l_list = inorder(t->lsub);
    ilist *r_list = inorder(t->rsub);

    ilist *new_list = connect(l_list, ilist_new(t->root, r_list));
    return new_list;
}

ilist *leaves(itree *t) {
    if (t == NULL) {
        return NULL;
    }
    ilist *l_list = leaves(t->lsub);
    ilist *r_list = leaves(t->rsub);
    ilist *new_list;
    if (t->lsub == NULL && t->rsub == NULL) {
        new_list = connect(l_list, ilist_new(t->root, r_list));
    }
    else {
        new_list = connect(l_list, r_list);
    }
    return new_list;    
}

unsigned int len_int(int i) {
    unsigned int count = 1;
    if (i < 0) {
        count ++;
        i *= -1;
    }
    while (i > 9) {
        count ++;
        i /= 10;
    }
    return count;
}

char *ilist_tos(ilist *ns) {
    int count = 0;
    for (ilist *current = ns; current != NULL; current = current->rest) {
        int i = current->first;
        count += len_int(i);
        count++;
    }
    count += 3;
    char *ilist_str = (char *)malloc((sizeof(char)*count)+1);
    if (ilist_str == NULL) {
        fprintf(stderr, "malloc failed on ilist_tos\n");
        exit(1);
    }
    int j = 0;
    for (ilist *current = ns; current != NULL; current = current->rest) {
        int i = current->first;
        unsigned int len = len_int(i);
        unsigned int len_copy = len;
        if (i == 0) {
            ilist_str[j] = i +'0';
            j++;
            len--;
            len_copy --;
        }

        if (i < 0) {
            ilist_str[j] = '-';
            i *= -1;
            j++;
            len--;
            len_copy--;
        }
        
        while (len > 0) {
            ilist_str[j+len-1] = (i%10) + '0';
            i /= 10;
            len--;
        }

        j += (len_copy);
        
        ilist_str[j] = ':';
        j++;
    }
    ilist_str[j] = 'n';
    ilist_str[j+1] = 'i';
    ilist_str[j+2] = 'l';
    ilist_str[j+3] = '\0';
    return ilist_str;
}

int ilist_eq(ilist *ms, ilist *ns) {
    if(ilist_len(ms) != ilist_len(ns)) {
        return 0;
    }

    for (int i = 0; i < ilist_len(ms); i++) {
        ilist *current1 = ms;
        ilist *current2 = ns;
        if (current1->first != current2->first) {
            return 0;
        }
        current1 = current1->rest;
        current2 = current2->rest;
    }
    return 1;
}

ilist *ilist_find(int(*test)(int), ilist *ns) {
    for (ilist *current = ns; current != NULL; current = current->rest) {
        if ((*test)(current->first)) {
            return ilist_dup(current);
        }
    }
    return NULL;
}

unsigned int ilist_count(int(*test)(int), ilist *ns) {
    unsigned int count = 0;
    for (ilist *current = ns; current != NULL; current = current->rest) {
        if ((*test)(current->first)) {
            count++;
        }
    }
    return count;
}

ilist *ilist_build_helper(unsigned int n, int(*f)(int), unsigned int k) {
    if (n==0) {
        return NULL;
    }
    ilist *new_list = ilist_new((*f)(k-n), ilist_build_helper(n-1, f, k));

    return new_list;
    
}

ilist *ilist_build(unsigned int n, int(*f)(int)) {
    return ilist_build_helper(n, f, n);
}

int even(int i) {
    if (i % 2 == 0) {
        return 1;
    }
    
    return 0;
}

int odd(int i) {
    if (i % 2 == 1) {
        return 1;
    }

    return 0;
}

int square(int i) {
    return i*i;
}

int add_three(int i) {
    return i+3;
}

int main() {
    int test1[6] = {1, -3, 5, 0, -13, 16};
    int test2[0] = {};
    ilist *ilist_test1 = ilist_from_array(test1, 6);
    ilist *ilist_test2 = ilist_from_array(test2, 0);
    ilist *ilist_test3 = ilist_new(901, NULL);
    ilist_write(stdout, ilist_test1, 1);
    ilist_write(stdout, ilist_test2, 1);
    ilist_write(stdout, ilist_test3, 1);
    ilist *ilist_test4 = ilist_dup(ilist_test1);
    ilist_write(stdout, ilist_test4, 1);
    ilist_test1->first = 10;
    ilist_write(stdout, ilist_test1, 1);
    ilist_write(stdout, ilist_test4, 1);
    ilist_test4 = ilist_new(5, ilist_test4);
    ilist_write(stdout, ilist_test4, 1);
    itree *t1 = itree_new(1, NULL, NULL);
    itree *t2 = itree_new(2, NULL, NULL);
    itree *t3 = itree_new(3, t1, t2);
    itree *t4 = itree_new(4, NULL, NULL);
    itree *t5 = itree_new(5, NULL, NULL);
    itree *t6 = itree_new(6, t4, t5);
    itree *t7 = itree_new(7, t3, t6);
    itree *t8 = itree_new(8, NULL, NULL);
    itree *t9 = itree_new(9, t8, NULL);
    itree *t10 = itree_new(10, t7, t9);
    itree_write(stdout, t10);
    printf("\n");
    itree *t11 = itree_dup(t10);
    itree_write(stdout, t11);
    printf("\n");
    t10->root = 11;
    t11->root = 12;
    itree_write(stdout, t10);
    printf("\n");
    itree_write(stdout, t11);
    printf("\n");
    itree *t12 = NULL;
    
    printf("%d, %d\n", ilist_sum(ilist_test1), ilist_sum(ilist_test2));
    printf("%d, %d, %d\n", itree_sum(t10), itree_sum(t12), itree_sum(t2));
    printf("%d, %d\n", ilist_len(ilist_test1), ilist_len(ilist_test2));
    printf("%d, %d, %d\n", itree_size(t10), itree_size(t12), itree_size(t2));
    printf("%d, %d, %d\n",itree_height(t10),itree_height(t12),itree_size(t2));
    ilist *ilist_test5 = inorder(t10);
    ilist *ilist_test6 = leaves(t10);
    ilist_write(stdout, ilist_test5, 1);
    ilist_write(stdout, ilist_test6, 1);
 
    char *s1 = ilist_tos(ilist_test1);
    char *s2 = ilist_tos(ilist_test2);
    printf("%s, %s\n", s1, s2);
    
    
    printf("%d\n", ilist_eq(ilist_test1, ilist_test2));
    ilist *ilist_test7 = ilist_dup(ilist_test1);
    printf("%d\n", ilist_eq(ilist_test1, ilist_test7));
    ilist *test11 = ilist_find(&even, ilist_test1);    
    ilist_write(stdout, test11, 1);
    printf("%d\n", ilist_count(&even, ilist_test1));
    ilist *test12 = ilist_find(&odd, ilist_test1);
    ilist_write(stdout, test12, 1);
    printf("%d\n", ilist_count(&odd, ilist_test1));
    
    ilist *test8 = ilist_build(5, &square);
    ilist *test9 = ilist_build(0, &square);
    ilist *test10 = ilist_build(9, &add_three);
    ilist_write(stdout, test8, 1);
    ilist_write(stdout, test9, 1);
    ilist_write(stdout, test10, 1);
    
    free(s1);
    free(s2);
    ilist_free(ilist_test5);
    ilist_free(ilist_test6);
    itree_free(t10);
    itree_free(t11);
    itree_free(t12);
    ilist_free(ilist_test1);
    ilist_free(ilist_test2);
    ilist_free(ilist_test3);
    ilist_free(ilist_test4);
    ilist_free(ilist_test7);
    ilist_free(test8);
    ilist_free(test9);
    ilist_free(test10);
    ilist_free(test11);
    ilist_free(test12);
    return 0;
}
