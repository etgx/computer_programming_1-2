// NTHUOJ 11770 - G - XOR   
// Description
// Writer: jjjjj19980806       Description: pclightyear        Difficulty: ★★★☆☆
// Given n numbers, you need to find a number k such that SUM is minimum,
// where we define SUM = ( a1 ^ k ) + ( a2 ^ k ) + ... + ( an ^ k )
// (^ stands for the "xor" bitwise operation of the two operand)

// Input
// The first line contains an integer n, representing the number of numbers.
// The next line contains n integers ai, representing each given number.
// It is guaranteed that:
// n ≤ 105
// 0 ≤ ai ≤ 106
// All numbers ( ai and k ) are unsigned numbers

// Output
// Please output the value of SUM.
// Note SUM may exceed INT.

// Sample Input  
// 6
// 1 2 3 4 5 6

// Sample Output  
// 21

#include<stdio.h>
#include<stdlib.h>

long long int solve1(int *a, int n){
    int minTarget = 0;
    long long int sum = 0, unit = 1;

    for(int i = 0; i < 32; i++){
        // int unit = 1;
        int count = 0;

        for(int j = 0; j < n; j++){
            // printf("a[%d] >> %d = %d & 1 = %d\n", j, i, (a[j] >> i), (a[j] >> i) & 1);
            count += ((a[j] >> i) & 1);
        }
        // printf("%dth\tbit count: %d\tunit: %lld\n", i, count, unit);
        if(count >= n - count){ // 1 is more than 0
            // 1 xor 1 = 0, to minimize the sum, set as 1
            minTarget += unit;   
        }
        unit = unit * 2;
    }

    for(int i = 0; i < n; i++){
        sum += (long long int)(a[i] ^ minTarget);
    }

    return sum;
}

long long int solve2(int *a, int n){
    // Goal: Let every bit of each number equal to 0 as many as possible after XOR
    int minTarget = 0;
    long long int sum = 0, tempSum = 0, unit = 1;

    for(int i = 0; i < 32; i++){
        // int unit = 1;
        int count = 0;

        for(int j = 0; j < n; j++){
            // printf("a[%d] >> %d = %d & 1 = %d\n", j, i, (a[j] >> i), (a[j] >> i) & 1);
            count += ((a[j] >> i) & 1);
        }
        // printf("%dth\tbit count: %d\tunit: %lld\n", i, count, unit);
        if(count >= n - count){ // 1 is more than 0
            // 1 xor 1 = 0, to minimize the sum, set as 1
            sum += (long long int)(n - count) * unit;
        }else{
            sum += (long long int)count * unit;
        }
        unit = unit * 2;
    }

    return sum;
}

int main(){
    int n = 0, minTarget = 0;
    long long int sum = 0, tempSum = 0;
    scanf("%d\n", &n);
    int *a = (int *)malloc(sizeof(int) * n);

    for(int i = 0; i < n; i++){
        int temp = 0;
        scanf("%d", &temp);
        a[i] = temp;
    }

    // printf("%lld\n", solve1(a, n));
    printf("%lld\n", solve2(a, n));
    
    free(a);
    return 0;
}