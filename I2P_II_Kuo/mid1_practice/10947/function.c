// I2P - Kuo Week0 Problem 1 | NTHUOJ 10947 - delete linked list   
// This problem will give you a sequence of positive integers.  Use this sequence to create a linked list to store those integers.  Next, the problem will give you another sequence of positive integers, p0, p1,…pk-1.  Delete the nodes in the position at p0, p1, …pk-1 of the linked list, where 1<=p0<p1<…pk-1<=N. If the node is not existing,do nothing. And show the final results.
// For example, if the first sequence is 1, 2, 3, 4, 5, 6,7, a linked list is created as
// If the second sequence is 1, 1, 4, do the follows.
// After p1=1, the list becomes
// because the first node is 1.  After p2 = 1, the list becomes
// because the first node is 2.  After p3 = 4, the list becomes
// because the fourth node is 6.
// The framework of the program is provided.
// Create a linked list from the input  (createList)
// while there are still some data pi
//     read in pi 
//     delete node at pi  (deleteNode)
// print the remaining list (printList)
// free the list (freeList)
// You will be provided with main.c and function.h. main.c contains the implementation of function printList, and freeList, and function.h contains the definition of node and the interface of createList(&head) and deleteNode(&head, pi).  You only need to implement createList(&head) and deleteNode(&head, pi) in function.c, in which head is the head of the linked list, and pi is the node at pi to be deleted.
// You will be provided with main.c and function.h, and asked to implement function.c.
// For OJ submission:
//        Step 1. Submit only your function.c into the submission block. (Please choose c compiler) 
//        Step 2. Check the results and debug your program if necessary.

// main.c

// #include <stdio.h>
// #include <stdlib.h>
// #include "function.h"

// void printList(Node *head){
//     Node *temp;
//     for(temp = head; temp!=NULL; temp=temp->next) {
//         printf("%d ", temp->data);
//     }
// }

// void freeList(Node *head){
//     Node *temp;
//     for(temp=head; temp!=NULL; temp=head){
//         head = head->next;
//         free(temp);
//     }
// }

// int main()
// {
//     Node *head;
//     int data;

//     head = createList();

//     while(1){
//         scanf("%d", &data);
//         if(data>-1){
//             deleteNode(&head,data);
//         }else break;

//     }

//     printList(head);
//     freeList(head);
//     return 0;
// }


// function.h

// #include <stdlib.h>
// #include <stdio.h>

// typedef struct _Node {
//     int data;
//     struct _Node *next;
// } Node;

// void deleteNode(Node ** nd, int data);
// Node* createList();

// Input
// The input contains 2 sequence of positive integers as the linklist and the order, except the last one, which is -1, indicating the end of the sequence. 

// Output
// The output contains the sequence of resulting linklist.

// Sample Input  

// 1 2 3 4 5 6 7 -1
// 1 1 4 -1

// Sample Output  

// 3 4 5 7 

#include "function.h"

void deleteNode(Node ** nd, int data){
    if(data == 1){
        Node *temp = *nd;
        *nd = (*nd)->next;
        free(temp);
    }else{
        Node *prev_del = *nd;
        for(int i = 0; i < data - 2; i++){
            prev_del = prev_del->next;
            if(prev_del->next == NULL){
                return;
            }
        }
        Node *del = prev_del->next;
        prev_del->next = prev_del->next->next;
        free(del);
    }
}

Node* createList(){
    // Head
    Node *temp = NULL, *head = NULL;

    int input = 0;
    scanf("%d", &input);

    while(input != -1){
        Node *new_node = (Node*)malloc(sizeof(Node));
        new_node->data = input;
        new_node->next = NULL;
        if(temp == NULL){
            temp = new_node;
            head = temp;
        }else{
            temp->next = new_node;
            temp = temp->next;
        }

        scanf("%d", &input);
    }

    return head;
}