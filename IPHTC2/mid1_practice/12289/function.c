// IPHTC2 Week2 Problem 3 | NTHUOJ 12289 - after rain
// Description
// After rain comes sunshine and rainbow.
// 5/17 is the International Day Against Homophobia, Transphobia and Biphobia(國際不再恐同日), which is also the day that legislative committees trial the special law about LGBT. They eventually pass a draft that fully in line with the referendum, which make Taiwan be the first Asia country that pass a law for LGBT.
// Knuckles is on his way of finding his queen. When he arrived Taiwan and see a lot of rainbow flags, he wondered that these rainbow flags might be a clue of the location of his queen. He will give some operations about these flags, you are going to help him, or he'll spit on you.
// There are colors on these flags. The colors include: "Red", "Orange", "Yellow", "Green", "Blue", "Purple", which are the color of rainbow.
// Knuckles has a sequence of colors. Initially, the sequence is empty.
// Knuckles has several operations: insert, erase1, erase2, reverse, show.
// insert <color> <dest>: means insert <color> after the location of <dest>. For example, insert Yellow 5 means insert a "Yellow" after the 5-th location. If <dest> is larger than the length of the sequence, just regard it as the last location of the sequence.
// erase1 <dest>: means erase the color locates at <dest>. For example, erase1 4 will erase the 4-th color in the sequence. If <dest> is larger than the length of the sequence, just regard it as the last location of the sequence.
// erase2 <color>: means erase all <color> in the sequence. For example, erase2 Purple will erase all the "Purple" in the sequence. After the operation, There should be no "Purple" in the sequence.
// reverse <dest1> <dest2>: means reverse the elements from dest1> to <dest2>. If the order was originally {"Yellow", "Purple", "Blue"}, after reversing, the order should become {"Blue", "Purple", "Yellow"}. If <dest1> or <dest2> is larger than the length of the sequence, just regard it as the last location of the sequence.
// show: show the sequence according to the order.
// You are going to implement a linked list that support these operations. We have implemented show operation, what you have to do is to implement the remaining operations: insert, erase1, erase2, reverse.
// If you have further questions, please reference to the sample I/O.

// Input
// The first line contains an integer n, indicates the number of operations.
// There are n lines below. Each line contains one operations described above.
// <color> will only appear the 6 colors described above.
// insert: 0 <= <dest> <= 10000
// erase1: 1 <= <dest> <= 10000
// reverse: 1 <= <dest1>, <dest2> <= 10000
// 1 <= n <= 5000

// Output
// When show operation is called, you should output the correct sequence after operating.

// Sample Input 1 
// 15
// insert Red 0
// insert Blue 10
// show
// insert Purple 1
// insert Blue 3
// insert Blue 1
// show
// erase1 3
// show
// insert Yellow 4
// insert Purple 6
// reverse 3 5
// show
// erase2 Blue
// show

// Sample Output 1
// Red Blue 
// Red Blue Purple Blue Blue 
// Red Blue Blue Blue 
// Red Blue Yellow Blue Blue Purple 
// Red Yellow Purple 

// 2021/09/27 SYC

#include "function.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

void insert(Node** head, char* color, int dest){ // insert <color> <dest>
    Node *new_node = (Node*)malloc(sizeof(Node)), *temp = (*head);
    strncpy(new_node->color, color, sizeof(new_node->color));
    new_node->next = NULL;

    for(int i = 0; i < dest; i++){
        if(temp->next == NULL)
            break;
        temp = temp->next;
    }

    new_node->next = temp->next;
    temp->next = new_node;
}

void erase1(Node** head, int dest){ // erase1 <dest>
    Node *temp = (*head);
    Node *delete_node = temp->next;

    // Return if the list is empty
    if(delete_node == NULL)
        return;
    // Move to next node
    for(int i = 1; i < dest; i++){    
        if(delete_node->next == NULL)
            break;
        temp = temp->next;
        delete_node = delete_node->next;
    }
    // Remove deleting mode from list
    temp->next = delete_node->next;
    free(delete_node);
}

void erase2(Node** head, char* color){ // erase2 <color>
    Node *temp = (*head);
    Node *delete_node = temp->next;
    while(delete_node != NULL){
        Node *next_to_delete = delete_node->next;

        if(strcmp(delete_node->color, color) == 0){
            // Remove deleting mode from list
            temp->next = next_to_delete;
            free(delete_node);
            // Move the checking pointer to the next node
            delete_node = next_to_delete;
        }else{
            // If the current node doesn't need to be deleted, move to next one
            temp = temp->next;
            delete_node = delete_node->next;
        }
    }
}

void reverse(Node** head, int dest1, int dest2){ // reverse <dest1> <dest2>
    // Record the real size of the sequence to be revesed
    int real_len = 1;
    const int sizeof_color = sizeof((*head)->color);

    // Move the start_node to the dest1
    Node *start_node = (*head);
    for(int i = 0; i < dest1; i++){
        if(start_node->next == NULL)
            break;
        start_node = start_node->next;
    }

    // Move the end_node to the dest2
    Node *end_node = start_node;
    for(int i = dest1; i < dest2; i++){
        if(end_node->next == NULL)
            break;
        end_node = end_node->next;
        real_len++;
    }
    
    // Create an array to store colors
    char **cache_colors = (char**)malloc(sizeof(char*) * real_len);
    for(int i = 0; i < real_len; i++){
        cache_colors[i] = (char*)malloc(sizeof(char) * sizeof_color);
        memset(cache_colors[i], 0, sizeof_color);
    }

    // Store colors in order
    Node *temp_node = start_node;
    for(int i = 0; i < real_len; i++){
        strncpy(cache_colors[i], temp_node->color, sizeof_color);
        temp_node = temp_node->next;
    }
    temp_node = start_node;
    // Copy colors to the list in reverse order
    for(int i = real_len - 1; i >= 0; i--){
        strncpy(temp_node->color, cache_colors[i], sizeof_color);
        temp_node = temp_node->next;
    }
    // Free the color array and pointer to the array
    for(int i = 0; i < real_len; i++){
        free(cache_colors[i]);
    }
    free(cache_colors);
}