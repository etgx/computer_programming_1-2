#include "function.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, k;
    while( scanf("%d%d", &n, &k)!=EOF )
    {
        Node *head;
        head = createList(n);
        printf( "%d\n", solveJosephus(&head, k) );
        freeList(head);
    }
    return 0;
}