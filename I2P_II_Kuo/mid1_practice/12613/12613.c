// I2P - Kuo Week0 Problem 6 | NTHUOJ 12613 - Yet Another Meme Problem
// Description
// Problem slightly modified from codeforces educational round 80
// meme
// You are given two integers A and B, calculate the number of pairs (a,b) such that 1≤a≤A, 1≤b≤B, and the equation a⋅b+a+b=conc(a,b) is true.
// conc(a,b) is the concatenation of a and b (for example, conc(12,23)=1223, conc(100,11)=10011). a and b should not contain leading zeroes.

// Hints
// For the first test case in sample input, there is only one suitable pair : a=1, b=9 (1+9+1⋅9=19).
// Since the number is large in this problem, it is suggested to use long long int.
 
// Input
// The first line contains t (1≤t≤100) — the number of test cases.
// Each test case contains two integers A and B (1≤A, b≤10^9).

// Output
// Print one integer — the number of pairs (a,b) such that 1≤a≤A, 1≤b≤B, and the equation a⋅b+a+b=conc(a,b) is true.

// Sample Input  

// 3
// 1 11
// 4 2
// 191 31415926

// Sample Output  

// 1
// 0
// 1337

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NUM_LEN 32

long long count_B_case(long long B){
    char B_str[NUM_LEN] = {0}, max_num_str[NUM_LEN] = {0};
    sprintf(B_str, "%lld", B);
    // Count the number of the digits of variable B
    long long digits = strlen(B_str), B_case = 0;
    // Fill the digit slots with 9 as variable 'max_num_str'. If the number of the digits is 8, then the 'max_num_str' would be '99999999'
    for(long long i = 0; i < digits; i++){
        max_num_str[i] = '9';
    }
    // Convert the string of the number to long long integer
    long long max_num = atoll(max_num_str);
    // printf("Digits: %lld, Max Num: %lld\n", digits, max_num);
    // If the variable 'max_num' <= B, then the useful cases of the number B is the digits of 'max_num', otherwise, should be the digits of 'max_num' - 1.
    if(B >= max_num){
        B_case = digits;
    }else{
        B_case = digits - 1;
    }

    return B_case;
}

long long count_case(long long A, long long B){
    long long B_case = count_B_case(B), A_case = A;
    // a * b + a + b = a * (b + 1) + b
    // If b + 1 = 10^n, n >= 0, then a * (b + 1) + b = a * 10^n + b = a || b (where we denote || as the operator of concatenation).
    return A_case * B_case;
}

int main(){
    long long t = 0;
    scanf("%lld\n", &t);

    for(long long i = 0; i < t; i++){
        long long A = 0, B = 0;
        scanf("%lld %lld\n", &A, &B);
        printf("%lld\n", count_case(A, B));
    }

    return 0;
}