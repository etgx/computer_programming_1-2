// I2P - Kuo Week0 Problem 7 | NTHUOJ 12615 - Knight Search
// Description
// Problem adapted from ICPC SG Preliminary Contest 2018
// Author of original problem : Steven Halim
// Licence : cc-by-sa
// Test case is regenerated in this problem
// Alice is a chess knight living in Chessland (an N x N board). The cells in Chessland are numbered from 1 to N^2 in row major order. Each cell has an UPPERCASE alphabet character assigned to it. The Chessland is described by a string S of length N^2 (in row major order). For example for N=5 and S = "IXIXXXXCXAXSXXPXXCSXAGXXX", the Chessland that Alice lives in looks like this:
//    12345
//    -----
//  1|IXIXX
//  2|XXCXA
//  3|XSXXP
//  4|XXCSX
//  5|AGXXX
// As Alice is a chess knight, she can only move from cell (a,b) to cell (c,d) in Chessland if and only if (a−c)^2+(b−d)^2=5. Alice wonder if she can find her favorite string "ICPCASIASG" in Chessland by starting from a cell with character 'I' and finds the other 9 characters by jumping around in Chessland using chess knight movements. Alice can visit the same cell more than once.
// You are of course Bob the computing bee and your job is to help her decide the answer.

// Input
// The first line of input consists of 1 integer: N (1≤N≤100). The second line contains a string S of N^2 UPPERCASE characters ['A'..'Z'] that describe Chessland.

// Output
// Print "YES" if Alice can find string "ICPCASIASG" in Chessland or print "NO" otherwise.

// Sample Input  

// # Sample Input 1

// 5
// IXIXXXXCXAXSXXPXXCSXAGXXX

// # Sample Input 2

// 5
// THEQUICKBROWNFOXJUMPSOVER

// Sample Output  

// # Sample Output 1

// YES

// # Sample Output 2

// NO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TARGET_STR "ICPCASIASG"
#define TARGET_STR_LEN strlen(TARGET_STR)
#define KNIGHT_DIR_CASE 8
const int KNIGHT_DIR_ROW[KNIGHT_DIR_CASE] = {1, 2, -1, 2, 1, -2, -1, -2};
const int KNIGHT_DIR_COL[KNIGHT_DIR_CASE] = {2, 1, 2, -1, -2, 1, -2, -1};

void show(char **chessland, int N){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            printf("%c", chessland[i][j]);
        }
        printf("\n");
    }
}

int find_target_char_by_idx(char **chessland, int N, int row, int col, int idx){
    if(idx >= TARGET_STR_LEN){return 1;}

    int count = 0;
    for(int i = 0; i < KNIGHT_DIR_CASE; i++){
        int next_row = row + KNIGHT_DIR_ROW[i], next_col = col + KNIGHT_DIR_COL[i];
        if(next_row >= 0 && next_row < N && next_col >= 0 && next_col < N){
            // printf("[%d, %d]: %c + (%d, %d) = (%d, %d): %c\n", row, col, chessland[row][col], row, col, next_row, next_col, chessland[next_row][next_col]);
            if(chessland[next_row][next_col] == TARGET_STR[idx]){
                count += find_target_char_by_idx(chessland, N, next_row, next_col, idx + 1);
            }
        }
    }
    return count;
}

int find_target_str(char **chessland, int N){
    int count = 0;
    for(int r = 0; r < N; r++){
        for(int c = 0; c < N; c++){
            if(chessland[r][c] == TARGET_STR[0]){
                // printf("[%d, %d]: %c\n", r, c, chessland[r][c]);
                count += find_target_char_by_idx(chessland, N, r, c, 1);
            }
        }
    }
    return count;
}

int main(){
    int N = 0;
    scanf("%d\n", &N);
    int chessland_row_bytes = sizeof(char*) * N, chessland_col_bytes = sizeof(char) * N;
    
    char **chessland = (char**)malloc(chessland_row_bytes);
    memset(chessland, 0, chessland_row_bytes);
    for(int i = 0; i < N; i++){
        chessland[i] = (char*)malloc(chessland_col_bytes);
        memset(chessland[i], 0, chessland_col_bytes);
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            scanf("%c", &(chessland[i][j]));
        }
    }
    // show(chessland, N);

    int str_count = find_target_str(chessland, N);
    if(str_count){
        printf("YES\n");
    }else{
        printf("NO\n");
    }

    return 0;
}