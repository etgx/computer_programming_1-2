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
