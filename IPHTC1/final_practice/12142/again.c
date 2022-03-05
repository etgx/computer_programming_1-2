// Another AC version
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MaxNumOfAi 105
#define MaxSizeOfAi 1005

int cmp(const char *a, const char *b){
    char ab[MaxSizeOfAi * 2] = {0};
    char ba[MaxSizeOfAi * 2] = {0};
    strncpy(ab, a, MaxSizeOfAi);
    strncpy(ba, b, MaxSizeOfAi);
    strncat(ab, b, MaxSizeOfAi);
    strncat(ba, a, MaxSizeOfAi);

    return strcmp(ba, ab) > 0;
}

int main(){
    int n = 0;
    while(scanf("%d", &n) != EOF){
        char buff[MaxNumOfAi][MaxSizeOfAi] = {0};
        for(int i = 0; i < n; i++){
            scanf("%s", buff[i]);
        }
        qsort(buff, MaxNumOfAi, MaxSizeOfAi, (int (*)(const void *, const void *))cmp);

        for(int i = 0; i < n; i++){
            printf("%s", buff[i]);
        }
        printf("\n");
    }

    return 0;
}