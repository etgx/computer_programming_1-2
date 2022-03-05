#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    char c;
    struct node *prev, *next;
}Node;

int main(){
    int T = 0, N = 0;
    scanf("%d", &T);
    for(int i = 0; i < T; i++){
        scanf("%d", &N);
        for(int j = 0; j < N; j++){
            char c = 0;
            scanf("%c", &c);
            switch (c)
            {
            case 'B':
                
                break;
            
            default:
                break;
            }
        }
    }
    return 0;
}
