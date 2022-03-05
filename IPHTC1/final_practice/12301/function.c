// NTHUOJ 12301 - Uncle Huang choose Tutor(Easy version)   
// Description
// Uncle Huang wants to find a tutor. He has n students to choose from. 
// Students are indexed 1, 2, . . . , n and standing in a circle. 
// Uncle Huang will count every k-th students in clock-wise.  
// The k-th student is going to be chosen but the student will disappear(Nobody knows why!) therefore Uncle Huang will continue his counting and start from the next student.
// The last remaining student will be his tutor.
// Tell Uncle Huang the index of the student who will be his tutor.
// example: If n = 5, k = 7

// Hint: 約瑟夫斯問題(https://zh.wikipedia.org/wiki/%E7%BA%A6%E7%91%9F%E5%A4%AB%E6%96%AF%E9%97%AE%E9%A2%98)
// This problem is partial judge.
// Note: k might be very large, if you just count k students you will get TLE. Try to count less by using mod.

// Input
// The input will end by EOF
// Every testcase only contains two integer n(1<= n <= 1000) and k(1 <= k <= 109)

// Output
// For each testcase print the index of the student who last remaining.
// remember to print \n at the end of every output.

// Sample Input  
// 10 2
// 3 1
// 5 7

// Sample Output  
// 5
// 3
// 4

// Partial Judge Code
// 12301.c

// Partial Judge Header
// 12301.h

#include <stdio.h>
#include <stdlib.h>
#include "function.h"

// typedef struct _Node{
//     int number;
//     struct _Node* next;
// }Node;

// Reference: https://zh.wikipedia.org/wiki/%E7%BA%A6%E7%91%9F%E5%A4%AB%E6%96%AF%E9%97%AE%E9%A2%98
//            https://www.itread01.com/content/1504374014.html
Node *createList(int n){
    Node *res = (Node *)malloc(sizeof(Node));
    res->number = n;
    return res;
}

void freeList(Node* head){
    free(head);
}

int solveJosephus(Node **head, int step){
    int n = (*head)->number;
    // printf("N: %d K: %d\n", n, step);
    // In computing, suppose index starts from 0;
    int s = 0; // Survial of n = 1
    for(int i = 2; i <= n; i++){
        s = (s + step) % i;
    }

    return s + 1; // Index starts from 1
}

// int solveJosephus(Node **head, int step){
//     int n = (*head)->number;
//     // printf("N: %d K: %d\n", n, step);
//     // In computing, suppose index starts from 0;
//     int s = 1; // Survial of n = 1
//     for(int i = 2; i <= n; i++){
//         s = ((s + (step % i) + 1) % i) + 1;
//     }

//     return s; // Index starts from 1
// }