#include <stdio.h>
#include <stdlib.h>
#include "function.h"


int main(){

    int n, k;

    while(scanf("%d%d", &n, &k)!=EOF){
        head = createList(n);
        solve(n, k);
    }

    return 0;
}