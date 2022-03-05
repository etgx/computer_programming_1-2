// NTHUOJ 11759 - B - Great Depression Again   
// Description
// Writer: jjjjj19980806       Description: pclightyear        Difficulty: ★★★★★
// As you all know, Kim Jong-un is the Chairman of the Workers' Party of Korea and supreme leader of North Korea. Recently, more and more countries and international bodies have been imposing economic sanctions against North Korea. The import of the raw material of all kind decreases dramatically, and the automobile industry in North Korea is suffering from severe depression again. Reorganization of the whole industry is needed to make North Korea GREAT AGAIN.
// According to the survey, there are n factory in North Korea. Each of them can produce two kinds of cars (car A & car B). Now, the supreme leader wants to assign x factory to produce car A and y factory to produce car B (i.e. no factory will produce two kinds of car at the same time.) so that the net profit will become maximum. However, due to the shortage of the raw material, it is possible that some factory will not produce any cars (i.e. x + y <= n).
// The supreme leader will give you the net profit each factory can make by producing car A and car B. Your program need to output the name of the x factory which produce car A in lexicographical order. If there are multiple answers, you need to output the one such that the total net profit of car A is maximum. 
// DO NOT DISAPPOINT HIM!!

// Input
// The first line contains three integers n, x, y, representing the total number of factory, the number of factory planned to produce car A, and the number of factory planned to produce car B. (according to the supreme leader's demand)
// The next n lines contains one string si and two integers ai, bi, representing the name of each factory, and the net profit each factory can make by producing only car A or only car B.
// It is guaranteed that :
// 0 < n, x, y ≤ 500
// x + y <= n
// 1 ≤ | si | ≤  20
// 0 < ai, bi < 106
// ai ≠ aj, bi ≠ bj  if i ≠ j.
// No duplicate names appears.

// Output
// Please output the list of x factory that need to produce car A in lexicographical order so that it will maximum the net profit.

// Sample Input  
// 10 3 4
// TOYOTA 10 100
// GM 20 90
// FORD 30 80
// Volkswagen 40 70
// Daimler 50 60
// Honda 60 50
// Nissan 70 40
// PEUGEOT 80 30
// FIAT 90 20
// BMW 100 10

// Sample Output  
// BMW
// FIAT
// PEUGEOT

#include<stdio.h>
#include<stdlib.h>

int main(){

    return 0;
}