// I2P - Kuo Week1 Problem 1 | NTHUOJ 13129 - prize!   
// Description
// There are n people, numbered 1 to n, in a circle and arranged in clockwise. They are playing a game, kth lucky people can get the prize.
// The following are rules of the game:
// 1. Each prize has a lucky number.
// 2. Who count the lucky number can get a prize.
// 3. If the lucky number is odd, count clockwise.
// 4. If the lucky number is even, count counterclockwise.
// 5. The student that gets prize will leave the circle.
// 6. After someone leave the circle, if the new lucky number is odd, count from the next person, otherwise count from the previous person.

// For example: 
// n = 8
// m = 3
// lucky number = 3 4 5

// The sequence of getting prize is:
// 1 2 3
// 2 1 8 7
// 8 1 2 4 5
// Then people 3, 5, 7 can get the prize.
// Please use doubly circular linked list to solve this problem.

// Input
// The first line has two integer n and k, where n is the number of total people, and k is the number of prizes.
// The second line has k positive number a1 ~ ak.
// testcases:
// 1. 1 <= k <= n <= 10000, 1 <= ak <= n
// 2. 1 <= k <= n <= 10000, 1 <= ak <= n
// 3. 1 <= k <= n <= 10000, 1 <= ak <= n
// 4. 1 <= k <= n <= 1000000, 1 <= ak <= 10000000, n*k <= 300000000
// 5. 1 <= k <= n <= 1000000, 1 <= ak <= 10000000, n*k <= 300000000
// 6. 1 <= k <= n <= 1000000, 1 <= ak <= 10000000, n*k <= 300000000

// Output
// The output has k lines, each line contains a number: who can get the prize.

// Sample Input  

// sample input 1
// 8 3
// 3 4 5


// sample input 2
// 7 5
// 3 3 3 3 3

// Sample Output  

// sample output 1
// 3
// 7
// 5


// sample output 2
// 3
// 6
// 2
// 7
// 5

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

void show(){
    if(head != NULL){
        Node *temp = head;
        printf("%d ", temp->number);
        temp = temp->next;
        for(;temp != head && temp != NULL; temp = temp->next){
            printf("%d ", temp->number);
        }
    }
    printf("\n");
}

Node* createList(int n){
    Node *tail = head = (Node*)malloc(sizeof(Node));
    tail->number = 1;
    tail->next = tail;
    tail->prev = tail;

    for(int i = 2; i <= n; i++){
        Node *new_node = (Node*)malloc(sizeof(Node));
        new_node->number = i;
        new_node->next = tail->next;
        new_node->prev = tail;
        tail->next = new_node;
        head->prev = new_node;

        tail = new_node;
    }
    //printf("All: ");
    //show();

    return head;
}

int del(Node *node){
    // Handling the edge cases
    // If node is NULL
    if(node == NULL || head ==NULL) return 0;

    // If delete the head node
    if(node == head){
        head = head->next;
    }

    // If delete the only one remaining node.
    if(node->next == node){
        head = NULL;
    }else{
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    free(node);
    return 1;
}

void solveJosephus(int n, int k){
    //printf("Hello N: %d, K: %d\n", n, k);
    Node *temp = head, *last_del = NULL;
    int current_n = n;
    for(int i = 0; i < k; i++){
        int mod = 0, lucky_num = 0, dir = 0;
        scanf("%d", &lucky_num);
        // Decide to go forward or go back
        dir = lucky_num % 2;
        // Index from 0
        lucky_num--;
        // printf("Temp at %d\n", temp->number);

        if(last_del != NULL){
            // If delete some node, shift the temp pointer
            if(dir == 1){
                // Odd lucky number
                temp = temp->next;
            }else if(dir == 0){
                // Even lucky number
                temp = temp->prev;
            }

            del(last_del);
            current_n--;
        }

        // You should compute the modulo after reducing the length of the linked list.
        mod = lucky_num % current_n;

        // Because we index the node from 1, when mod == 0, it actually ask to remove the node before temp.
        for(int j = 0; j < mod; j++){
            if(dir){
                temp = temp->next;
            }else{
                temp = temp->prev;
            }
        }
        last_del = temp;
        // printf("Lucky Number: %d, Mod: %d, DEL: %d\n", lucky_num, mod, temp->number);
        // printf("Remain: ");
        // show();
        printf("%d\n", temp->number);
    }
}
