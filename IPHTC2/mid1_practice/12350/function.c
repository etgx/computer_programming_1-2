// IPHTC2 Week3 Problem 3 | NTHUOJ 12350 - Typing   
// Description
// Nderman stole a special typing machine. Because he doesn't like anybody look at him, he can only type to express himself. There're several function that this typing machine has.
// (This problem is partial judge!)

// void insert(Node**, char);
// append one more character char after the cursor. Note that the cursor doesn't move after the appending.

// void deletion(Node**);
// delete one character after the cursor. If you reach the end of the typing, delete nothing.

// void backspace(Node**);
// delete one character before the cursor. If you reach the beginning of the typing, delete nothing.

// void go_left(Node**, int);
// move the cursor to the left for int times. If you reach the beginning of the typing you should go to the end of typing and continue the moves of your cursor.

// void go_right(Node**, int);
// move the cursor to the right for int times. If you reach the end of the typing you should go to the beginning of typing and continue the moves of your cursor.

// void go_home(Node**);
// move the cursor to the beginning of the typing.

// void go_end(Node**);
// move the cursor to the end of the typing

// void show();
// show all the typing.

// Finish all the function except "show()"(we have done it for you).
// (the picture Nderman stealing the typing machine)

// Input
// input contains several lines
// First line will contain one integer n.
// testcase 1 & 2：​1  <= n <= 100
// testcase 3 & 4：500 <= n <= 2000
// Following n lines, each line contains one of the functions.

// Output
// If the function is show you should print all the tpying.

// Sample Input  
// 26
// insert a
// insert b
// insert c
// insert d
// insert e
// insert f
// insert g
// show
// go_right 2
// deletion
// show
// go_right 2
// backspace
// show
// go_left 4
// insert L
// show
// go_right 2
// insert R
// show
// go_home
// insert H
// show
// go_end
// insert E
// show

// Sample Output  
// g f e d c b a 
// g f d c b a 
// g f d b a 
// g f d b a L 
// R g f d b a L 
// H R g f d b a L 
// H R g f d b a L E 

// Partial Judge Code
// 12350.c
// Partial Judge Header
// 12350.h

// 2021/10/07 SYC

#include "function.h"
#include <stdio.h>
#include <stdlib.h>

void insert(Node **cur, char c){
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->character = c;

    Node *next_node = (*cur)->ptr_to_next_node;
    Node *prev_node = (*cur);
    new_node->ptr_to_next_node = next_node;
    new_node->ptr_to_prev_node = prev_node;
    // Insert the new node to the list
    prev_node->ptr_to_next_node = new_node;
    next_node->ptr_to_prev_node = new_node;

    if((*cur) == tail)
        // When the head == tail, redirct the tail to the new node
        tail = new_node;
}

void deletion(Node **cur){
    if((*cur) != tail && (*cur) != NULL){
        Node *delete_node = (*cur)->ptr_to_next_node;
        Node *prev_node = delete_node->ptr_to_prev_node;
        Node *next_node = delete_node->ptr_to_next_node;
        prev_node->ptr_to_next_node = next_node;
        next_node->ptr_to_prev_node = prev_node;

        // When the delete_node == head, redirct the head to the ptr_to_next_node node of the head
        if(delete_node == head)
            head = next_node;
        // When the delete_node == tail, redirct the tail to the previous node of the tail
        if(delete_node == tail)
            tail = prev_node;

        free(delete_node);
    }
}

void backspace(Node **cur){
    if((*cur) != head && (*cur) != NULL){
        Node *delete_node = (*cur);
        Node *prev_node = delete_node->ptr_to_prev_node;
        Node *next_node = delete_node->ptr_to_next_node;
        prev_node->ptr_to_next_node = next_node;
        next_node->ptr_to_prev_node = prev_node;
        (*cur) = prev_node;

        // When the delete_node  == head, redirct the head to the ptr_to_next_node node of the head
        if(delete_node == head)
            head = next_node;
        // When the delete_node  == tail, redirct the tail to the previous node of the tail
        if(delete_node == tail)
            tail = prev_node;

        free(delete_node);
    }
}

void go_left(Node **cur, int t){
    for(int i = 0; i < t; i++){
        *cur = (*cur)->ptr_to_prev_node;
    }
}

void go_right(Node **cur, int t){
    for(int i = 0; i < t; i++){
        *cur = (*cur)->ptr_to_next_node;
    }
}

void go_home(Node **cur){
    (*cur) = head;
}

void go_end(Node **cur){
    (*cur) = tail;
}