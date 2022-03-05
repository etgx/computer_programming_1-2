// NTHUOJ 11119 binary addition   
// Description
// Given a positive integer N, transform it to its unsigned binary representation (e.g. 10 => 1010). Your program needs to 
// output the binary representation of N+1 and the number of carries during the addition in binary representation.
// For example, if the input is 11 (in decimal), your program needs to output 1100, because it is the binary representation of 11+1=12. Also your program needs to output 2, because during the binary addition of 11+1, there are two carries generated.
//      1011 (11 in binary)
// +    0001 (1 in binary)
// ---------------------------------
//      1100 (12 in binary)

// Input
// The input consist of an integer N (0 <= N <= 1022)

// Output
// The "unsigned" binary representation of N+1 and the number of carries during the binary addition of N+1. Those two numbers are separated by a space. Note that you do not need to print ‘\n’ at the end of the output.

// Sample Input  
// 11 
// Sample Output  
// 1100 2 

// 2020/05/01 SYC

#include<stdio.h>
#include<stdlib.h>

int countCarry(int dec, int carry){
    int count = 0;
    if(dec > 1){
        count = countCarry(dec >> 1, dec & carry);
    }
    // printf("%d", (dec ^ carry) & 1);
    return count + (dec & carry);
}

void bin(int dec){
    if(dec > 1){
        bin(dec >> 1);
    }
    printf("%d", dec & 1);
}

int main(){
    int input = 0;
    int carryTimes = 0;
    scanf("%d", &input);

    bin(input + 1);
    carryTimes = countCarry(input, 1);
    printf(" %d", carryTimes);

    return 0;
}