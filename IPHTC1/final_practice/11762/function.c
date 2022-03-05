// NTHUOJ 11762 - E - Reverse Linked List   
// Description
// Writer: jjjjj19980806       Description: pclightyear        Difficulty: ★☆☆☆☆
// Given a linked list, you have to reverse it and output the result.
// You have to implement four function:
// 1. Node* Create_List(Node*, int);
// This function is used to create the linked list according to the input.
// 2. Node* Reverse_List(Node*);
// This function is used to reverse the given linked list.
// 3. void Print_List(Node*);
// This function is used to print out the key value in the linked list.
// 4. void Free_List(Node*);
// This function is used to free the memory space.

// Input
// The first line contains one integer n, representing the number of nodes in the linked list.
// The next lines contains n integers, each integer represents a node in the linked list.
// It is guaranteed that :
// 1 ≤ n ≤ 10
// 0 ≤ ai ≤ 100

// Output
// You need to output the reversed linked lists.
// Each key value is separated by "->".

// Sample Input  
// 3
// 1 2 3

// Sample Output  
// 3->2->1

// Partial Judge Code
// 11762.c

// Partial Judge Header
// 11762.h

// #include<stdio.h>
// #include<stdlib.h>
#include"function.h"

// typedef struct _Node {
//     int data;
//     struct _Node *next;
// } Node;

Node* Create_List(Node* head, int data){
    if(head == NULL){
        // If Head is NULL, add first Node of list
        head = (Node *)malloc(sizeof(Node));
        head->data = data;
        head->next = NULL;
        // printf("add FIRST Node with data: %d\n", head->data);
    }else{
        // Find last Node(->next == NULL)
        Node *temp = head;
        while(temp->next != NULL){
            temp = temp->next;
        }
        // Set up new Node
        temp->next = (Node *)malloc(sizeof(Node));
        temp->next->data = data;
        temp->next->next = NULL;
        // printf("add Node with data: %d\n", temp->next->data);
    }
    return head;
}

Node* Reverse_List(Node* head){
    // Confirm head is not NULL
    if(head == NULL){return NULL;}

    int buff[105] = {0};
    int n = 0; // The number of Nodes
    Node *temp = head;

    // Store list in an array
    while(temp != NULL){
        buff[n] = temp->data;
        temp = temp->next;
        n++;
    }

    // Reverse store back to list
    temp = head;
    for(int i = n - 1; i >= 0; i--){
        temp->data = buff[i];
        temp = temp->next;
    }

    return head;
}

void Print_List(Node* head){
    // Confirm head is not NULL
    if(head == NULL){return;}

    printf("%d", head->data);

    Node *temp = head->next;
    while(temp != NULL){
        printf("->%d", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void Free_List(Node* head){
    // Confirm head is not NULL
    if(head == NULL){return;}

    Node *del = head;
    while(del != NULL){
        head = del->next;
        free(del);
        del = head;
    }
}