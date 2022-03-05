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