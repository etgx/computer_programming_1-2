// NTHUOJ 12674 - Eat candies
// Description
// You have three different kinds of candies: color red, color green, color blue.
// You got three number r, g, b which means the number of candies for each color.
// You need to eat exactly two candies each day.
// The candies you eat have to be different colors.
// Your goal is to find out what's the maximum days that you can eat the candies that qualified for the rules above.
// Example:
// if r = 7, g = 4, b = 10
// You can eat green and blue for 4 days, then you got r = 7, g = 0, b = 6.
// Then you can eat red and blue for 6 days, then you got r = 1, g = 0, b = 0.
// There's only one red left, you can't have two candies anymore.
// The answer will be 10 days.

// Input
// The input first contains one integer t( 1 <= t <= 10^6) which means the number of testcases.
// The following t lines each line contains three integer r, g, b(0 <= r, g, b <= 10^8)

// Output
// For each testcase print a integer which means the maximum days that you can eat the candies.
// Remember to print \n at the end of each output.

// Sample Input  
// 6
// 1 1 1
// 1 2 1
// 4 1 1
// 7 4 10
// 8 1 4
// 8 2 8

// Sample Output  
// 1
// 2
// 2
// 10
// 5
// 9

// SYC
// 2020 / 4 / 13

#include<stdlib.h>
#include<stdio.h>

int *triSort(int a, int b, int c){
    int *re = (int *)malloc(sizeof(int) * 3);

    if(a >= b){
        if(b >= c){
            re[0] = a;
            re[1] = b;
            re[2] = c;
            return re;
        }else{
            if(a >= c){
                // re = {a, c, b};
                re[0] = a;
                re[1] = c;
                re[2] = b;
                return re;
            }else{
                // int re[3] = {c, a, b};
                re[0] = c;
                re[1] = a;
                re[2] = b;
                return re;
            }
        }
    }else{
        if(a >= c){
            // int re[3] = {b, a, c};
            re[0] = b;
            re[1] = a;
            re[2] = c;
            return re;
        }else{
            if(b >= c){
                // int re[3] = {b, c, a};
                re[0] = b;
                re[1] = c;
                re[2] = a;
                return re;
            }else{
                // int re[3] = {c, b, a};
                re[0] = c;
                re[1] = b;
                re[2] = a;
                return re;
            }
        }
    }
}

int main(){
    int max = 0;
    int min = 0;
    int middle = 0;

    int n = 0;

    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        int a = 0;
        int b = 0;
        int c = 0;

        scanf("%d", &a);
        scanf("%d", &b);
        scanf("%d", &c);

        int *sorted = triSort(a, b, c);

        max = sorted[0];
        middle = sorted[1];
        min = sorted[2];

        if(middle + min >= max){
            printf("%d\n", (max + middle + min) / 2);
        }else{
            printf("%d\n", middle + min);
        }
    }

    return 0;
}