#include<stdio.h>
#include<stdlib.h>
#define MapSize 5
#define Inf 4294967295

typedef struct monster{
    int hp;
    int attack;
    int x;
    int y;
}Monster;

typedef struct you{
    int hp;
    int attack;
}You;

void showMap(int (*map)[MapSize]){
    for(int i = 0; i < MapSize; i++){
        for(int j = 0; j < MapSize; j++){
            printf("%d\t", map[i][j]);
        }
        printf("\n");
    }
}

// int fight(const int youHp, const int youAttack, const Monster mon){
//     if(youAttack <= 0){
//         return Inf;
//     }else{
//         return youHp - (((mon.hp / youAttack) + (mon.hp % youAttack > 0) - 1) * mon.attack);
//         // return youHp - ((mon.hp / youAttack + 1) * mon.attack);
//     }
// }

int fight(const int youHp, const int youAttack, const Monster mon){
    if(youAttack <= 0){
        return Inf;
    }else{
        int tempHp = youHp;
        int tempMonHp = mon.hp;
        while(tempMonHp > 0){
            tempMonHp -= youAttack;
            if(tempMonHp > 0){
                tempHp -= mon.attack;
            }
        }
        // return youHp - (((mon.hp / youAttack) + (mon.hp % youAttack > 0) - 1) * mon.attack);
        // return youHp - ((mon.hp / youAttack + 1) * mon.attack);
        return tempHp;
    }
}

int main(){
    You y;
    Monster mons[MapSize][MapSize];
    int maxHpMap[MapSize][MapSize] = {0};
    int k = 0;

    scanf("%d %d %d\n", &(y.hp), &(y.attack), &k);
    maxHpMap[0][0] = y.hp;

    for(int i = 0; i < MapSize; i++){
        for(int j = 0; j < MapSize; j++){
            mons[i][j].hp = 0;
            mons[i][j].attack = 0;
        }
    }

    for(int i = 0; i < k; i++){
        int hp = 0, attack = 0, x = 0, y = 0;
        scanf("%d %d %d %d\n", &hp, &attack, &x, &y);
        mons[x - 1][y - 1].hp = hp;
        mons[x - 1][y - 1].attack = attack;
        mons[x - 1][y - 1].x = x - 1;
        mons[x - 1][y - 1].y = y - 1;
    }
    
    // printf("Monster HP: %d Attack: %d\n", mons[2][1].hp, mons[2][1].attack);

    for(int k = 0; k < 25; k++){
        for(int i = 0; i < MapSize; i++){
            for(int j = 0; j < MapSize; j++){
                if(maxHpMap[i][j] > 0){
                    // printf("Iterate K: %d, [%d][%d]\n", k, i, j);
                    // printf("Hero HP:%d Attack:%d\n", maxHpMap[i][j], y.attack);
                    if(i + 1 < MapSize){
                        int fightRes = fight(maxHpMap[i][j], y.attack, mons[i + 1][j]);
                        // fightRes = fightRes < 0? fightRes : fightRes;
                        // printf("Monster[%d][%d] HP: %d Attack: %d Res: %d\n", i + 1, j, mons[i + 1][j].hp, mons[i + 1][j].attack, fightRes);
                        if(fightRes > maxHpMap[i + 1][j]){
                            maxHpMap[i + 1][j] = fightRes;
                        }
                    }

                    if(i - 1 >= 0){
                        int fightRes = fight(maxHpMap[i][j], y.attack, mons[i - 1][j]);
                        // fightRes = fightRes < 0? fightRes : fightRes;
                        // printf("Monster[%d][%d] HP: %d Attack: %d Res: %d\n", i - 1, j, mons[i - 1][j].hp, mons[i - 1][j].attack, fightRes);
                        if(fightRes > maxHpMap[i - 1][j]){
                            maxHpMap[i - 1][j] = fightRes;
                        }
                    }

                    if(j + 1 < MapSize){
                        int fightRes = fight(maxHpMap[i][j], y.attack, mons[i][j + 1]);
                        // fightRes = fightRes < 0? fightRes : fightRes;
                        // printf("Monster[%d][%d] HP: %d Attack: %d Res: %d\n", i, j + 1, mons[i][j + 1].hp, mons[i][j + 1].attack, fightRes);
                        if(fightRes > maxHpMap[i][j + 1]){
                            maxHpMap[i][j + 1] = fightRes;
                        }
                    }
                    
                    if(j - 1 >= 0){
                        int fightRes = fight(maxHpMap[i][j], y.attack, mons[i][j - 1]);
                        // fightRes = fightRes < 0? fightRes : fightRes;
                        // printf("Monster[%d][%d] HP: %d Attack: %d Res: %d\n", i, j - 1, mons[i][j - 1].hp, mons[i][j - 1].attack, fightRes);
                        if(fightRes > maxHpMap[i][j - 1]){
                            maxHpMap[i][j - 1] = fightRes;
                        }
                    }
                }
            }
        }
    }

    showMap(maxHpMap);

    if(maxHpMap[4][4] > 0){printf("HEIR OF FIRE DESTROYED\n");}
    else{printf("YOU DIED\n");}

    return 0;
}