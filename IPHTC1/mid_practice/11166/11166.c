// NTHUOJ 11166 Simple integer sorting   
// Description
// Given some integers, please list them in increasing order.

// Input
// First line is an integer T (T <= 20) followed by T test cases.
// Each test case consists of two lines. First line is an integer n (n <= 104), and second line contains n integers V1, V2, ..., Vn. (-231< Vi < 231-1 for 1 <= i <= n )

// Output
// For each test case, list a line of numbers from the smallest one to the largest one ending with '\n'. Two adjacent numbers in one line should be separated by a whitespace.

// Sample Input  
// 3
// 3
// 1 3 2
// 4
// -1 -2 -3 -1
// 2
// 0 1
// Sample Output  
// 1 2 3
// -3 -2 -1 -1
// 0 1

// 2020/05/01 SYC

#include<stdio.h>
#include<stdlib.h>

int main(){
    int T = 0;
    scanf("%d\n", &T);

    for(int i = 0; i < T; i++){
        int n = 0;
        long int array[10005] = {0};
        scanf("%d\n", &n);

        for(int j = 0; j < n; j++){
            scanf("%ld", &(array[j]));
        }

        for(int p = 1; p < n; p++){
            for(int q = p; q > 0 && array[q] < array[q - 1]; q--){
                long int temp = array[q];
                array[q] = array[q - 1];
                array[q - 1] = temp;
            }
        }

        for(int k = 0; k < n - 1; k++){
            printf("%ld ", array[k]);
        }
        printf("%ld\n", array[n-1]);
    }

    return 0;
}