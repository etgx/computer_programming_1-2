// Another AC Version
#include <stdio.h>
#include <stdlib.h>
#define MaxTableSize 10

void showTable(int chessNum, int (*table)[MaxTableSize]){
    printf("\n=====================================\n");
    for(int i = 0; i < chessNum; i++){
        for(int j = 0; j < chessNum; j++){
            printf("%d ", table[i][j]);
        }
        printf("\n");
    }
    printf("\n=====================================\n");
}

int checkCol(const int idx, const int chessNum, int (*table)[MaxTableSize]){
    for(int i = 0; i < chessNum; i++){
        if(table[i][idx]){return 0;}
    }

    return 1;
}

int checkDia(const int row, const int col, const int chessNum, int (*table)[MaxTableSize]){
    int res = 0;
    // Return 0: Means no castle or queens
    //        1: Means no queens
    //        2: Means exist queens

    // row++ && col++, bottom right direction
    for(int i = row + 1, j = col + 1; i < chessNum && j < chessNum; i++, j++){
        if(table[i][j] == 2){
            return 2;
        }else if(table[i][j] == 1){
            res = 1;
        }
    }

    // row-- && col--, upper left direction
    for(int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--){
        if(table[i][j] == 2){
            return 2;
        }else if(table[i][j] == 1){
            res = 1;
        }
    }

    // row++ && col--, bottom left direction
    for(int i = row + 1, j = col - 1; i < chessNum && j >= 0; i++, j--){
        if(table[i][j] == 2){
            return 2;
        }else if(table[i][j] == 1){
            res = 1;
        }
    }

    // row-- && col++, upper right direction
    for(int i = row - 1, j = col + 1; i >= 0 && j < chessNum; i--, j++){
        if(table[i][j] == 2){
            return 2;
        }else if(table[i][j] == 1){
            res = 1;
        }
    }

    return res;
}

int search(const int n, const int m, const int chessNum, int (*table)[MaxTableSize], const int layer){
    // printf("n: %d m: %d chessNum: %d layer: %d", n, m, chessNum, layer);
    if(layer >= chessNum){
        // showTable(chessNum, table);
        return 1;
    }

    int count = 0;
    
    for(int i = 0; i < chessNum; i++){
        if((!table[layer][i]) && checkCol(i, chessNum, table)){
            // printf("Pass checkCol\n");
            int checkDiaRes = checkDia(layer, i, chessNum, table);
            table[layer][i] = 1;

            // Iterate Castles (m)
            if(m > 0 && checkDiaRes < 2){count += search(n, m - 1, chessNum, table, layer + 1);}
            
            // Iterate Queens (n)
            if(checkDiaRes == 0 && n > 0){
                // printf("Pass checkDia\n");
                table[layer][i] = 2;
                count += search(n - 1, m, chessNum, table, layer + 1);
            }
            table[layer][i] = 0;
        }
    }

    return count;
}

int main(){
    // n Queens, m Castles
    int n = 0, m = 0, count = 0;
    int table[MaxTableSize][MaxTableSize] = {0};

    scanf("%d %d\n", &n, &m);
    
    count = search(n, m, n + m, table, 0);

    printf("%d\n", count);

    return 0;
}