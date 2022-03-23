#include <stdio.h>
#include <ctype.h>

int main()
{
    int c = getchar();
    int i = 0;
    while (c != EOF) {
        if (isgraph(c) || c == ' ')
            printf("%d\t%c\t%d\n", i++, c, c);
        else
            printf("%d\t~\t%d\n", i++, c);
        c = getchar();
    }
}