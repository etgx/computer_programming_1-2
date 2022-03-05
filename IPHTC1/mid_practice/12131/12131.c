// NTHUOJ 12131 - No, I don't know the way, but....   
// Description
// Knuckles, from Ugandan, is finding his queen. Soon, he met Sonic the Hedgehog. "Do you know de way to our queen?", Knuckles asked. "No, I don't know the way, but...", not until Sonic finish his words, Knuckles spits him with a speed faster than sound! "I don't know the way But I DO know the distance between you and your queen!" Knukcles soon claps for him. However, Sonic seems very angry. He decides not telling Knuckles the answer directly, but give him a puzzle to solve. Although Knuckles is smart enough, he is too busy to solve it alone, now he asks you for help. Could you help him?
// Sonic will give Knuckles two numbers A and B, which may be non-negative integers or floats.
// A is the distance between Knuckles and an unknown site, B is the distance between the unknown site and the queen.
// Knuckles wants to know the longest distance between him and his queen, so that he could make the worst plan. You're going to write a program to help him. Go ahead!

// Input
// The input contains only one testcase.
// The first and the only line contains A and B, seperate with a space.

// Output
// The output contains only one number.
// Output the longest distance between Knuckles and his queen. You should output the number to three decimal places. Note that if the decimal place is 0, you still need to output them. For example: 32 -> 32.000, 15.23 -> 15.230
// Remember to print '\n' at the end of the output.

// Sample Input  
// 15.623 4

// Sample Output  
// 19.623

#include<stdio.h>

int main(){
    float a = 0;
    float b = 0;
    scanf("%f %f", &a, &b);
    printf("%.3f\n", a + b);
    return ;
}
