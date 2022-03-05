// NTHUOJ 11758 - A - Markov Matrix   
// Description
// Writer: jjjjj19980806       Description: pclightyear        Difficulty: ★★★☆☆
// In mathematics, a Markov matrix is a square matrix used to describe the transitions of a Markov chain. Each of its entries is a nonnegative real number representing a probability. It has found use throughout a wide variety of scientific fields, including population genetics.
// Consider a country with n cities. Originally, each city has its own population, which can be described as a state vector X0. As the time pass by, the population will move from one city to another. The whole progress can be described as a n × n Markov matrix A.
// In this problem, if the state vector of the city population now is Xn, after a year, the state vector will become Xn+1, where Xn+1 = AXn.
// Now, you are given the original population in each city by a state vector X0 and the Markov matrix A. You need to calculate how many years it takes to let the first city’s population to drop below or equal to a specific number p, or it will never drop below p.

// Input
// The first line contains an integer T, representing the number of test cases.
// For each test case:
// The first line contains an integer n, representing the number of the cities.
// The next n lines contain n floating-point number aij, representing each entry in the Markov matrix A.
// The next line contains n integers Xi, representing each entry in the state vector X0.
// The next line contains an integer p, representing the specific number of population.
// It is guaranteed that:
// 1 ≤ T ≤ 5
// 1 ≤ n ≤ 5
// 0 ≤ X0i ≤ 106

// Output
// Please output how many years it takes to let the first city’s population to drop below p, or output "Never" if it will never drop below p.

// Sample Input  
// 3
// 
// 2
// 0.5 0.5
// 0.5 0.5
// 1000 0
// 500
// 
// 3
// 0.4 0.5 0.3
// 0.4 0.3 0
// 0.2 0.2 0.7
// 6000 3000 1000
// 1000
// 
// 2
// 0.9 0.8
// 0.1 0.2
// 1000 0
// 889

// Sample Output  
// 1
// Never
// 3

// 2020/06/19 SYC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *malloc1d(const int unitSize, const int n){
    void *res = (void *)malloc(unitSize * n);
    memset(res, 0, unitSize * n);
    return res;
}

void **malloc2d(const int unitSize, const int rows, const int cols){
    void **res = (void **)malloc(sizeof(void *) * rows);
    for(int i = 0; i < rows; i++){
        res[i] = (void *)malloc1d(unitSize, cols);
        // res[i] = (void *)malloc(unitSize * cols);
        // memset(res[i], 0, unitSize * cols);
    }
    return res;
}

// Multiply Square
long double **mulSq(long double **a, long double **b, const int n){
    long double **res = (long double **)malloc2d(sizeof(long  double), n, n);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){
                res[i][j] = res[i][j] + a[i][k] * b[k][j];
            }
        }
    }

    return res;
}

// Multiply Vertex
long double mulVer(long double  *a, long double *b, const int n){
    long double res = 0;
    for(int i = 0; i < n; i++){
        res = res + a[i] * b[i];
    }

    return res;
}

void freeSq(long double **a, const int n){
    for(int i = 0; i < n; i++){
        free(a[i]);
    }
}

int main(){
    int T = 0;
    scanf("%d\n", &T);

    for(int i = 0; i < T; i++){
        int n = 0;
        long double target = 0;
        scanf("%d\n", &n);
        long double **transit = (long double **)malloc2d(sizeof(long double), n, n);
        long double **mulTransit = (long double **)malloc2d(sizeof(long double), n, n);
        long double *init = (long double *)malloc1d(sizeof(long double),  n);

        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){
                scanf("%Lf", &(transit[j][k]));
                mulTransit[j][k] = transit[j][k];
                // printf("%d\n")
            }
        }
        for(int j = 0; j < n; j++){
            scanf("%Lf", &(init[j]));
        }
        scanf("%Lf\n", &target);

        // Solve
        int iters = 0;
        long double prevP = init[0] + 1;
        long double p = init[0];
        long double **freeTransit = mulTransit;
        while(p > target && prevP > p){
            prevP = p;
            p = mulVer(mulTransit[0], init, n);
            mulTransit = mulSq(mulTransit, transit, n);
            iters++;
            // Free Memory
            freeSq(freeTransit, n);
            freeTransit = mulTransit;
            // printf("Iters: %d -> %Lf\n", iters, p);
        }

        if(p <= target){
            printf("%d\n", iters);
        }else{
            printf("Never\n");
        }
    }


    return 0;
}