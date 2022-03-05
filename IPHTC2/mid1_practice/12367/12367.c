// IPHTC2 Week2 Problem 1 | NTHUOJ 12367 - Gey cool~
// Description
// A famous streamer once said: "Gey cool...gey...gey...gey... gey cool~". While this streamer playing his video games, you still need to finish your OJ test. The following is your problem.
// You will have nn numbers and qq times of queries.
// Each query includes two numbers aa, bb which indicate the range.
// The sum of a range indicates the sum of numbers from position aa to position b$.
// If aa bigger than bb , you need to sum up the numbers from aa to the end and from the start to bb.
// If aa is smaller than bb you just need to sum up the numbers from aa to bb.
// If aa is equal to bb, than there's only one number, and the number will be the sum.
// Your task is finding the range that has the maximum sum.
// Note that the index is start from 1.
// If you find multiple answers, you only need to answer the first one appear in the queries.

// Input
// Input end with EOF.
// Each testcase contains several lines.
// First line contains two integer n(1\leq n \leq 2000000)n(1≤n≤2000000)​​ and q(1\leq q\leq2000000)q(1≤q≤2000000)
// Second line contains nn integers. Each number ranged from 1\sim 10000000001∼1000000000.
// The following are qq lines. Each line contain two integer a,b(1\leq a,b \leq n)a,b(1≤a,b≤n)
// Testcases are divided by a blank line.

// Output
// For each testcases print the answer in the following format:
// Max_range: (%d,%d); Value: %d
// The first two integer means the two numbers which indicate the range.
// The last integer means the sum of this range.
// Remember to print \n at the end of each output.

// Sample Input 1 
// 10 5
// 7 1 19 14 8 14 20 10 3 8
// 3 3
// 10 1
// 4 4
// 8 1
// 9 9

// 10 8
// 16 17 18 11 999 6 5 1 18 20
// 1 2
// 6 8
// 6 10
// 3 4
// 7 3
// 5 5
// 6 9
// 1 4

// 10 5
// 7 1 19 14 8 14 20 10 3 8
// 2 4
// 10 1
// 4 4
// 8 1
// 9 9

// Sample Output 1
// Max_range: (8,1); Value: 28
// Max_range: (5,5); Value: 999
// Max_range: (2,4); Value: 34

// 2020/09/27 SYC

#include <stdio.h>
#include <stdlib.h>

long long int query(long long int n, long long int *seq, long long int *prefix_sum, long long int a, long long int b){
    long long int b_minus_a = prefix_sum[b] - prefix_sum[a - 1];
    if(b >= a)
        return b_minus_a;
    else{
        return prefix_sum[n] + b_minus_a;
    }
}

int main(){
    char input = 0;
    do{
        long long int n = 0, q = 0;
        long long int *seq = NULL, *prefix_sum = NULL;
        long long int max_a = 0, max_b = 0, max_sum = 0;
        scanf("%lld %lld", &n, &q);
        if(n <= 0 || q <= 0)
            break;
        
        seq = (long long int*)malloc((n + 1) * sizeof(long long int));
        prefix_sum = (long long int*)malloc((n + 1) * sizeof(long long int));
        prefix_sum[0] = seq[0] = 0;

        for(int i = 1; i <= n; i++){
            scanf("%lld", &(seq[i]));
            prefix_sum[i] = prefix_sum[i - 1] + seq[i];
        }

        for(int i = 0; i < q; i++){
            long long int a = 0, b = 0, sum = 0;
            scanf("%lld %lld", &a, &b);

            sum = query(n, seq, prefix_sum, a, b);
            // printf("Range: (%lld, %lld) = %lld\n", a, b, sum);
            if(sum > max_sum){
                max_a = a;
                max_b = b;
                max_sum = sum;
            }
        }

        printf("Max_range: (%lld,%lld); Value: %lld\n", max_a, max_b, max_sum);
        free(seq);
        input = getc(stdin);
        // printf("Char: %d\n", input);
    }while(input != EOF);
}