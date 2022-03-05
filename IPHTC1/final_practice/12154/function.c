// NTHUOJ 12154 - You shall not pass!   
// Description
// Attention: This problem uses partial judge to judge your answer!

// One day, Knuckles is on his way for finding his queen. He encounters an old wizard, murmuring "You shall not....You shall not....". Knuckles decides to ignore the crazy wizard and continues his journey. Suddenly, that old crazy wizard blocks his way and says "YOU SHALL NOT PASS!!!"
// The wizard, who is actually the legendary wizard Gandalf, is guarding this path. But Knuckles dones't care much. What he only cares is that the old man just blocks his way to his queen, which makes him very mad, and launches a duel to Gandalf.
// This is a real man duel for spitter to wizard, sputum to magic spell, mysterious creature to man, legend to legend, a duel that whoever wins will change the whole world...... .
// After minutes of fighting, they both feel tired, so they makes an agreement: Gandalf will cast his strongest spell to attack, and Knuckles needs to defend it. If Knuckles defends successfully, Knuckles wins; otherwise,  Gandalf wins.
// Gandalf will cast a spell "Pegasus Meteor Spell(天馬流星咒)". The spell will summon meteors from Pegasus and hit the ground hardly. The meteors will hit in a n*n square range. Knuckles needs to stop all the meteors, otherwise he'll be hit and lose the fight. 
// Knuckles will use "Sputum of the North Star(北斗神痰)" to defend. He will spit k sputum. Each time he spit, the next sputum will be more powerful. In other word, the power of sputums is sorted in ascending order. 
// He's going to spit on every meteor that falls onto the ground. The power of his sputum must be equal to or more powerful than the meteor he spits to destroy the meteor. If he spits a sputum that is weaker than the target meteor, the meteor will directly fall onto Knuckles' head and he'll lose. That is, each meteor can be spitted only once.
// Knuckles will give you n, k, the power of each meteor and where will it fall, the sequence of the power of his sputum. You're going to tell him if he could win this fight or not.

// There are some meteors falling in a n*n area. The meteor's power of section (i,j) is denoted as "M(i,j)". There's no meteor if M(i,j) = 0. 
// You have a sequence of sputum denoted as "S(i)", sorted in ascending order.
// If any sputum S(i) >= M(j,k), meteor M(j,k) can be destroyed by sputum S(i). At the same time, the sputum S(i) will be brken, too, which means that you can only use one sputum once. 
// If all of the meteors can be destroyed (which means all elements in M are 0), Knuckles wins. Otherwise, he loses.

// Input
// The first line contains two positive integer n and k.
// The next n lines, each line contains exactly n numbers, indicating the power of the meteors which will fall onto this place. 0 means no meteor will fall on this place.
// The last line contains k numbers, which indicate the power of every sputum. As the description says, the power will be in ascending order.
// 1 <= n <= 100, 1 <= k <= n*n, and the power of meteors and the power of sputums will be in range [1,10000].

// Output
// You should output only one line. If Kunckles wins, output "Victory belongs to the Spitters!", otherwise output "Fly you fool."

// Sample Input  
// 5 13
// 0 0 1 3 4
// 8 7 4 2 3
// 0 0 0 0 0
// 0 0 0 99 0
// 9 9 9 9 0
// 2 2 3 4 4 5 8 13 17 21 23 25 108

// Sample Output  
// Victory belongs to the Spitters!

// Partial Judge Code
// 12154.c

// Partial Judge Header
// 12154.h
#include<stdio.h>
#include<stdlib.h>
#include"function.h"

int cmp(const int *a, const int *b){
    return (*a) > (*b);
}

int solve(int *n, int *k, int *sputum, int (*spell)[MAX_N]){
    // n: Number of spell area(Meteor)
    // k: Number of Sputum
    // nTotal: Number of spellS(Meteor)
    const int ns = (*n), ks = (*k);
    int nTotal = 0;
    int *spellS = (int *)malloc(sizeof(int) * ns * ns);

    for(int i = 0; i < ns; i++){
        for(int j = 0; j < ns; j++){
            if(spell[i][j] > 0){
                spellS[nTotal] = spell[i][j];
                // printf("%d ", spellS[nTotal]);
                nTotal++;
            }
        }
    }

    if(nTotal > ks){return 0;}
    qsort(spellS, nTotal, sizeof(int), (int (*)(const void*, const void*))cmp);

    int flag = 1;
    for(int i = 0; i < ks; i++){
        // printf("[%d]Sputim:%d\tSpell:%d\n", i, sputum[i], spellS[i]);
        
        if(i >= nTotal){
            break;
        }
        if(sputum[i] < spellS[i]){
            flag = 0;
            break;
        }
    }

    // printf("\n%d\n", flag);

    return flag;
}