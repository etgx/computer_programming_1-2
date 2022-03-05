// NTHUOJ 12237 - TA's Heartfelt   
// Description
// "Oh, no! The problem is so hard! No, no, no... Am I too stupid?"
// "Hey, my code is right! Why do I always get a WA or TLE?"
// "The method is difficult to understand, why are TAs always give us such a hard problem?"
// "Did you heard that? I heard that the problem of the other professorss course is far more easier..." "Really? I should have chosen the other course..."
// Yeah, we TA all know that it's hard for you to understand these new concepts. However, we do hope you to learn some knowledge that is important or useful. Such as "Prefix Sum", you can pre-calculate all the sum of (1,i) to get any sum of (i,j), which is far more faster than calculate the sum using for/while... right? 
// What about gcd or fast power(快速冪)? I think all of you may learn the split phase division(輾轉相除法), so it should be not too hard to you guys to learn that, right? For the part of fpw(fast power), it's not too hard to realize how it works, which is also wonderful that we could calculate nm or the n-th Fibonacci number so fast, even without include<moon>!
// We do hope you guys could enjoy learning these interesting concepts instead of just taking the course, getting an A/A+, and treat this course as a part of your 4.3 GPA. 
// If you don't want to learn these extra knowledge, or you're too busy to learn, you can just submit a brute-force solution without using any of the concepts above, you can still pass 3-5 testcases(only if the method is right).
// So now, we're going to have another question. Don't worry, you can get an AC by brute force (though that would be a little difficult).
// You guys have learned IEEE floating point number, right? If you forget it, rewind it, please. Our problem won't become easier for you :(
// You are given a IEEE-754 floating number with single precision(which is type "float" in C)
// You are going to output every bit of the number, from the largest bit to the smallest bit (including every 0)
// Hint.1: You may solve this problem by using pointer tricks extremely easily. However, you can still solve this by using traditional way. :)
// Hint.2: You may refer to this page to check the binary of a fp number.
// Enjoy!

// Input
// The input contains multiple testcases, which means we'll input several floating point numbers, ended by EOF.
// Note that there may be precision error due to the precision of floating point number. What we want you to output is the binary bits of the floating point number stored in C variable.
// We recommand to use scanf as your input function.
// You can take a look and observe the sample IO.
// The range of the floating point number is -1020 ~ 1020.

// Output
// Output every bit of the floating point number. Remember to print a '\n' at the end of every output.

// Sample Input  
// 28.759
// 18
// 213.888
// -31.25
// -10
// 0

// Sample Output  
// 01000001111001100001001001101111
// 01000001100100000000000000000000
// 01000011010101011110001101010100
// 11000001111110100000000000000000
// 11000001001000000000000000000000
// 00000000000000000000000000000000

// 2020/05/09 SYC

// Reference: 
// https://www.geeksforgeeks.org/program-for-conversion-of-32-bits-single-precision-ieee-754-floating-point-representation/
// https://www.itread01.com/content/1544817994.html

#include<stdio.h>
#include<stdlib.h>

typedef union{
    float f;
    struct {
        unsigned int mantissa: 23;
        unsigned int exponent: 8;
        unsigned int sign: 1;
    } raw;
}Float;

void printBin(int num, int len){
    for(int i = len - 1; i >= 0; i--){
        printf("%d", (num >> i) & 1);
    }
}

void printFloat(float f){
    Float fStruct;
    fStruct.f = f;
    printBin(fStruct.raw.sign, 1);
    printBin(fStruct.raw.exponent, 8);
    printBin(fStruct.raw.mantissa, 23);
    printf("\n");
}

int main(){

    float f = 0;
    while((scanf("%f", &f)) != EOF){
        printFloat(f);
    }
    
    return 0;
}