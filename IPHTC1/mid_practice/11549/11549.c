// NTHUOJ 11549 Easy Palindrome   
// Description
// The input is a 6-digit floating number N that consists of digits 1-9 except 0. For example, 156.854 is such a number. The task is to reverse the order of the digits of integer part and decimal part respectively to get a new six-digit floating number M, and compute the sum of the N and M. For example, if N is 123.456, then M is 321.654, and the answer should be 445.110.
// Hint1: you can use double type to store input
// Hint2: if your answer is 445.110000, you can use %.3lf to print 445.110

// Input
// A six-digit floating number consisting of 1-9 except 0

// Output
// The sum of the input number and its reversal
// The answer should be expressed as a floating point number with precision to the three decimal place. For example, 445.110
// Note that you do not need to print ‘\n’ at the end of the output.

// Sample Input  
// 123.456
// Sample Output  
// 445.110

// 2020/05/01 SYC

#include<stdio.h>
#include<stdlib.h>

int main(){
    double N = 0, M = 0;
    char NStr[10] = {0};
    scanf("%s\n", NStr);

    N = atof(NStr);

    char temp = '0';
    temp = NStr[0];
    NStr[0] = NStr[2];
    NStr[2] = temp;

    temp = NStr[4];
    NStr[4] = NStr[6];
    NStr[6] = temp;

    M = atof(NStr);

    printf("%.3lf", N + M);

    return 0;
}