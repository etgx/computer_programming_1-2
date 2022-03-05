// NTHUOJ 12145 - Species of Knuckles   
// Description
// There're different kinds of Knuckles in this world. According to the research, there're 26 different kinds of Knuckles.
// Let's denote different kind of Knuckles as 'a' ~ 'z'.
// Knuckles is a magic creature.
// If you have at least 2 same kind of Knuckles, you can transform these Knuckles into any kind of Knuckles with same number of them.
// For example：
// if you have n=3 Knuckles representing as "aab" you can transform 'a' Knuckles into 'b' Knuckles. In the end you will get "bbb" Knuckles.
// Because you're a deadly Ethnic nationalism, you want all Knuckles to be the same.
// Find out whether you can do that.
// NOTE: Case 6 limits the memory to 1 MB, so try not to declare a large array.

// Input
// Input contains two lines.
// First line contains only one integer n( 1 <= n <= 107 ), representing the number of Knuckles.
// Second line contains one string, the length of n.

// Output
// If you can make all Knuckles the same, output "I'm the god of Knuckles!"
// Otherwise,  output "Different makes perfect"
// Remember to print \n at the end of output

// Sample Input  
// 5
// abcca

// Sample Output  
// I'm the god of Knuckles!

// 2020/05/19 SYC

#include<stdlib.h>
#include<stdio.h>

#define TypeOfKnukles 26

int main(){
    long int n = 0;
    long int knukles[TypeOfKnukles] = {0};
    scanf("%ld\n", &n);

    if(n == 1){
        printf("I'm the god of Knuckles!\n");
        return 0;
    }

    for(long int i = 0; i < n; i++){
        char temp;
        scanf("%c", &temp);
        // printf("%c %d %d\n",temp,  temp, temp - 97);
        knukles[temp - 97]++;
    }

    int flag = 1;
    for(int i = 0; i < TypeOfKnukles; i++){
        if(knukles[i] > 1){
            printf("I'm the god of Knuckles!\n");
            flag = 0;
            break;
        }
    }

    if(flag){
        printf("Different makes perfect\n");
    }

    return 0;
}