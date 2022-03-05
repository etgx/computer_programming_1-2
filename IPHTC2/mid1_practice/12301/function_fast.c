// IPHTC2 Week3 Problem 2 | NTHUOJ 12301
// Uncle Huang choose Tutor(Easy version)
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

// Sample Input 1 

// 10 2
// 3 1
// 5 7

// Sample Output 1

// 5
// 3
// 4

// The struct of Node.

// struct _Node{
//     int number;
//     struct _Node* next;
// };
// The main function

// int main()
// {
//     int n, k;
//     while( scanf("%d%d", &n, &k)!=EOF )
//     {
//         Node *head;
//         head = createList(n);
//         printf( "%d\n", solveJosephus(&head, k) );
//         freeList(head);
//     }
//     return 0;
// }

#include "function.h"
#include <stdio.h>
#include <stdlib.h>

Node *createList(int n){
    Node *list = (Node*)malloc(sizeof(Node) * n);
    list[0].number = n;
    return list;
}

void freeList(Node* head){
    free(head);
}

int josephus_for(int n, int k){
    // The index should start from 0, otherwisw, the modular arithemetic would encouter some errors
    int survivor = 0;
    // Start from n = 2
    for(int i = 2; i <= n; i++){
        // The last survivor of (n, k) is (n - 1, k) % n, since we need to remove 1 person and shift the original index right with k.
        // Then, take modular to avoid the index exceed n
        survivor = (survivor + k) % i;
    }
    // Recompute the survivor from index = 1
    return survivor + 1;
}

int josephus_recursive(int n, int k){
    if(n == 1){
        return 1;
    }else{
        // We should start counting from 0 to avoid the edge case like n = k
        // So, we need to mnius 1 to make the index count from 0, and then, plus 1 to recover to correct order.
        return (josephus_recursive(n - 1, k) + k - 1) % n + 1;
    }
}

int solveJosephus(Node **head, int step){
    // return josephus_recursive((*head)->number, step);
    return josephus_for((*head)->number, step);
}
