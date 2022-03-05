// NTHUOJ 11099 Money Money   
// Description
// Jay, Jolin and JJ are three people.
// All of them have some money.
// 1. Jay and Jolin have X dollors.
// 2. Jolin and JJ have Y dollors.
// 3. Jay and JJ have Z dollors.
// How many dollars does each of them have?

// Input
// Three positive even integers, X, Y and Z.

// Output
// The output contains three positive even integers indicating the money of Jay, Jolin, and JJ. 
// There is a whitespace between any two integers and a newline character '\n' at the end of the line.

// Sample Input  
// 170 160 190

// Sample Output  
// 100 70 90

// 2020/05/01 SYC

#include<stdio.h>
#include<stdlib.h>

int main(){
    long int X = 0, Y = 0, Z = 0;
    long int sum = 0;
    scanf("%ld %ld %ld\n", &X, &Y, &Z);

    sum = (X + Y + Z) / 2;
    
    printf("%ld %ld %ld\n", sum - Y, sum - Z, sum - X);

    return 0;
}