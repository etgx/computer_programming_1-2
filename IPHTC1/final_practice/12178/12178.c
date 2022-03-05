// NTHUOJ 12178 - Queens and Castles   
// Description
// Long long long long long long long long long long time ago, there's a lovely kingdom named "Chess". There's King, Queen, Knight, Castle, Bishop, ...etc. Just like the modern game "chess". 
// A king possessed one or more castles, and likewise a king could have two or more queens (same as queen, a queen is able to have two or more kings). Now in this kingdom, the king has N queens and M castles. All the castles are male, and of course, all the queens are female. 
// Moreover, the queen would eventually fall in love with castles, castles would eventually fall in love with queens, queens would eventually fall in love with other queens, castles would eventually fall in love with other castles.(This is a diversified world, BL or GL could happen.) Queens and castles concerned that if the king found betrayal by which giving a large green hat, they will not be forgiven. 
// Queens and castles assign a secret mission to you, the mightily programming knight. They'd like to figure out the possibilities that the king was unaware their relationship in the palace.
// There are N queens and M castles in the palace.
// The palace is just like a chessboard with size (N+M)*(N+M). 
// Queen can see all people in 8 directions(←, ↑, →, ↓, ↖, ↗, ↘, and ↙. Just like what queen in the chess does). If any queen see castles or other queens, the mission will fail. 
// Castle can see all people in 4 directions(←, ↑, →, and ↓. Just like what castle in the chess does). If any castle see queens or other castles, the mission will fail. 
// Find out the total amount of states that all queens and castles are placed in the palace and mission isn't fail.

// Input
// The input contains exactly two numbers N and M, each seperated by a space. 
// 1 <= N+M <= 9.

// Output
// Output only one number ── the total amount of states that queens and castles are placed in the palace and mission isn't fail.
// Remember to print a '\n' at the end of the output.

// Sample Input  
// 8 0

// Sample Output  
// 92

#include <stdio.h>
#include <stdlib.h>
#define TableMaxSize 10

int DiaDirR[4] = {1, 1, -1, -1};
int DiaDirC[4] = {1, -1, 1, -1};

int checkCol(int (*table)[TableMaxSize], const int row, const int col, const int chessNum){
    for(int i = 0; i < chessNum; i++){
        if(table[i][col]){return 1;}
    }
    return 0;
}

int checkDia(int (*table)[TableMaxSize], const int row, const int col, const int chessNum){
    int res = 0;
    for(int i = 0; i < 4; i++){ // Iterate 4 direction
        for(int j = 1; j < chessNum; j++){ // Extend Each Direction, Problem: forget to set chessNum as bound
            int r = row + j * DiaDirR[i], c = col + j * DiaDirC[i];
            if(r >= 0 && c >= 0 && r < chessNum && c < chessNum){
                int mark = table[r][c];
                if(mark == 2){return 2;}
                else if(mark == 1){res = 1;}
            }else{break;}
        }
    }
    return res;
}

int search(const int n, const int m, const int chessNum, int (*table)[TableMaxSize], const int layer){
    // Problem: forget to return 1
    if(layer >= chessNum){return 1;}
    int count = 0;
    for(int i = 0; i < chessNum; i++){
        // if(!table[layer][i]){
            int resCol = checkCol(table, layer, i, chessNum);
            int resDia = checkDia(table, layer, i, chessNum);
            // Put Castles
            table[layer][i] = 1;
            // Problem: Forget to check the number of castles
            // Problem: Misunderstand the maening of chessNum, the "chessNum" means the size of used table
            if(resCol == 0 && resDia < 2 && m > 0){count += search(n, m - 1, chessNum, table, layer + 1);}
            // Put Queens
            table[layer][i] = 2;
            // Problem: Forget to check the number of queens
            // Problem: Misunderstand the maening of chessNum, the "chessNum" means the size of used table
            if(resCol == 0 && resDia == 0 && n > 0){count += search(n - 1, m, chessNum, table, layer + 1);}
            // Reset 
            table[layer][i] = 0;
        // }
    }
    return count;
}

int main(){
    // n: Queens, m: Castles
    int n = 0, m = 0, count = 0;
    int table[TableMaxSize][TableMaxSize] = {0};

    scanf("%d %d", &n, &m);

    count = search(n, m, n + m, table, 0);

    printf("%d\n", count);


    return 0;
}