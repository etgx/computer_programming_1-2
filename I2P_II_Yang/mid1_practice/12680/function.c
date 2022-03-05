// I2P - Yang Week1 Problem 2 | NTHUOJ 12680 - Card Magic
// Description
// Mr. Lu is a famous magician. There’s a poker magic tutorial on his youtube channel.
// There’re N stacks of cards on the table at begining.
// And then, Mr. Lu make M actions on these card stacks.
// There’s only two kinds of actions Merge and Cut:

// Merge x y: put the x-th card stack on the top of y-th card stack.
// Cut x i: cut the x-th card stack into two stacks. One is the card stack contains ( 1~i )-th cards of original stack. The other one is the remaining. The former’s index will be x, the latter’s will be (x+1)
// The indexes of stacks and cards will be changed after Merge and Cut.
// For example:

// As a lazy CS student, you only focus on the result.
// Therefore, you decide to write a program to compute the final state of card stacks.

// It’s partial judge for this problem.
// Please download the code at the bottom to see the interface and main function.
// You have to implement a data structure like below:


// Input
// Two integer N,M on the first line.
// For each of the next N lines, there’re several integers Ni and Ci,1,Ci,2...Ci,Ni.
// Ni means the number of cards in the i-th stack.
// Ci,j denotes the j-th card of i-th stack.
// The folloing M lines contains one action per line.
// Every Action is one of “Merge x y” or “Cut x i”.

// It’s guaranteed that:
// 1 ≤ N, M ≤ 9000
// ∑ Ni ≤ 4∗104
// Ci,j is non-negative integer.
// In “Merge x y” action:
// the x, y-th stacks always exist.
// x is not equal to y.
// In “Cut x i” action:
// the x-th stack always exists.
// i is always between 1 and Nx - 1.
// There’s at least 1 card in each card stack.

// Output
// Print the card stacks by the order of index.
// One line for one card stack.
// Please refer to the sample input/output for the precise format.
// There is a ‘\n’ at the end of each line.

// Sample Input  

// 4 3
// 4: 1 2 3 4
// 2: 8 7
// 2: 5 6
// 1: 9
// Merge 4 2
// Cut 1 2
// Cut 3 1

// Sample Output  

// 1 2
// 3 4
// 8
// 7 9
// 5 6


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

Node* ReadOneList(){
    int *stack = NULL, stack_size = 0;
    scanf("%d: ", &stack_size);
    stack = (int*)malloc(sizeof(int) * stack_size);
    for(int i = 0; i < stack_size; i++){
        scanf("%d", &(stack[i]));
    }

    Node *node = (Node*)malloc(sizeof(Node));
    node->data = stack;
    node->size = stack_size;
    node->next = NULL;

    return node;
}

void PrintList(Node* head){
    Node *temp = head->next;
    for(; temp != NULL; temp = temp->next){
        printf("%d", temp->data[0]);
        for(int i = 1; i < temp->size; i++){
            printf(" %d", temp->data[i]);
        }
        printf("\n");
    }
}

void Merge(Node* head, int x, int y){
    // Merge x stack to y stack
    int x_stack_len = 0, y_stack_len = 0, merge_stack_len = 0;
    Node *x_node = head->next, *y_node = head->next, *del_prev = head;

    for(int i = 1; i < x; i++){
        x_node = x_node->next;
        del_prev = del_prev->next;
    }
    for(int i = 1; i < y; i++){
        y_node = y_node->next;
    }
    x_stack_len = x_node->size;
    y_stack_len = y_node->size;
    merge_stack_len = x_stack_len + y_stack_len;

    // Copy stacks
    // printf("x_stack: %d, y_stack: %d => merge: %d\n", x_stack_len, y_stack_len, merge_stack_len);
    int *merge_stack = (int*)malloc(sizeof(int) * merge_stack_len);
    memcpy(merge_stack, y_node->data, sizeof(int) * y_stack_len);
    memcpy(&(merge_stack[y_stack_len]), x_node->data, sizeof(int) * x_stack_len);
    // printf("Merge: [%d %d %d]\n", merge_stack[0], merge_stack[1], merge_stack[2]);

    // Free useless stacks
    free(x_node->data);
    free(y_node->data);
    y_node->data = merge_stack;
    y_node->size = merge_stack_len;

    // Free useless x_node
    del_prev->next = x_node->next;
    free(x_node);
}

void Cut(Node* head, int x, int y){
    int new_x_stack_len = 0, new_stack_len = 0;
    Node *x_node = head->next, *new_node = (Node*)malloc(sizeof(Node));

    // Move to target x_node
    for(int i = 1; i < x; i++){
        x_node = x_node->next;
    }
    new_x_stack_len = y;
    new_stack_len = x_node->size - y;

    // Allocate new memory
    int new_x_stack_byte = sizeof(int) * new_x_stack_len, new_stack_byte = sizeof(int) * new_stack_len;
    int *new_x_stack = (int*)malloc(new_x_stack_byte), *new_stack = (int*)malloc(new_stack_byte);

    // Copy data to new array
    memcpy(new_x_stack, x_node->data, new_x_stack_byte);
    memcpy(new_stack, &(x_node->data[new_x_stack_len]), new_stack_byte);

    // Free the old array
    free(x_node->data);

    // Update the new address and the length
    x_node->data = new_x_stack;
    x_node->size = new_x_stack_len;
    new_node->data = new_stack;
    new_node->size = new_stack_len;

    // Insert to list
    new_node->next = x_node->next;
    x_node->next = new_node;
}