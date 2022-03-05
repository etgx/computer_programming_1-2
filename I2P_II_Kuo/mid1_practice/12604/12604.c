// I2P - Kuo Week0 Problem 3 | NTHUOJ 12604 - N-Queens M-Rooks Problem   
// Description
// N queens problem asks how many ways to place N non-attacking queens on an N×N chessboard.
// For example, there’re 2 solutions for N = 4:
// ( 0 means empty spot, Q means queen. )

// 0 Q 0 0     0 0 Q 0
// 0 0 0 Q     Q 0 0 0
// Q 0 0 0     0 0 0 Q
// 0 0 Q 0     0 Q 0 0

// While, there’s no solution for N = 2:
// Below is the all placements. All of them contains queens threaten each other.

// Q Q    Q 0    Q 0    0 Q    0 Q    0 0
// 0 0    Q 0    0 Q    Q 0    0 Q    Q Q

// Let’s define a new problem “N-Queens M-Rooks Problem”.
// It asks how many ways to place N queens and M rooks on an (N+M)×(N+M)( chessboard such that no two of queens or rooks can attack each other in 1 step.
// For N = 1, M = 2, there’re 4 solutions:
// ( 0 means empty spot, Q means queen, R means rook. )

// Q 0 0    0 R 0
// 0 0 R    R 0 0
// 0 R 0    0 0 Q

// 0 R 0    0 0 Q
// 0 0 R    R 0 0
// Q 0 0    0 R 0

// Possible move of Queen:
// Possible move of Rook:


// Input

// There’re multiple testcases.
// Each testcase is consisted of 2 integers N,M on one line.
// It’s guaranteed that:
// 0 ≤ N, M ≤ 9
// 1 ≤ N+M ≤ 9

// Output
// Print the number of solution for N-Queens M-Rooks Problem for every testcase.
// Remember ‘\n’ on the end of line.

// Sample Input  

// 0 5
// 5 0
// 1 2

// Sample Output  

// 120
// 10
// 4

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum Type{Queen, Rook};

typedef struct spot{
    int row, col, type;
}Spot;

const Spot Dummy = {-1, -1, -1};

void show(Spot *chesses, int n, int size){
    printf("---------------\n");
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            int is_printed = 0;
            for(int k = 0; k < n; k++){
                if(chesses[k].row == i && chesses[k].col == j && chesses[k].type == Queen){
                    is_printed = 1;
                    printf("Q");
                }else if(chesses[k].row == i && chesses[k].col == j && chesses[k].type == Rook){
                    is_printed = 1;
                    printf("R");
                }
            }
            if(!is_printed){
                printf("X");
            }
        }
        printf("\n");
    }
    printf("---------------\n");
}

int check_valid(Spot a, Spot b){
    if(a.row == b.row || a.col == b.col){
        // printf("Vertical Conflict\n");
        return 0;
    }else{
        if(a.type == Queen || b.type == Queen){
            if((a.row - b.row) == (a.col - b.col) || (a.row - b.row) == -(a.col - b.col)){
                // printf("q: %lf = Row: (%d - %d) / Col: (%d - %d) - Diagonal Conflict\n", q, a.row, b.row, a.col, b.col);
                return 0;
            }
        }
    }
    return 1;
}

int check_chesses(Spot* chesses, int n, Spot chess){
    for(int i = 0; i < n; i++){
        if(!check_valid(chesses[i], chess)){
            // printf("Chess[%d]: (%d, %d) conflict with (%d, %d)\n", i, chesses[i].row, chesses[i].col, chess.row, chess.col);
            return 0;
        }
    }
    return 1;
}

int count_possible(int N, int M, int remain_queen, int remain_rook, int depth){
    int size = N + M, counter = 0;
    // Init
    static Spot *chesses;
    if(depth == 0){
        chesses = (Spot*)malloc(sizeof(Spot) * size);
    }

    if(depth >= size){
        // show(chesses, size, size);
        return 1;
    }

    if(remain_queen > 0){
        for(int i = 0; i < size; i++){
            Spot c = {depth, i, Queen};
            // printf("Next Queen R: %d, C: %d\n", depth, i);
            // show(chesses, size, size);
            if(check_chesses(chesses, depth, c)){
                // printf("Feasible\n==========\n");
                chesses[depth] = c;
                counter += count_possible(N, M, remain_queen - 1, remain_rook, depth + 1);
            }
            chesses[depth] = Dummy;
        }
    }

    if(remain_rook > 0){
        for(int i = 0; i < size; i++){
            Spot c = {depth, i, Rook};
            if(check_chesses(chesses, depth, c)){
                chesses[depth] = c;
                counter += count_possible(N, M, remain_queen, remain_rook - 1, depth + 1);
            }
        }
    }

    // End
    if(depth == 0){
        free(chesses);
        chesses = NULL;
    }    
    return counter;
}

int main(){
    int N = 0, M = 0;
    while(scanf("%d %d", &N, &M) != EOF){
        // printf("N: %d | M: %d\n", N, M);
        int count = count_possible(N, M, N, M, 0);
        printf("%d\n", count);
    }
    return 0;
}