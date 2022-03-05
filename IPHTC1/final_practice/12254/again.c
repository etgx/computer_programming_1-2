#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define Mod 1000000007
#define TransMSize 3
#define P1 1
#define P2 12
#define P3 13

void **malloc2d(const int unitSize, const int rows, const int cols){
    void **p = (void **)malloc(sizeof(void *) * rows);
    for(int i = 0; i < rows; i++){
        p[i] = (void *)malloc(unitSize * cols);
        memset(p[i], unitSize * cols, 0);
    }
    return p;
}

long long int mod(const long long int a){return a % Mod;}

long long int **mulSq(long long int **a, long long int **b, const int n){
    long long int **res = (long long int **)malloc2d(sizeof(long long int), n, n);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){
                res[i][j] = mod(mod(res[i][j]) + mod((mod(a[i][k]) * mod(b[k][j]))));
            }
        }
    }

    return res;
}

long long int mulVert(long long int **a, long long int *b, const int n){
    long long int x = 0;
    for(int i = 0; i < n; i++){
        x = mod(mod(x) + mod(mod(a[0][i]) * mod(b[i])));
    }
    return x;
}

long long int **genIdM(const int n){
    long long int **res = (long long int **)malloc2d(sizeof(long long int), n, n);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i == j){res[i][j] = 1;}
            else{res[i][j] = 0;}
        }
    }
    return res;
}

long long int **genTransM(){
    long long int **res = (long long int **)malloc2d(sizeof(long long int), TransMSize, TransMSize);
    res[0][0] = 1;
    res[0][1] = 2;
    res[0][2] = 1;
    res[1][0] = 1;
    res[1][1] = 0;
    res[1][2] = 0;
    res[2][0] = 0;
    res[2][1] = 1;
    res[2][2] = 0;
    return res;
}

long long int **fastP(const int n, const long long int term){
    long long int **base = genTransM();
    long long int **accum = genIdM(TransMSize);
    long long int y = term;
    // long long int a = 0;
    // long long int b = 1;

    while(y > 1){
        if(y & 1){ // Odd
            accum = mulSq(accum, base, TransMSize);
            base = mulSq(base, base, TransMSize);
            // a = a + b;
            // b = b * 2;
        }else{ // Even
            base = mulSq(base, base, TransMSize);
            // b = b * 2;
        }
        y = y >> 1;
    }

    // printf("A: %lld B: %lld\n", a, b);
    return mulSq(accum, base, TransMSize);
}

int main(){
    int t = 0;
    scanf("%d\n", &t);

    for(int i = 0; i < t; i++){
        long long int x = 0;
        scanf("%lld\n", &x);
        if(x == 1){
            printf("%d\n", P1);
        }else if(x == 2){
            printf("%d\n", P2);
        }else if(x == 3){
            printf("%d\n", P3);
        }else{
            long long int init[3] = {P3, P2, P1}; // Problem: Often place in wrong order
            long long int **trans = fastP(TransMSize, x - 3);
            long long int res = mulVert(trans, init, TransMSize);
            printf("%lld\n", res);
        }
    }

    return 0;
}