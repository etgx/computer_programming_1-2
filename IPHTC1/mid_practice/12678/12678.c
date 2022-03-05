// NTHUOJ 12678 - Count 1s   
// Description
// Given two number a,b.
// You need to calculate how many 1 appear in range a~b(decimal representation).
// Example:
// Given a = 1, b = 11.
// 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
// There're four 1 appear in range 1~11(1, 10, 11).
// The answer is 4.

// Input
// First line contains one integer t(1 <= t <= 10^6) which means the number of testcases.
// The following t lines, each line contains two integer a, b( 1 <= a <= b <= 10^6)

// Output
// For each testcase print only one number which means the number of 1 appear in range a~b.
// Remember to print \n at the end of output.

// Sample Input  
// 3
// 1 11
// 10 100
// 1 2

// Sample Output  
// 4
// 20
// 1

// SYC
// 2020 / 4 / 13

#include<stdlib.h>
#include<stdio.h>

int main(){
    long int n = 0;

    long int prefixSum[1000002];
    long int count = 0;
    for(long int i = 1; i < 1000002; i++){
        
        char strInt[10];
        sprintf(strInt, "%ld", i);
        // printf("%s\n", strInt);
        // printf("%ld\n", sizeof(strInt));
        for(long int j = 0; j < 10; j++){
            // printf("%c", strInt[j]);
            if(strInt[j] == '1'){
                count++;
            }
        }

        prefixSum[i] = count;
    }

    scanf("%ld", &n);
    for(long int i = 0; i < n; i++){
        long int a = 0;
        long int b = 0;

        scanf("%ld", &a);
        scanf("%ld", &b);

        printf("%ld\n", prefixSum[b] - prefixSum[a-1]);
    }

    return 0;
}