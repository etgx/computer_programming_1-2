// NTHUOJ 12138 - too many treasures   
// Description
// Ovuvuevuevue Enyetuenwuevue Ugbemugbem Osas accidentally found an undiscovered tomb. He successfully sneaked in without triggering any traps. When he finally got into the treasure room, he found a note that warns tomb raiders about the trap in the treasure room. Osas arranged the note and concluded some rules:
//  - The treasure room has n treasure crates, each crate has its value. The values are sorted in descending order.
//  - There are several intervals [l,r] on the note.
//  - Tomb raiders must loot less than or equal to m treasure crates in the correct interval, where m is a number that Osas have to guess.
//  - If any tomb raider loot more than m treasure crates or loot any crate that not in the interval, the trap would trigger and kill that tomb raider! Osas doesn't want to die here.
// Osas wants these treasures, but he doesn't want to die. Osas wants to know if he pick one interval and guess a number as "m", what is the maximum value he could loot? Osas asks you for help!
// Osas will give you the value of every treasure crate and the number he would like to guess, you need to write a program to help him.

// Input
// The input contains exactly one testcase.
// The first line contains two integers n, q. q indicates the amount of queries of (l,r,m).
// The next line is the sequence of values of n treasure crates, each seperated by a space. 
// The next q lines, each line contains exactly three integers l, r, m.
// 1<=m<=n<=106, 1<=q<=106, 1<=l<=r<=n, m<=r-l+1, the value of every treasure crate won't larger than 105 or smaller than -105. All of the values are integers. Notice that the value could be negative, and Osas can choose nothing.
// Note that the sequence index starts from 1. For example: for a sequence "a": "3 4 5 6 7", a[4]=6, a[1]=3.

// Output
// For each query, output the maximum value Osas could get. Each query holds exactly one line.
// Remember to print a '\n' at the end of the output.

// Sample Input  
// 5 5
// 97836 12032 3029 -51025 -73177
// 5 5 1
// 5 5 1
// 1 4 3
// 1 2 1
// 4 4 1

// Sample Output  
// 0
// 0
// 112897
// 97836
// 0

// SYC
// 2020 / 4 / 13

#include<stdlib.h>
#include<stdio.h>

int main(){
    long int n = 0;
    long int q = 0;

    long int prefixSum[1000005] = {0};

    scanf("%ld", &n);
    scanf("%ld", &q);

    long int accSum = 0;
    // prefixSum[0] = 0;
    for(long int i = 1; i <= n; i++){
        long int temp = 0;
        scanf("%ld", &temp);
        if(temp > 0){
            accSum += temp;
            prefixSum[i] = accSum;
        }else{
            accSum += 0;
            prefixSum[i] = accSum;
        }
        // printf("%ld ", prefixSum[i]);
    }

    // printf("\n");

    for(long int i = 0; i < q; i++){
        long int a = 0;
        long int b = 0;
        long int c = 0;

        scanf("%ld", &a);
        scanf("%ld", &b);
        scanf("%ld", &c);

        // long int idxA = a - 1;
        // long int idxB = b - 1;

        // printf("%ld %ld %ld %ld %ld\n", a, b, c, a + c - 1, a - 1);
        // printf(" %ld\n", );
        printf("%ld\n", prefixSum[a + c - 1] - prefixSum[a - 1]);
    }

    return 0;
}