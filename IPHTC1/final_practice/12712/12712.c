// NTHUOJ 12712 - Got flunked   
// Description
// Help! Help! We're all gonna be flunked by these devil-like TAs!
// ── Students
// It's said that there's a course that every student who take that course will be flunked...
// The course might be Advanced Calculus, Complex Analysis ... it could be Introduction to Programming! Who knows?
// The only thing you know is that the professor of this course is Professor Chen-Tzong Hwann(煥陳宗), a.k.a. CTH. His TAs keep producing extremely hard problems, leads that every student are going to be flunked.
// However, flunking every student means that CTH needs to submit a report to the administration of the university, and CTH is too lazy to write that report, so he decide to let exactly one student pass.
// The class have  students, CTH will organize a tournament. The tournament is going to be held with the following format:
// If there's only one student remaining, then the student is the winner, the tournament ends.
// If the number of remaining students is even, they split in pairs and compete for each pair. The loser of each pair will be eliminated(no draws for this competition).
// Otherwise, if the number of remaining students is odd, they'll compete each other once in round robin tournament and decide the final winner, then the tournament ends.
// For the round robin tournament part, if there are  students remaining, there will be  competitions since they compete with everyone once.
// For example, if there are 20 students initially, they would have 10 competitions, then 10 students are eliminated. The remaining 10 students would have 5 competitions and remain 5 students, then have 10 competitions for round robin tournament. Totally there are 10+5+10=25 competitions.
// CTH's TA want to see exactly  competitions in order to see them suffer. He asks you to calculate the minimum number of students that the course need to have.

// Hint:
// This problem involves brute force(暴力搜尋) and binary search(二分搜尋). One of the solutions is to combine the two techniques. You may try to think what we can enumerate, and what we can do a binary search.
// Brute Force: usually applied when the number is small.
// Binary Search: If the sequence is in increasing / decreasing order, the binary search technique can be applied.

// Input
// The first line contains an integer . There are  testcases below. .
// There are  lines below. Each line contains exactly one integer , the number of competitions.
// .

// Output
// For each testcase, output its minimum number of students that the course need to have with newline.
// If there's no such answer, print -1 instead.

// Sample Input  
// 5
// 3
// 25
// 2
// 314
// 576460752303423487

// Sample Output  
// 3
// 20
// -1
// -1
// 576460752303423488

#include <stdio.h>
#include <stdlib.h>
#define MaxI 60 // 10^3 ~ 2^10 -> 10^18 ~ 2^60
#define MaxK 1000000000000000000 // 10^18
// #define MaxKI 499
#define Error -1

// Compute the number of the competitions needed to be held from given the number of students
long long int s2c(const long long int k, int i){ // Student to Competitions
    // printf("%d\n", 1 << i);
    const long long int unit = 1;
    return k * (k - 1) / 2 + k * ((unit << i) - 1);

}
// K must be odd, convert ki into k with this
long long int odd(const long long int ki){
    return 2 * ki + 1;
}

long long int binSearch(const long long int target, const int ipow){
    // Setup upper bound for endKI with ipow
    const long long int unit = 1;
    const long long int upper = unit << (60 - ipow);
    long long int startKI = 0, endKI = upper;
    long long int midKI = (startKI + endKI) / 2; // Get odd
    // int pow = 1 << ipow;

    while(startKI < endKI){
        // printf("StartKI: %lld EndKI: %lld MidKI: %lld -> s2c: %lld\n", startKI, endKI, midKI, s2c(odd(midKI), ipow));
        if(s2c(odd(midKI), ipow) < target){
            startKI = midKI + 1;
            midKI = (startKI + endKI) / 2;
        }else{
            endKI = midKI;
            midKI = (startKI + endKI) / 2;
        }
    }

    if(s2c(odd(midKI), ipow) != target){return Error;}
    else{return (odd(midKI) * (unit << ipow));}
}

long long int solve(const long long int target){
    for(int j = 0; j < MaxI; j++){
        // printf("2^%d:\n", j);
        long long int res = binSearch(target, j);
        // printf("Solve: %lld\n", res);
        if(res != Error){return res;}
    }

    return Error;
}

int main(){
    int t = 0;
    scanf("%d\n", &t);

    for(int i = 0; i < t; i++){
        long long int n = 0;
        scanf("%lld\n", &n);
        // printf("N: %lld\n", n);

        // solve
        long long int res = solve(n);
        printf("%lld\n", res);
    }
    return 0;
}