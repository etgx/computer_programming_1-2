// IPHTC2 Week3 Problem 2 | NTHUOJ 12301 - Uncle Huang choose Tutor(Easy version)
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

// 2021/10/07 SYC

#include "function.h"
#include <stdio.h>
#include <stdlib.h>

Node *createList(int n){
    Node *head = NULL;
    Node *tail = NULL;
    for(int i = n; i > 0; i--){
        // From tail to head
        Node *new_node = (Node*)malloc(sizeof(Node));
        new_node->number = i;
        new_node->next = head;
        head = new_node;
        if(i == n)
            tail = new_node;
    }
    if(tail != NULL)
        tail->next = head;
    return head;
}

void freeList(Node* head){
    if(head != NULL)
        free(head);
}

int solveJosephus(Node **head, int step){
    Node *kill_node = (*head);
    Node *prev_kill_node = NULL;
    Node *tail = (*head);
    int len = 1, mod_step = 0;

    // Calculate length and the tail
    while(tail->next != (*head)){
        tail = tail->next;
        len++;
    }
    prev_kill_node = tail;
    // printf("Len: %d\n", len);

    while(kill_node->next != kill_node){
        // Because the first one is 1, the next one is 2..., thus the pointer only need to move forward (step - 1) times.
        mod_step = (step - 1) % len;
        // printf("Mod_step: %d, len: %d\n", mod_step, len);

        for(int i = 0; i < mod_step; i++){
            prev_kill_node = kill_node;
            kill_node = kill_node->next;
            // printf("Count: %d, Num: %d, Prev Num: %d\n", i+1, kill_node->number, prev_kill_node->number);
        }
        prev_kill_node->next = kill_node->next;
        if(kill_node == (*head)){
            (*head) = kill_node->next;
        }
        if(kill_node == tail){
            tail = prev_kill_node;
        }
        free(kill_node);
        kill_node = prev_kill_node->next;
        len--;
    }
    return kill_node->number;
}
