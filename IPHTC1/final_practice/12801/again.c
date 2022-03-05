#include <stdio.h>
#include <stdlib.h>
#define MaxCoffees 200010

int binSearch(long int *coffees, const int start, const int end, const long int m){
    // m: target
    // Goal: find out the number coffees[midI] < m, coffees[midI] is the largest one
    int startI = start, endI = end;
    int midI = (start + end) / 2;

    while(startI < endI){
        printf("Start[%d]: %ld End[%d]: %ld Mid[%d]: %ld\n", startI, coffees[startI], endI, coffees[endI], midI, coffees[midI]);
        if(coffees[midI] < m){
            endI = midI;
        }else{
            startI = midI + 1;
        }
        midI = (startI + endI) / 2;
    }

    return midI;
}

int solve(long int *coffees, long int *prefixSum, const int n, const long int m){
    for(int d = 1; d <= n; d++){
        // 
        // Get iteration round numer: if the modulo > 0 means it has remaining days except fully division
        int maxRound = n / d + (n % d > 0);
        long int accumCode = prefixSum[d];
        for(int r = 1; r < maxRound; r++){
            int start = r * d + 1, end = (r + 1) * d > n? n : (r + 1) * d;
            int binRes = binSearch(coffees, start, end, r);

            if(coffees[binRes] >= r){
                accumCode += (prefixSum[binRes] - prefixSum[start - 1] - (end - start + 1) * r);
            }else{

            }
        }
    }
}

int main(){
    int t = 0;
    long int m = 0;
    scanf("%d %ld\n", &t, &m);
    long int *a = (long int *)malloc(sizeof(long int) * t);

    for(int i = 0; i < t; i++){
        scanf("%ld", &(a[i]));
    }
    int res = binSearch(a, 0, t - 1, m);
    printf("[%d]: %ld\n", res, a[res]);


    // for(int i = 0; i < t; i++){
    //     // n: Number of coffees, m: Traget of codes
    //     int n = 0;
    //     long int m = 0;
    //     long int coffees[MaxCoffees] = {0}, prefixSum[MaxCoffees] = {0};
    //     scanf("%d %ld\n", &n, &m);

    //     scanf("%ld", &(coffees[0]));
    //     prefixSum[0] = coffees[0];
    //     for(int j = 1; j <= n; j++){
    //         scanf("%ld", &(coffees[j]));
    //         prefixSum[j] = prefixSum[j - 1] + coffees[j];
    //     }

    //     solve(coffees, prefixSum, n, m);
    // }

    return 0;
}