// IPHTC2 Week9 Problem Bonus | NTHUOJ 13002 - the answer to life, the universe, and everything
// Description
// The Answer to the Ultimate Question of Life, The Universe, and Everything. ── 42
// "The Answer to the Ultimate Question of Life, The Universe, and Everything", they said.
// "42", Siri said when I asked her the meaning of life.
// And 42 is divided by 3.
// Coincidence? I don't think so.
// If we focus on the problem ID, the number is 110, which is divided by 3 in 3-base representation.
// What about the title? We seek to find the answer to "life", the "universe", and "everything". If we map 'a' as 1, 'b' as 2 and so on, the sum of "life", "universe", and "everything" is 32, 113, 133, respectively. It seems that there's no relationship between these numbers. However, if we calculate the difference of "everything" and the other two, we'll get the answer -12, which is also divided by 3. And if we resemble the title, we can even get a word "triangle".
// The more we focus on, the more evidence we found. What evidence? Now I can say that this problem is:
// Illuminati confirmed.
// Knuckles is on his way of finding his queen. However, a strange giant triangle stele with a single eye blocked his way, Knuckles needs to solve a puzzle so that he shall pass and keep his journey of finding the queen.
// Knuckles needs to solve the puzzle shown below:

// Given a sequence F:F_0=1,\ F_i=F_{i-1}+F_{i-2}F, and an non-negative integer nn, he needs to find a minimal F_1 
// such that F_x=n for a suitable x.
// For example, if n=20n=20, the minimal F_1=6, since the sequence F will be <1,6,7,13,20> where F_4=n, and we cannot find a smaller F_1 that nn appears in F.

// Input
// The input contains multiple testcases. The total number of testcases is no larger than 100.
// For each testcase, there will be only one integer n. 
// 0\le n\le 10^{18}

// Output
// For each testcase, output a single number, represents the minimal non-negative integer F_1 that there's n appears in sequence F.

// Sample Input 1 

// 0
// 1
// 20
// 2147483647
// 765237384630454014
// 554
// 1221305
// 48367341873
// 731652777315453
// 997974924660318991

// Sample Output 1

// 0
// 0
// 6
// 1073741823
// 765237384630454013
// 42
// 42
// 42
// 42
// 42

// Solution:

// Observe the following sequence, while F_1 = 0, 1, 2, 3, 4, 5, 6...
// 1, 0, 1, 1, 2, 3, 5, 8, 13, 21
// 1, 1, 2, 3, 5, 8, 13, 21, 34
// 1, 2, 3, 5, 8, 13, 21, 34
// 1, 3, 4, 7, 11, 18, 29
// 1, 4, 5, 9, 14, 23
// 1, 5, 6, 11, 17, 28
// 1, 6, 7, 13, 20, 33

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_SEQ_LEN 90

void print_seq(long long *seq, long long n){
    for(long long i = 0; i < n; i++){
        printf("%lld ", seq[i]);
    }
    printf("\n");
}

void build_fibonacci(long long *seq, long long n){
    seq[0] = seq[2] = 0;
    seq[1] = 1;
    for(long long i = 3; i < n; i++){
        seq[i] = seq[i - 2] + seq[i - 1];
    }
}

long long compute_F1(long long *seq, long long n, long long x){
    long long idx = 0, f1 = 0;
    for(idx = n - 1; idx > 0; idx--){
        // printf("[%lld]: %lld\n", idx, seq[idx]);

        long long fn = seq[idx], fn_add = seq[idx], addition = seq[idx - 1], i = 0, found = 0;
        if(fn < x){
            long long residual = x - fn;
            if(addition > 0 && residual % addition == 0){
                i = (residual / addition) + 1; 
                fn_add = fn + addition * (i - 1);
                found = 1; 
                // printf("(%lld - %lld) / %lld = %lld\n", x, fn, addition, i);
            }
        }

        if(fn_add == x){
            f1 = i;
            // printf("f1=%lld\n", f1);
            break;
        }
        
    }
    return f1;
}

int main(){
    long long fibonacci_seq[MAX_SEQ_LEN] = {0}, x = 0;
    build_fibonacci(fibonacci_seq, MAX_SEQ_LEN);

    // print_seq(fibonacci_seq, MAX_SEQ_LEN);

    while(scanf("%lld", &x) != EOF){
        // printf("X: %lld\n", x);
        printf("%lld\n", compute_F1(fibonacci_seq, MAX_SEQ_LEN, x));
    }

    return 0;
}