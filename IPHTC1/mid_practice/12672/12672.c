// NTHUOJ 12672 - Three number   
// Description
// You will have three number A, B, C each represents a+b, b+c, c+a respectively.
// You need to answer what a, b, c are.
// Example:
// If A = 168, B = 134, C = 112
// And you need to calculate what a,b,c are.
// In this example, a = 73, b = 95, c = 39.

// Input
// Input only contains three number A, B, C(0 <= A, B, C <= 2*10^8)

// Output
// Output three number which represent a,b,c respectively.
// We guarantee that a, b, c will be integers.
// Remember to print \n at the end of output.

// Sample Input  
// 168 134 112

// Sample Output  
// 73 95 39

#include<stdio.h>

int main(){
    int a = 0;
    int b = 0;
    int c = 0;
    int sum = 0;
    scanf("%d %d %d", &a, &b, &c);
    sum = (a + b + c) / 2;
    printf("%d %d %d\n", sum - b, sum - c, sum - a);

    return 0;
}