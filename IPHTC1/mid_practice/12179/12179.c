// NTHUOJ 12179 - Queens   
// Description
// Long long long long long long long long long long time ago, there's a lovely kingdom named "Chess". There's King, Queen, Knight, Castle, Bishop, ...etc. Just like the modern game "chess". 
// A king definitely have not only one castle or knight. But no one says that a king shouldn't have two or more queens (same as queen, a queen is able to have two or more kings). Now in this kingdom, the king has N queens. 
// However, all the queens want to get the title "King's favorite", if one is uglier than the other one (which is judged by the king), then just win by manner. If one is more rude than the other one, then just win by skills. But if a queen loses on everything...... then just let them disappear or die "accidentally"...HEHEHE..... The king soon realized that, for the safety of all of his lovely queens, he must make them cannot see each other. 
// Now, the king ask you, the mighty programming knight, for a mission. They want to find out how many possibilities that the queens won't launch a war in the palace.
// There are N queens in the palace.
// The palace is just like a chessboard with size N*N. 
// Queen can see all people in 8 directions(←, ↑, →, ↓, ↖, ↗, ↘, and ↙. Just like what queen in the chess does). If any queen see other queens, the mission will fail. 
// Find out the total amount of states that all queens are placed in the palace and mission isn't fail.
// Warning! Do not just look up the answer table! You are supposed to solve this problem by recursive. Otherwise you will regret it!

// Input
// The input contains exactly one number N. 
// 1 <= N <= 14.

// Output
// Output only one number ── the total amount of states that queens are placed in the palace and mission isn't failed.
// Remember to print a '\n' at the end of the output.

// Sample Input  
// 8

// Sample Output  
// 92

// 2020/05/01 SYC

#include<stdio.h>
#include<stdlib.h>

#define QueensMax 16

int isAvailable(int layer, int col, int queensNum, int *cols, int *upperRight2BottomLeft, int *upperLeft2BottomRight){
    return ((!cols[layer]) && (!upperRight2BottomLeft[layer + col]) && (!upperLeft2BottomRight[layer - col + queensNum]))? 1 : 0;
}

int solveQueens(int layer, int queensNum, int *cols, int *upperRight2BottomLeft, int *upperLeft2BottomRight){
    if(layer > queensNum){
        return 1;
    }else{
        int solutions = 0;
        for(int i = 1; i <= queensNum; i++){
            // if(isAvailable(layer, i, queensNum, cols, upperRight2BottomLeft, upperLeft2BottomRight)){
            if((!cols[i]) && (!upperRight2BottomLeft[layer + i]) && (!upperLeft2BottomRight[layer - i + queensNum])){
                cols[i] = 1;
                upperRight2BottomLeft[layer + i] = 1;
                upperLeft2BottomRight[layer - i + queensNum] = 1;
                solutions += solveQueens(layer + 1, queensNum, cols, upperRight2BottomLeft, upperLeft2BottomRight);
                cols[i] = 0;
                upperRight2BottomLeft[layer + i] = 0;
                upperLeft2BottomRight[layer - i + queensNum] = 0;
            }
        }
        return solutions;
    }
}

int main(){
    int N = 0;
    int cols[QueensMax] = {0};
    int upperRight2BottomLeft[2 * QueensMax] = {0};
    int upperLeft2BottomRight[2 * QueensMax] = {0};
    int layer = 1;
    
    scanf("%d", &N);

    int solutions = solveQueens(layer, N, cols, upperRight2BottomLeft, upperLeft2BottomRight);
    printf("%d\n", solutions);
    return 0;
}