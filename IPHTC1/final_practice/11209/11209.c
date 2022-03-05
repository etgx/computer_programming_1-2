// NTHUOJ 11209 - N queens   
// Description
// You have to place N queens on a NxN chessboard in such a way that no queen threatens another one
// The rule is that each row and column of the board contains exactly 1 queen , and each diagonal contains no more than 1 queen.
// Your mission is to compute how many possible ways to place N queens on that chessboard.

// Input
// An integer N which represent the size of chessboard and the number of queens.
// where 1<=N<=10

// Output
// An integer which represent the number of possible distributions of  N queens.
// There is no need to add '\n' at the end of output

// Sample Input  
// 8

// Sample Output  
// 92

// 2020/05/05 SYC

#include<stdio.h>
#include<stdlib.h>

#define MaxLen 12

int solveQueens(int N, int layer, int *cols, int *topRight2BottomLeft, int *topLeft2BottomRight){
    if(layer >= N){
        return 1;
    }else{
        int count = 0;
        for(int i = 0; i < N; i++){
            if(cols[i] == 0 && topRight2BottomLeft[layer + i] == 0 && topLeft2BottomRight[layer - i + N] == 0){
                // printf("%d\n", i);
                cols[i] = 1;
                topRight2BottomLeft[layer + i] = 1;
                topLeft2BottomRight[layer - i + N] = 1;
                count += solveQueens(N, layer + 1, cols, topRight2BottomLeft, topLeft2BottomRight);
                cols[i] = 0;
                topRight2BottomLeft[layer + i] = 0;
                topLeft2BottomRight[layer - i + N] = 0;
                // printf("Count %d\n", count);
            }
        }

        return count;
    }

    
}

int main(){
    int N = 0;
    int cols[MaxLen] = {0}, topRight2BottomLeft[2 * MaxLen] = {0}, topLeft2BottomRight[2 * MaxLen] = {0};
    scanf("%d", &N);
    printf("%d", solveQueens(N, 0, cols, topRight2BottomLeft, topLeft2BottomRight));

    return 0;
}