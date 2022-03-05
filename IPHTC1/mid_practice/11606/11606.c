// NTHUOJ 11606 - Factor Counter   
// Description
// Given an interval [L,R], please find out the integer which has the most positive factors (正因數) in this interval.
// If there are multiple answers, print the smallest of them.

// Input
// The first line contains an integer T, representing the number of testcases.
// The next T lines contain two integers L and R, representing the endpoints of the interval.
// 1 ≤ T ≤ 20
// 1 ≤ L ≤ R ≤ 20000

// Output
// For each testcase, please output a line contains an integer representing your answer.
// (i.e. Please print '\n' after each answer.)

// Sample Input  
// 5
// 5 5
// 5 6
// 5 7
// 5 8
// 5 12

// Sample Output  
// 5
// 6
// 6
// 6
// 12

// 2020/05/01 SYC

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void sieveOfEratosthenes(int target, int *primeRecord, int *primeCounter){
    int *table = (int *)malloc(sizeof(int) * (target + 1));
    // primeRecord = (int *)malloc(sizeof(int) * (target));
    // primeCounter = (int *)malloc(sizeof(int));

    for(int i = 0; i < target + 1; i++){
        table[i] = 1;
    }
    table[0] = 0;
    table[1] = 0;

    for(int i = 0; i < target; i++){
        primeRecord[i] = 0;
    }

    (*primeCounter) = 0;

    for(int i = 2; i <= target; i++){
        if(table[i] == 1){
            int multiplier = 1;
            
            primeRecord[(*primeCounter)] = i;
            (*primeCounter) = (*primeCounter) + 1;

            while(i * multiplier <= target){
                table[i * multiplier] = 0;
                multiplier++;
            }
        }
    }
}

int countFactors(int target, int *primeRecord, int primeCount){
    int factorCounter = 1;
    int primeCounter = 0;
    int remain = target;

    while(remain >= primeRecord[primeCounter] && primeCounter < primeCount){
        int thisFactorCount = 0;
        // printf("[%d]: %d %d\n", primeCounter, primeRecord[primeCounter], primeCount);
        while(remain % primeRecord[primeCounter] == 0){
            remain = remain / primeRecord[primeCounter];
            thisFactorCount++;
        }
        factorCounter = factorCounter * (thisFactorCount + 1);
        primeCounter++;
    }
    return factorCounter;
}

int main(){
    const int primeRecordLen = 35;
    const int primeUnder = 150;
    int *primeRecord = (int *)malloc(sizeof(int) * (primeUnder));
    int *primeCounter = (int *)malloc(sizeof(int));
    sieveOfEratosthenes(primeUnder, primeRecord, primeCounter);

    int t = 0;
    scanf("%d\n", &t);

    for(int i = 0; i < t; i++){
        int l = 0, r = 0; 
        scanf("%d %d\n", &l, &r);

        int maxNumber = 0;
        int maxFactor = 0;
        for(int j = l; j <= r; j++){
            int tempFactorNumber = countFactors(j, primeRecord, (*primeCounter));
            if(maxFactor < tempFactorNumber){
                maxNumber = j;
                maxFactor = tempFactorNumber;
            }else if(maxFactor == tempFactorNumber && maxNumber > j){
                maxNumber = j;
            }
        }

        printf("%d\n", maxNumber);
    }

    // for(int i = 0; i < (*primeCounter); i++){
    //     printf("%d ", primeRecord[i]);
    // }
    // printf("\n%d\n", (*primeCounter));

    return 0;
}