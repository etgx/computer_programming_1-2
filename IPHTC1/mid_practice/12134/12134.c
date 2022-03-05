// NTHUOJ 12134 - The Big Hammer Rise   
// Description
// A famous streamer once said: " Abortion Uncle!! Begin abort!!! " The Abortion Uncle is also known as "The Big Hammer Rise". The famous streamer wants to know the exactly time "Big Hammer Rise" kill an enemy. Because he got a double kill, he know exacly two time which denote as a, b.
// The famous streamer will give you two number a,b which are represented as float numbers and have two digit after the decimal point.
// For example：
// If a,b are ranged from 1~99, 1<= a , b < 100;
// a,b will be like these forms： 18.00,  99.30,  71.22
// You need to calculate ans = a*b, and ans should follow the rule:
// if the number of digits after decimal point is less then four digits, then you need to print 0 to make it four digits.
// For example: 18.56 -> 18.5600, 18 -> 18.0000, 18.9 -> 18.9000
// If you tell him the right answer he will help you kill the ice bird.
// ( Note: you can use scanf("%d.%d %d.%d", &int, &int, &int, &int). Use %f may cause trouble because the precision of float type. )
// ( Note: you can use  printf("%d.%04d\n", int/10000, int%10000); )

// Input
// input only contains two float number a,b ( 1<= a , b < 100 ) the two number are seperated by a blank.

// Output
// output contains only a float number which have four digit after the decimal point.
// remember to print \n at the end of output.

// Sample Input  
// 39.78 61.80

// Sample Output  
// 2458.4040

#include "stdio.h"
int main(){
	int a, b, c, d;
	scanf("%d.%d %d.%d", &a, &b, &c, &d);
	int product = (a * 100 + b) * (c * 100 + d);
	printf("%d.%04d\n", product/10000, product%10000);
}