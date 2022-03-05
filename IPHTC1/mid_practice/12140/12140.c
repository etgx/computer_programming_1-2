// NTHUOJ 12140 - HaSaKi~   
// Description
// "Death is like the wind, always by my side.", said by a famous streamer, Mr. Yasuoo.
// Mr. Yasuoo is known for his skill "Slides up".
// When Mr. Yasuoo slides across a string S, he will be asked t questions.
// In each question, he should respond the number of occurrences of substring s, given a interval of [ l, r ].
// Specifically, if the string S is "hasahasasaki" and the substring s is "sa", Mr. Yasuoo should answer 2 given the interval of [3, 9].
// Since the interval [3~9]  indicates "sahasas",  the number of occurrences of substring "sa" is then 2.
// Note that the index of string starts from 1 and contains only 'a' ~ 'z'.
// Help Mr. Yasuoo to answer these questions before he starts feeding, ASAP!

// ⠄⠄⠄⠄⠄⠄⠄
//  ⠄⠄⠄⠄⠄⠄⠄⠈⠉⠁⠈⠉⠉⠙⠿⣿⣿⣿⣿⣿
//  ⠄⠄⠄⠄⠄⠄⠄⠄⣀⣀⣀⠄⠄⠄⠄⠄⠹⣿⣿⣿
//  ⠄⠄⠄⠄⠄⢐⣲⣿⣿⣯⠭⠉⠙⠲⣄⡀⠄⠈⢿⣿
//  ⠐⠄⠄⠰⠒⠚⢩⣉⠼⡟⠙⠛⠿⡟⣤⡳⡀⠄⠄⢻
//  ⠄⠄⢀⣀⣀⣢⣶⣿⣦⣭⣤⣭⣵⣶⣿⣿⣏⠄⠄⣿
//  ⠄⣼⣿⣿⣿⡉⣿⣀⣽⣸⣿⣿⣿⣿⣿⣿⣿⡆⣀⣿
//  ⢠⣿⣿⣿⠿⠟⠛⠻⢿⠿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣼
//  ⠄⣿⣿⣿⡆⠄⠄⠄⠄⠳⡈⣿⣿⣿⣿⣿⣿⣿⣿⣿
//  ⠄⢹⣿⣿⡇⠄⠄⠄⠄⢀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
//  ⠄⠄⢿⣿⣷⣨⣽⣭⢁⣡⣿⣿⠟⣩⣿⣿⣿⠿⠿⠟
//  ⠄⠄⠈⡍⠻⣿⣿⣿⣿⠟⠋⢁⣼⠿⠋⠉⠄⠄⠄⠄
//  ⠄⠄⠄⠈⠴⢬⣙⣛⡥⠴⠂⠄⠄⠄⠄⠄⠄⠄⠄⠄...
// (the photo of the famous streamer)

// Input
// Input should contain multiple lines.
// First line indicates the string S ( 1<= length of S <= 103 )
// Second line gives the substring s ( 1<= length of s <= 103 )
// the string contains only lower case a~z.
// Third line contains one integer t ( 1<= t <= 2*106 )
// each of the following t lines gives two integer [l , r], where ( 1<= l <= r <= length of S)

// Output
// For each question, you are asked to print the the number of occurrences of substring s.
// Your program should present a single '\n' at the end of output.

// Sample Input  
// hasahasasaki
// sa
// 3
// 3 9
// 1 4
// 2 3

// Sample Output  
// 2
// 1
// 0

// 2020/07/01 SYC

#include <stdio.h>
#include <stdlib.h>
#define BuffSize 1010

void showArr(int *a, const int start, const int end){
    for(int i = start; i <= end; i++){
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main(){
    char buff[BuffSize] = {0};
    char sub[BuffSize] = {0};
    int record[BuffSize] = {0};
    int buffCount = 0, subSize = 0, t = 0;
    scanf("%s", &(buff[1]));
    scanf("%s", sub);
    // printf("%s\n", buff + 1);
    // printf("%s\n", sub);

    for(int i = 0; i < BuffSize && sub[i] != '\0'; i++){
        subSize++;
    }

    for(int i = 1; i < BuffSize && buff[i] != '\0'; i++){
        buffCount++;
        int isMatch = 1;
        for(int j = 0; j < BuffSize && sub[j] != '\0'; j++){
            // printf("Buff: %c Sub: %c\n", buff[i], sub[j]);
            if(buff[i + j] != sub[j]){isMatch = 0; break;}
        }
        if(isMatch){record[i]++;}
    }
    // showArr(record, 1, buffCount);

    for(int i = 1; i <= buffCount; i++){
        record[i] = record[i - 1] + record[i];
    }
    // showArr(record, 1, buffCount);
    
    scanf("%d", &t);
    for(int i = 0; i < t; i++){
        int l = 0, r = 0;
        scanf("%d %d", &l, &r);

        printf("%d\n", record[r - subSize + 1] - record[l - 1]);
    }

    return 0;
}