// NTHUOJ 11691 - pC - Ponds   
// Description
// Writer: jjjjj19980806       Description: pclightyear       Difficulty: ★★☆☆☆
// Frank Lin likes to go mountain climbing. Every time before he goes mountain climbing, he needs to look up the map to plan for the route. According to Frank’s experience, it is very important to locate the position of ponds, since it is usually the best place for resting. Now, Frank gives you a map sized m ✕ n consists of only two symbols '~' and '.', representing water and land, respectively. Frank wonders how many ponds (consecutive position of water) are there on the map.
// If you can help Frank solve this problem, maybe he will teach you how to build a tent within five minutes.

// Input
// The first line contains two integers m, n, representing the size of the map Frank gives to you.
// The next m lines contain n characters, either '~' or '.', representing the status of position aij.
// It is guaranteed that :
// 1 ≤ m, n ≤ 1000

// Output
// Please output the number of ponds on the map.

// Sample Input  
// 2 3
// ~.~
// ~..

// Sample Output  
// 2

// 2020/05/08 SYC

#include<stdio.h>
#include<stdlib.h>

int map[1050][1050] = {0};

int dfs(int row, int col, int m, int n, int count){
    if(map[row][col] == -1){
        // printf("%d %d\n", row, col);
        map[row][col] = count;
    }else{
        return 0;
    }

    if(row < m - 1 && map[row + 1][col] == -1){dfs(row + 1, col, m , n, count);}
    if(row > 0 && map[row - 1][col] == -1){dfs(row - 1, col, m , n, count);}
    if(col < n - 1 && map[row][col + 1] == -1){dfs(row, col + 1, m , n, count);}
    if(col > 0 && map[row ][col- 1] == -1){dfs(row, col - 1, m , n, count);}

    return 1;
}


int main(){
    int m = 0, n = 0;
    int count = 1;
    
    
    scanf("%d %d\n", &m, &n);

    for(int i = 0; i < m; i++){
        char buff[1050] = {0};
        scanf("%s", buff);

        for(int j = 0; j < n; j++){
            if(buff[j] == '~'){
                map[i][j] = -1;
            }   
        }
    }

    // printf("HI\n");
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            // printf("HI\n");
            if(dfs(i, j, m, n, count)){
                // printf("%d\n", count);
                count++;

            }
        }
    }

    printf("%d\n", count - 1);

    return 0;
}