// NTHUOJ 12129 - Do you know de way?   
// Description
// Knuckles, from Ugandan, is finding his queen. He accidentally find a ancient stele which curved two numbers on it. He reckon it as a clue to find his queen. Knuckles is very smart. He soon realizes that the rule between numbers.
// The stele contains two numbers l,r which means the range from l ~ r .
// Knuckles wants to find two different numbers x,y in the range, 
// in other word l <= x < y <= r.
// And Knuckles also wants that x divides y( y%x == 0 ). 
// Knuckles thinks that the minimum sum of x+y will be the clue to find the queen. Because the stele is from Ugandan gods there is always an answer.
// Help Knuckles find his queen or he will spit on you.

// Input
// input contains two integer l and r ( 1 <= l < r <= 109 )

// Output
// output contains two integer x and y ( l <= x < y <= r ) which x divides y.( remember print \n at the end of output and x ,y are seperated by a blank.)

// Sample Input  
// 9 30

// Sample Output  
// 9 18

#include<stdio.h>

int main(){
    float a = 0;
    float b = 0;
    scanf("%f %f", &a, &b);
    printf("%.3f\n", a + b);
    return 0;
}
