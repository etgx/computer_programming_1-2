// NTHUOJ 11620 pD - Distrait   
// Description
// Eccioa's Japanese teacher sometimes plays Bingo with students in the class. Students will be asked to randomly fill 1~25 in a 5*5 card. Then the teacher asks each of the students to choose a number one by one. The first few students who find the selected numbers are arranged on their card in a row, a column or a diagnose can get snacks that the teacher brought back from Japan as a reward.
// One day, the teacher started to play Bingo again. But Eccioa zoned out for a minute. When he woke up, there were already N numbers being selected. He wondered if he gets the reward. If so, when did he win?

// Input
// First 5 lines describe the card. Each line contains 5 integers between 1 and 25.
// ( We guarantee that all 25 numbers are distinct. )
// Next line contains an integer T ( 1 <= T <= 100 ), number of testcases.
// Following are T testcases, and each of them contains 2 lines.
// The first line of each testcase contains an integer N ( 1 <= N <= 25 ), number of selected numbers.
// The second line contains N distinct selected numbers, from 1-st to N-th.

// Output
// For each testcase, print out an integer x, telling eccioa he can get the reward at x-th number, with x as small as possible. If he couldn't, tell him that he did not get the reward yet.
// See Sample Output for more information about output format.

// Sample Input  
// 1 2 3 4 5
// 16 17 18 19 6
// 15 24 25 20 7
// 14 23 22 21 8
// 13 12 11 10 9
// 2
// 7
// 1 3 5 7 9 2 4
// 4
// 9 4 8 7

// Sample Output  
// Case #1: 7
// Case #2: Not yet \(^o^)/

// 2020/05/01 SYC

#include<stdio.h>
#include<stdlib.h>

#define TableLen 5
#define TableSize 25

typedef struct coord{
    int row;
    int col;
} Coord;

Coord table[TableSize];
int marked[TableLen][TableLen];

int isBingo(){
    // Check Rows
    // for(int i = 0; i < len; i++){
    //     int isBingoYet = 1;
    //     for(int j = 0; j < len; j++){
    //         if(!marked[i][j]){isBingoYet = 0; break;}
    //     }
    //     if(isBingoYet){
    //         return 1;
    //     }
    // }

    // // Check Columns
    // for(int i = 0; i < len; i++){
    //     int isBingoYet = 1;
    //     for(int j = 0; j < len; j++){
    //         if(!marked[j][i]){isBingoYet = 0; break;}
    //     }
    //     if(isBingoYet){
    //         return 1;
    //     }
    // }

    // Check Rows
    if(marked[0][0] && marked[0][1] && marked[0][2] && marked[0][3] && marked[0][4]){return 1;}
    if(marked[1][0] && marked[1][1] && marked[1][2] && marked[1][3] && marked[1][4]){return 1;}
    if(marked[2][0] && marked[2][1] && marked[2][2] && marked[2][3] && marked[2][4]){return 1;}
    if(marked[3][0] && marked[3][1] && marked[3][2] && marked[3][3] && marked[3][4]){return 1;}
    if(marked[4][0] && marked[4][1] && marked[4][2] && marked[4][3] && marked[4][4]){return 1;}

    // Check Columns
    if(marked[0][0] && marked[1][0] && marked[2][0] && marked[3][0] && marked[4][0]){return 1;}
    if(marked[0][1] && marked[1][1] && marked[2][1] && marked[3][1] && marked[4][1]){return 1;}
    if(marked[0][2] && marked[1][2] && marked[2][2] && marked[3][2] && marked[4][2]){return 1;}
    if(marked[0][3] && marked[1][3] && marked[2][3] && marked[3][3] && marked[4][3]){return 1;}
    if(marked[0][4] && marked[1][4] && marked[2][4] && marked[3][4] && marked[4][4]){return 1;}

    // Check Diagonoses
    if(marked[0][0] && marked[1][1] && marked[2][2] && marked[3][3] && marked[4][4]){
        return 1;
    }
    if(marked[0][4] && marked[1][3] && marked[2][2] && marked[3][1] && marked[4][0]){return 1;}

    return 0;
}

void clearMarked(){
    for(int i = 0; i < TableLen; i++){
        for(int j = 0; j < TableLen; j++){
            marked[i][j] = 0;
        }
    }
}

int main(){
    int T = 0;
    // Coord table[25];
    // int marked[5][5];

    for(int i = 0; i < TableLen; i++){
        for(int j = 0; j < TableLen; j++){
            int temp = 0;
            scanf("%d", &temp);
            table[temp].row = i;
            table[temp].col = j;
            marked[i][j] = 0;
        }
    }

    scanf("%d", &T);
    for(int i = 0; i < T; i++){
        int N = 0;
        scanf("%d", &N);

        int flag = 0;
        for(int k = 0; k < N; k++){
            int temp = 0;
            scanf("%d", &temp);

            if(!flag){
                marked[table[temp].row][table[temp].col] = 1;
                flag = isBingo();
                if(flag){
                    printf("Case #%d: %d\n", i + 1, k + 1);
                }
            }
        }
        if(!flag){
            printf("Case #%d: Not yet \\(^o^)/\n", i + 1);
        }
        clearMarked();
    }

    return 0;
}
