// NTHUOJ 12144 - Dark Souls   
// Description
// Dark Souls is a famous video game. The main character in Dark Souls 3 is known as
// " Ashen one ". Today you are the Ashen one.
// You are in a 5*5 room. You are at the
// position ( 1, 1 ) -- the top left corner -- and you want to reach the
// position ( 5, 5 )-- the lower right corner.
// There's no obstacle in the room but monsters. If you and the monster are at the same position, you need to fight it.
// The rule of fighting is Turn-based. You can always attack first, if the monster didn't die after your attack, then it's the monster's turn to attack you and so on. 
// There is always only two result after a fight, you died or the monster died.
// Note that once you lost your hp you can't restore it.
// Find out if you can reach the position ( 5,5 )

// Input
// input contain servel lines.
// First line contains three integers.
// The Hp, attack of Ashen one and k( 1 <= k <= 25 ) the number of monsters.
// Following k lines each lines contains four integers.
// The Hp, attack of i-th monster and the position x,y of i-th monster.
// All numbers are >= 1 and in the range of int

// Output
// If you can reach the position ( 5 ,5 ) print "HEIR OF FIRE DESTROYED"
// otherwise print "YOU DIED"
// remember to print \n at the end of output

// Sample Input  
// 100 20 5
// 41 50 5 5
// 22 24 2 4
// 30 10 1 3
// 26 25 2 5
// 28 41 1 4

// Sample Output  
// YOU DIED

// (0, 0) may occur monsters
#include<stdio.h>
#include<stdlib.h>
#define MapSize 5
#define Inf 4294967295

typedef struct monster{
    int hp;
    int attack;
    int r;
    int c;
    int isEverPass;
}Monster;

typedef struct you{
    int hp;
    int attack;
    int r;
    int c;
}You;

const int dirR[4] = {1, -1, 0, 0};
const int dirC[4] = {0, 0, 1, -1};

void showMap(int (*map)[MapSize]){
    for(int i = 0; i < MapSize; i++){
        for(int j = 0; j < MapSize; j++){
            printf("%d\t", map[i][j]);
        }
        printf("\n");
    }
}

int fight(const You you, const Monster mon){
    if(you.attack <= 0 && mon.hp > 0){
        return 0;
    }else{
        // Since the hero attack first, so the rounds that hero was attacked minus 1
        return you.hp - (((mon.hp / you.attack) + (mon.hp % you.attack > 0) - 1) * mon.attack);
        // return you - ((mon.hp / youAttack + 1) * mon.attack);
    }
}
// the following way can do the same thing as the previous function
// int fight(const You you, const Monster mon){
//     // Return HP of hero after fight with monster
//     if(you.attack <= 0 && mon.hp > 0){
//         return 0;
//     }else{
//         int tempHp = you.hp;
//         int tempMonHp = mon.hp;
//         while(tempMonHp > 0){
//             tempMonHp -= you.attack;
//             if(tempMonHp > 0){
//                 tempHp -= mon.attack;
//             }
//         }
//         return tempHp;
//     }
// }

int dfs(Monster (*mons)[MapSize], const You you){
    int isAlive = 0;
    You nowYou = you;
    if(nowYou.r >= 0 && nowYou.c >= 0 && nowYou.r < MapSize && nowYou.c < MapSize){
        if(!mons[nowYou.r][nowYou.c].isEverPass){
            nowYou.hp = fight(nowYou, mons[nowYou.r][nowYou.c]);
            if(nowYou.hp > 0){
                if(nowYou.r == 4 && nowYou.c == 4) {return 1;}

                mons[nowYou.r][nowYou.c].isEverPass = 1;
                // printf("you: HP: %d, ATK: %d, (%d, %d)\n", nowYou.hp, nowYou.attack, nowYou.r, nowYou.c);
                for(int i = 0; i < 4; i++){
                    You nextY = nowYou;
                    nextY.r += dirR[i];
                    nextY.c += dirC[i];
                    isAlive = dfs(mons, nextY);
                    if(isAlive){return 1;}
                }
                mons[nowYou.r][nowYou.c].isEverPass = 0;
            }
        }
    }
    return 0;
}

int main(){
    You y;
    Monster mons[MapSize][MapSize];
    int k = 0, isAlive = 0;

    scanf("%d %d %d\n", &(y.hp), &(y.attack), &k);
    y.r = 0;
    y.c = 0;

    for(int i = 0; i < MapSize; i++){
        for(int j = 0; j < MapSize; j++){
            mons[i][j].hp = 0;
            mons[i][j].attack = 0;
            mons[i][j].isEverPass = 0;
        }
    }

    for(int i = 0; i < k; i++){
        int hp = 0, attack = 0, r = 0, c = 0;
        scanf("%d %d %d %d\n", &hp, &attack, &r, &c);
        mons[r - 1][c - 1].hp = hp;
        mons[r - 1][c - 1].attack = attack;
        mons[r - 1][c - 1].r = r - 1;
        mons[r - 1][c - 1].c = c - 1;
    }
    // mons[0][0].isEverPass = 1;
    
    // printf("Monster HP: %d Attack: %d\n", mons[2][1].hp, mons[2][1].attack);
    isAlive = dfs(mons, y);
    // showMap(maxHpMap);

    if(isAlive){printf("HEIR OF FIRE DESTROYED\n");}
    else{printf("YOU DIED\n");}

    return 0;
}