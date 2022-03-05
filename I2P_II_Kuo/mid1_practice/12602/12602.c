// I2P - Kuo Week0 Problem 2 | NTHUOJ 12602 - OuQ String   
// Description
// Define the level 1 string s1 = “OuQ”,
// and the level k string sk = “O” + sk−1 + “u” + sk−1 + “Q”.
// For example:
// s2 = “O” + s1 + “u” + s1 + “Q” = “OOuQuOuQQ”
// s3 = “OOOuQuOuQQuOOuQuOuQQQ”
// Given 3 integeres k,l,r.
// Please find all characters of sk[l],sk[l+1],...sk[r−1],sk[r]

// Input
// There’re multiple testcases in input.
// Three integers k,l,r on each line.
// 1 ≤ k ≤ 50
// 0 ≤ l ≤ r < length of sk
// 1 ≤ |r−l+1| ≤ 100

// Output
// For each testcase, print |r−l+1| characters,sk[l],sk[l+1],...sk[r−1],sk[r], for a line.
// Remember ‘\n’ on the end of each line.

// Sample Input 

// 1 0 2
// 2 1 7
// 1 1 1

// Sample Output  

// OuQ
// OuQuOuQ
// u

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define CHAR_BYTE sizeof(char)
#define MAX_K 50

char* build_s1(){
    int str_full_bytes = CHAR_BYTE * 4;
    char *str_full = (char*)malloc(str_full_bytes);
    memset(str_full, 0, str_full_bytes);
    str_full[0] = 'O', str_full[1] = 'u', str_full[2] = 'Q';
    return str_full;
}

char* new_concat_str(char *substr){
    int str_len = strlen(substr), str_full_bytes = CHAR_BYTE * (str_len * 2 + 4);
    char *str_full = (char*)malloc(str_full_bytes);
    memset(str_full, 0, str_full_bytes);
    strncpy(&(str_full[1]), substr, str_len);
    strncpy(&(str_full[str_len + 2]), substr, str_len);
    str_full[0] = 'O', str_full[str_len + 1] = 'u', str_full[str_len * 2 + 2] = 'Q';
    return str_full;
}

char* build_str_dp(int k, char **dp_map){
    char *str = dp_map[k - 1];
    return new_concat_str(str);
}

void build_k_dp_map(int k, char **dp_map){
    for(int i = 0; i <= k; i++){
        if(dp_map[i] == NULL){
            // printf("Building s%d\n", i);
            if(i <= 1){
                // s1, s0
                dp_map[i] = build_s1();
            }else{
                // sk, k > 1
                dp_map[i] = build_str_dp(i, dp_map);
            }
            // printf("DP_MAP[%d]: %s\n", i, dp_map[i]);
        }
    }
}

// 1. DP Method
char* get_str(int k, char **dp_map){
    build_k_dp_map(k, dp_map);
    char *str_k_map = dp_map[k];
    char *str_ret = (char*)malloc(CHAR_BYTE * strlen(str_k_map));
    strcpy(str_ret, str_k_map);
    return str_ret;
}

// 2. Bottom-Up Method
char* build_str_bu(int k){
    char *str_sub = NULL, *str_full = NULL;
    for(int i = 1; i <= k; i++){
        if(i == 1){
            str_full = build_s1();
        }else{
            str_sub = str_full;
            str_full = new_concat_str(str_sub);
            free(str_sub);
        }
    }
    return str_full;
}

// 3. Top-Down Method
char* build_str(int k){
    if(k <= 1){
        int str_full_bytes = CHAR_BYTE * 4;
        char *str_full = (char*)malloc(str_full_bytes);
        memset(str_full, 0, str_full_bytes);
        str_full[0] = 'O', str_full[1] = 'u', str_full[2] = 'Q';
        return str_full;
    }else{
        char *str = build_str(k - 1);
        int str_len = strlen(str), str_full_bytes = CHAR_BYTE * (str_len * 2 + 4);
        char *str_full = (char*)malloc(str_full_bytes);
        memset(str_full, 0, str_full_bytes);
        strncpy(&(str_full[1]), str, str_len);
        strncpy(&(str_full[str_len + 2]), str, str_len);
        str_full[0] = 'O', str_full[str_len + 1] = 'u', str_full[str_len * 2 + 2] = 'Q';
        free(str);
        return str_full;
    }
}

// 4. Counting Directly
char count(long long k, long long i){
    // Due to memory issue, this problem can only be solved by this method.
    static long long *len_map = NULL;
    if(len_map == NULL){
        // Build the map of the length of the strings
        len_map = (long long*)malloc(sizeof(long long) * (MAX_K + 1));
        for(long long i = 1; i <= MAX_K; i++){
            if(i == 1){
                // Length of s_1
                len_map[i] = 3;
            }else{
                // Length of s_k, k > 1
                len_map[i] = len_map[i - 1] * 2 + 3;
            }
        }
    }
    if(i == 0){
        // The head of each string should be 'O', because s_k = 'O' + s_{k-1} + 'u' + s_{k-1} + 'Q'
        // Follow similar idea for the following case
        return 'O';
    }else if(i == len_map[k] / 2){
        // Middle
        return 'u';
    }else if(i == len_map[k] - 1){
        // Tail
        return 'Q';
    }else if(i > 0 && i < len_map[k] / 2){
        // If the index of string s_k, i_{s_k} minus 1, it would be the index i_{s_{k-1}} of the substring in the first half part.
        // i_{s_k} - 1 = i_{s_{k-1}}
        // The last half part follows similar idea.
        return count(k - 1, i - 1);
    }else if(i > len_map[k] / 2 && i < len_map[k] - 1){
        // i_{s_k} - (i_{s_k} / 2) - 1 = i_{s_{k-1}}
        return count(k - 1, i - (len_map[k] / 2) - 1);
    }
}

int main(){
    int k = 0, l = 0, r = 0, built_k = 0;
    // char *dp_map[MAX_K] = {NULL};
    while(scanf("%d %d %d", &k, &l, &r) != EOF){
        // printf("K: %d, L: %d, R: %d\n", k, l, r);
        // char *str_full = build_str_bu(k);
        for(int i = l; i <= r; i++){
            // printf("%c", str_full[i]);
            printf("%c", count(k, i));
        }
        printf("\n");
        // printf("%s\n", str_full);
        // free(str_full);
    }
    return 0;
}