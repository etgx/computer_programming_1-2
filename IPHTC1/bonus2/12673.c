// NTHUOJ 12673 - Guard The Wall   
// Description
// I shall take no wife, hold no lands, father no children.
// ~ by anonymous loser.
// The night's watch needs to guard The Wall.
// But they're lack of resource. They can only choose q-2 men from q men to guard The Wall.
// Help them find the maximum number of section they can protect.
// There're n sections in a line numbered from 1 to n.
// There're q soldiers, for i-th soldier, he can guard from section L_i to R_i(1 <= i <= q)
// A section is guarded if at least one soldier guard the section.
// You can only hire q-2 soldiers.
// You need to find the maximum number of sections that can be guarded by hiring q-2 soldiers from q soldiers.

// Example
// If you got n = 4 sections and q = 3 soldiers.
// First soldier guard L_1 = 1, R_1 = 1.
// Second soldier guard L_2 = 2, R_2 = 2.
// Third soldier guard L_3 = 3, R_3 = 4.
// You can hire q-2 = 1 soldier.
// The best solution is hired the third soldier then you got 2 section guarded.
// The answer will be 2.

// Input
// The input first contains one integer t( 1 <= t <= 5) which means the number of testcases.
// Each testcase first contains two numbers n, q(3 <= n, q <= 5000).
// Then the following q lines, each line contains two integer L_i, R_i( 1<= L_i <= R_i <= n )

// Output
// For each testcase print a integer which means the maximum number of sections that can be guarded by hiring q-2 soldiers.
// Remember to print \n at the end of each output.

// Sample Input  
// 3
// 7 5
// 1 4
// 4 5
// 5 6
// 6 7
// 3 5
// 4 3
// 1 1
// 2 2
// 3 4
// 4 4
// 1 1
// 2 2
// 2 3
// 3 4

// Sample Output  
// 7
// 2
// 3

// 2020/05/03 SYC

#include<stdio.h>
#include<stdlib.h>

typedef struct soldier{
    int l;
    int r;
    int len;
} Soldier;

int main(){
    int t = 0;
    scanf("%d", &t);

    for(int i = 0; i < t; i++){
        int n = 0, q = 0;
        Soldier soldierBuff[6000];
        int sections[6000] = {0};
        int weak1stSoldierIdx = 0;
        int weak2ndSoldierIdx = 0;
        int record1st = 99999;
        int record2nd = 99999;
        int guarded = 0;
        scanf("%d %d", &n, &q);

        for(int j = 0; j < q; j++){
            scanf("%d %d", &(soldierBuff[j].l), &(soldierBuff[j].r));

            soldierBuff[j].len = soldierBuff[j].r - soldierBuff[j].l + 1;
            for(int k = soldierBuff[j].l; k <= soldierBuff[j].r; k++){
                sections[k]++;
            }
        }

        for(int j = 0; j < q; j++){ // Iterate Each Soldier to Find Weakest 1st
            int numberOfOnlyGuard = 0;
            for(int k = soldierBuff[j].l; k <= soldierBuff[j].r; k++){
                if(sections[k] == 1){numberOfOnlyGuard++;}
            }
            if(record1st > numberOfOnlyGuard){
                record1st = numberOfOnlyGuard;
                weak1stSoldierIdx = j;
            }
        }

        // Elimenate Record1st
        for(int k = soldierBuff[weak1stSoldierIdx].l; k <= soldierBuff[weak1stSoldierIdx].r; k++){
            sections[k]--;
        }

        for(int j = 0; j < q; j++){ // Iterate Each Soldier to Find Weakest 2nd
            if(j != weak1stSoldierIdx){
                int numberOfOnlyGuard = 0;
                for(int k = soldierBuff[j].l; k <= soldierBuff[j].r; k++){
                    if(sections[k] == 1){numberOfOnlyGuard++;}
                }
                if(record2nd > numberOfOnlyGuard){
                    record2nd = numberOfOnlyGuard;
                    weak2ndSoldierIdx = j;
                }
            }
        }

        // Elimenate Record2nd
        for(int k = soldierBuff[weak2ndSoldierIdx].l; k <= soldierBuff[weak2ndSoldierIdx].r; k++){
            sections[k]--;
        }

        for(int j = 1; j <= n; j++){
            if(sections[j]){guarded++;}
        }

        printf("%d\n", guarded);
    }

    return 0;
}