// IPHTC2 Week4 Problem 1 | NTHUOJ 12371 - Crazy give head
// Description
// A famous streamer once said: "From now on, CRAZY GIVE HEAD!!". The streamer was so furious that he said many dirty words. You wonder how many times did a specific word appears in those words.
// You will have one long string SS and one short string pp.
// Then you will have qq times of queries.
// Each query includes two numbers a, ba,b which indicate the range in string SS.
// The sum of a range indicates the occurrences of string p from position a of string SS to position b of string SS.
// Your task is finding the maximum sum from all the queries.
// Note that the index is start from 11.
// For example:
// You have S="ababaaaaba"S="ababaaaaba" and p="ba"p="ba". You got q = 5q=5, the five queries are as follow:
// 88 99
// 22 55
// 66 77
// 66 66
// 22 44
// Position 88 to position 99 the occurrence of pp equals 00
// Position 22 to position 55 the occurrence of pp equals 22
// Position 66 to position 77 the occurrence of pp equals 00
// Position 66 to position 66 the occurrence of pp equals 00
// Position 22 to position 44 the occurrence of pp equals 11
// Therefore, the answer is 22.

// Input
// Input end with EOF.
// Each testcase contains several lines.
// First line contains two string S(1\leq strlen(S) \leq 1000)S(1≤strlen(S)≤1000) and p(1\leq strlen(q)\leq 1000)p(1≤strlen(q)≤1000)
// Second line one integer q(1 \leq q \leq 200000)q(1≤q≤200000)
// The following are qq lines. Each line contain two integer a,b(1\leq a \leq b \leq strlen(S))a,b(1≤a≤b≤strlen(S))

// Output
// For each testcases print the maximum sum from all the queries.
// Remember to print \n at the end of each output.

// Sample Input 1 
// ababaaaaba ba
// 5
// 8 9
// 2 5
// 6 7
// 6 6
// 2 4
// abbababaaa b
// 6
// 1 7
// 4 6
// 7 7
// 10 10
// 3 10
// 1 1

// Sample Output 1
// 2
// 4

// Hint
// The biggest problem is that if you construct a prefix sum array based on the occurrences of p[0]p[0] and check if it makes the entire pp , you will get error when the range cut the "part of pp".
// Therefore consider this: if we want to avoid the "part of pp" problem we can consider that if a part of pp will be cut in range (L, R)(L,R) that means p[0]p[0] must in the place of (R-length(p)+2, R)(R−length(p)+2,R). Therefore we only need to consider range (L,R-length(p)+1)(L,R−length(p)+1)
// To sum up, we can change the range (L, R)(L,R) into (L, R-length(p)+1)(L,R−length(p)+1). Use the prefix sum array to calculate this problem will be like: prefix[ R-length(p)+1 ] - prefix[ L-1 ]prefix[R−length(p)+1]−prefix[L−1]. In this way, we can avoid the "part of pp" problem and solve the question.

// ⠄⠄⠄⠄⠄⠄⠄
// ⠄⠄⠄⠄⠄⠄⠄⠈⠉⠁⠈⠉⠉⠙⠿⣿⣿⣿⣿⣿
// ⠄⠄⠄⠄⠄⠄⠄⠄⣀⣀⣀⠄⠄⠄⠄⠄⠹⣿⣿⣿
// ⠄⠄⠄⠄⠄⢐⣲⣿⣿⣯⠭⠉⠙⠲⣄⡀⠄⠈⢿⣿
// ⠐⠄⠄⠰⠒⠚⢩⣉⠼⡟⠙⠛⠿⡟⣤⡳⡀⠄⠄⢻
// ⠄⠄⢀⣀⣀⣢⣶⣿⣦⣭⣤⣭⣵⣶⣿⣿⣏⠄⠄⣿
// ⠄⣼⣿⣿⣿⡉⣿⣀⣽⣸⣿⣿⣿⣿⣿⣿⣿⡆⣀⣿
// ⢠⣿⣿⣿⠿⠟⠛⠻⢿⠿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣼
// ⠄⣿⣿⣿⡆⠄⠄⠄⠄⠳⡈⣿⣿⣿⣿⣿⣿⣿⣿⣿
// ⠄⢹⣿⣿⡇⠄⠄⠄⠄⢀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
// ⠄⠄⢿⣿⣷⣨⣽⣭⢁⣡⣿⣿⠟⣩⣿⣿⣿⠿⠿⠟
// ⠄⠄⠈⡍⠻⣿⣿⣿⣿⠟⠋⢁⣼⠿⠋⠉⠄⠄⠄⠄
// ⠄⠄⠄⠈⠴⢬⣙⣛⡥⠴⠂⠄⠄⠄⠄⠄⠄⠄⠄⠄... (the photo of the famous streamer)

// 2021/10/10 SYC 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define S_LEN 1003
#define P_LEN 1003
#define SIZEOF_CHAR sizeof(char)

void build_prefix_sum(int *prefix_sum, char *S, char *p){
    int S_len_real = 0, p_len_real = 0;
    for(S_len_real = 0; S_len_real < S_LEN; S_len_real++){
        if(S[S_len_real] == 0)
            break;
    }
    for(p_len_real = 0; p_len_real < P_LEN; p_len_real++){
        if(p[p_len_real] == 0)
            break;
    }
    for(int i = 0; i <= S_len_real; i++){
        if(i < p_len_real){
            prefix_sum[i] = 0;
        }else{
            char buf[P_LEN] = {0};
            memcpy(buf, &(S[i - p_len_real]), p_len_real);
            if(strncmp(buf, p, p_len_real) == 0){
                prefix_sum[i] = prefix_sum[i - 1] + 1;
            }else{
                prefix_sum[i] = prefix_sum[i - 1];
            }
        }
    }
}

int count_occur(char *p, int *prefix_sum, int a, int b){
    int a_reindex = a + strlen(p) - 1;
    if(a_reindex <= b)
        return prefix_sum[b] - prefix_sum[a_reindex - 1];
    else
        return 0;
}

int main(){
    char S[S_LEN] = {0}, p[P_LEN] = {0};
    while(scanf("%s %s", S, p) != EOF){
        int q = 0, a = 0, b = 0, max_occur = 0;
        int prefix_sum[S_LEN + 1] = {0};
        build_prefix_sum(prefix_sum, S, p);

        scanf("%d", &q);
        for(int i = 0; i < q; i++){
            scanf("%d %d", &a, &b);
            int occur = count_occur(p, prefix_sum, a, b);
            if(max_occur < occur)
                max_occur = occur;
        }
        printf("%d\n", max_occur);
        memset(S, 0, SIZEOF_CHAR * S_LEN);
        memset(p, 0, SIZEOF_CHAR * P_LEN);
    }
    
    return 0;
}