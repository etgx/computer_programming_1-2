// Another AC Version
#include <stdio.h>
#include <stdlib.h>

typedef struct cattoast{
    int x, y, isVisited;
}CatToast;

int disSq(CatToast a, CatToast b){
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

int dfs(CatToast *cts, const int n, const int start, const int r){ // Return the size of blackhole
    int sumOfBlk = 1;
    for(int i = 0; i < n; i++){
        if(!cts[i].isVisited){
            if(disSq(cts[start], cts[i]) <= r * r){
                cts[i].isVisited = 1;
                sumOfBlk += dfs(cts, n, i, r);
            }
        }
    }

    return sumOfBlk;
}

void solve(CatToast *cts, const int n, const int r){
    int blks = 0;
    int remains = 0;
    for(int i = 0; i < n; i++){
        int res = 0; // Suppose cts[i] has been visited
        if(!cts[i].isVisited){
            cts[i].isVisited = 1;
            res = dfs(cts, n, i, r);
        }
        
        if(res > 1){
            blks++;
        }else if(res == 1){
            remains++;
        }
    }

    printf("%d %d\n", remains, blks);
}

int main(){
    int n = 0, r = 0;
    scanf("%d %d\n", &n, &r);
    CatToast *cts = (CatToast *)malloc(sizeof(CatToast) * n);

    for(int i = 0; i < n; i++){
        scanf("%d %d\n", &(cts[i].x), &(cts[i].y));
        cts[i].isVisited = 0;
    }

    solve(cts, n, r);

    return 0;
}