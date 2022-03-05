// NTHUOJ 12151 - Johnny's sugar   
// Description
// Johnny just got a lot of sugar from his PaPa!
// However, Johnny is too excited that he accidently fall and all of the sugar just fall onto the ground. 
// PaPa is angry, and asked Johnny to clean the room up and take all his sugar away. 
// After Johnny's begging, PaPa thought of a problem. If Johnny could solve it, PaPa may just forgive him.
// The sugar now seperated on the ground. The ground is a 2D coordinate with n * n slots, each slot has several pieces of sugar. PaPa will give Johnny the number of pieces of sugar in each slot. Johnny needs to answer the maximum number of every row and the minimum number of every column, otherwise, he will be punished!
// Johnny is a bad boy, he command you to help him, and if you do it well, he will not give you any sugar, but you'll receive an AC.

// Input
// The first line contains only one integer that indicates the number n.
// The next n lines, each line contains n non-negitive integers, PaPa will give you the number of pieces of sugar in each slot.
// 1 <= n <=1000, each piece of sugar will not excceed 50000. 

// Output
// The first line, output the maximum number of each row. There should be n numbers.
// The second line, output the minimum number of each column. There should be n numbers, too.
// There should be a space next to each number except the last number, which means there should be no space at the end of each line.
// Remember to output a '\n' at the end of the output. 

// Sample Input  
// 4
// 1 14 11 16
// 9 10 3 12
// 13 6 15 8
// 13 2 7 4

// Sample Output  
// 16 12 15 13
// 1 2 3 4

// 2020/05/09 SYC

#include<stdlib.h>
#include<stdio.h>

int map[1050][1050] = {0};

int main(){
    int n = 0;
    scanf("%d", &n);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d", &(map[i][j]));
        }
    }

    for(int i = 0; i < n; i++){
        int max = 0;
        for(int j = 0; j < n; j++){
            if(max < map[i][j]){
                max = map[i][j];
            }
        }

        if(i < n - 1){
            printf("%d ", max);
        }else{
            printf("%d\n", max);
        }
    }

    for(int i = 0; i < n; i++){
        int min = 100000;
        for(int j = 0; j < n; j++){
            if(min > map[j][i]){
                min = map[j][i];
            }
        }

        if(i < n - 1){
            printf("%d ", min);
        }else{
            printf("%d\n", min);
        }
    }

    return 0;
}