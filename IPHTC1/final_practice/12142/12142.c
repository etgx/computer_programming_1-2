// NTHUOJ 12142 - Ugandan Knuckles's adventure   
// Description
// After Knuckles escaped from the dungeon he faced on another difficulty. He meet an elder who claimed that he knew where to find the queen. As long as Knuckles solve the question.
// The elder will give Knuckles n integers, and Knuckles can make a big integer by appending those integers after one another. 
// For example:
// If n = 3, Knuckles have three integers: "71", "87", "22". Following integers can be made:
// "718722", "227187", "877122", "228771".......
// In this example, 6 such integers can be made. Knuckles  need to find the biggest integer.  In this example, the answer will be "877122".
// Help Knuckles find the biggest integer he can make.

// Input
// The input will end by EOF.
// Each input contains several lines.
// First line contains an integer n(1 <= n <= 100).
// The following n lines, each line contains an interger ai(1 <= ai <=10999)
// Each testcase contains at most 10 input.

// Output
// For each input, print the biggest integer you can make
// remember to print \n after each output

// Sample Input  
// 4
// 3115
// 13521
// 30747
// 4856
// 3
// 71
// 87
// 22
// 5
// 21078
// 18680
// 4115
// 13485
// 10319

// Sample Output  
// 485631153074713521
// 877122
// 411521078186801348510319

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define IntSize 1005
#define DoubleIntSize 2010
#define ArraySize 105

int cmp(const char *a, const char *b){
    char combineA[DoubleIntSize] = {'0'};
    char combineB[DoubleIntSize] = {'0'};
    
    memcpy(combineA, b, IntSize);
    memcpy(combineB, a, IntSize);
    strcat(combineA, a);
    strcat(combineB, b);

    return strcmp(combineA, combineB);
}

int main(){
    int n = 0;

    while(scanf("%d", &n) != EOF){
        char array[ArraySize][IntSize] = {'0'};
        // printf("%d Integers\n", n);
        for(int i = 0; i < n; i++){
            scanf("%s", array[i]);
            // printf("%s\n", array[i]);
        }

        qsort(array, ArraySize, IntSize, (int (*)(const void *, const void *))cmp);

        for(int i = 0; i < n; i++){
            for(int j = 0; array[i][j] != '\0'; j++){
                printf("%c", array[i][j]);
            }
        }
        printf("\n");
    }

    return 0;
}
