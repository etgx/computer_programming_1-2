// IPHTC2 Week5 Problem 2 | NTHUOJ 12145 - Species of Knuckles
// Description
// here're different kinds of Knuckles in this world. According to the research, there're 2626 different kinds of Knuckles.
// Let's denote different kind of Knuckles as 'a' ~ 'z'.
// Knuckles is a magic creature.
// If you have at least 22 same kind of Knuckles, you can transform these Knuckles into any kind of Knuckles with same number of them.
// For example：
// if you have n=3 Knuckles representing as "aab" you can transform 'a' Knuckles into 'b' Knuckles. In the end you will get "bbb" Knuckles.
// Because you're a deadly Ethnic nationalism, you want all Knuckles to be the same.
// You can do the transformation many times.
// Find out whether you can do that.

// Input
// Input contains two lines.
// First line contains only one integer n( 1 <= n <= 10^7 ), representing the number of Knuckles.
// Second line contains one string, the length of nn.

// Output
// If you can make all Knuckles the same, output "I'm the god of Knuckles!"
// Otherwise, output "Different makes perfect"
// Remember to print \n at the end of output

// Sample Input 1 
// 5
// abcca

// Sample Output 1
// I'm the god of Knuckles!

// 2021/10/30 SYC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_ALPHABET 26

int main(){
    int n = 0, is_god = 0, counters[NUM_ALPHABET] = {0};
    scanf("%d", &n);

    if(n == 1){
        is_god = 1;
    }else{
        for(int i = 0; i < n; i++){
            char character = getchar();
            int bin = (int)(character - 'a');

            counters[bin]++;
            if(counters[bin] > 1){
                is_god = 1;
                break;
            }
        }
    }
    
    if(is_god){
        printf("I'm the god of Knuckles!\n");
    }else{
        printf("Different makes perfect\n");
    }
    return 0;
}