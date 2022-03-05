// I2P - Kuo Week0 Problem 4 | NTHUOJ 12605 - Rebranding   
// Description
// The name of one small but proud corporation consists of n lowercase English letters. The Corporation has decided to try rebranding — an active marketing strategy, that includes a set of measures to change either the brand (both for the company and the goods it produces) or its components: the name, the logo, the slogan. They decided to start with the name.
// For this purpose the corporation has consecutively hired m designers. Once a company hires the i-th designer, he immediately contributes to the creation of a new corporation name as follows: he takes the newest version of the name and replaces all the letters x_i by y_i, and all the letters y_i by x_i. This results in the new version. It is possible that some of these letters do no occur in the string. It may also happen that x_i coincides with y_i. The version of the name received after the work of the last designer becomes the new name of the corporation.
// Manager Arkady has recently got a job in this company, but is already soaked in the spirit of teamwork and is very worried about the success of the rebranding. Naturally, he can’t wait to find out what is the new name the Corporation will receive.
// Satisfy Arkady’s curiosity and tell him the final version of the name.
// This Problem is reproduced from http://codeforces.com/problemset/problem/591/B

// Input
// The first line of the input contains two integers n and mm (1 ≤ n, m ≤ 200,000)— the length of the initial name and the number of designers hired, respectively.
// The second line consists of nn lowercase English letters and represents the original name of the corporation.
// Next m lines contain the descriptions of the designers’ actions: the i-th of them contains two space-separated lowercase English letters x_i and y_i.

// Output
// Print the new name of the corporation.
// Remember '\n' on the end of line.

// Sample Input  

// 11 6
// abacabadaba
// a b
// b c
// a d
// e g
// f a
// b b

// Sample Output  

// cdcbcdcfcdc

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_ALPHABET 26

void init_map_dict(char *map, char **dict, int len){
    for(int i = 0; i < len; i++){
        map[i] = 'a' + (char)i;
        dict[i] = &(map[i]);
        // printf("map[%d]: %c | dict[%d]: %c\n", i, map[i], i, *dict[i]);
    }
}

void rebrand(char *map, char **dict, char x, char y){
    int x_idx = (int)(x - 'a'), y_idx = (int)(y - 'a');
    char *x_addr = dict[x_idx], *y_addr = dict[y_idx];
    
    // Swap character
    char temp_char = *x_addr;
    *x_addr = *y_addr;
    *y_addr = temp_char;

    // Swap Mapping
    dict[x_idx] = y_addr;
    dict[y_idx] = x_addr;
}

int main(){
    int n = 0, m = 0;
    scanf("%d %d\n", &n, &m);
    char *brand = (char*)malloc(sizeof(char) * (n + 1));
    char map[NUM_ALPHABET] = {0}, *dict[NUM_ALPHABET] = {0};

    scanf("%s\n", brand);
    // printf("%s\n", brand);

    init_map_dict(map, dict, NUM_ALPHABET);
    for(int i = 0; i < m; i++){
        char x = 0, y = 0;
        scanf("%c %c\n", &x, &y);
        // printf("X: %c | Y: %c\n", x, y);
        rebrand(map, dict, x, y);
    }

    for(int i = 0; i < n; i++){
        int idx = (int)(brand[i] - 'a');
        // printf("brand[%d]: %c - %d | map[%d]: %c\n", i, brand[i], idx, idx, map[idx]);
        brand[i] = map[idx];
    }
    printf("%s\n", brand);
}