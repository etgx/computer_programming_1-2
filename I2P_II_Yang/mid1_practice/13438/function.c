#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

void show_list(){
    if(head == NULL) return;
    
    Node *temp = head->next;
    if(temp != NULL){
        printf("%d", temp->number);
        temp = temp->next;
    }

    for(; temp != NULL;){
        printf(" %d", temp->number);
        temp = temp->next;
    }
    printf("\n");
}

Node* createList(int n){
    // Dummy head
    Node *tail = NULL, *dummy_head = NULL;
    dummy_head = tail = (Node*)malloc(sizeof(Node));
    dummy_head->number = 0;
    dummy_head->next = dummy_head->prev = NULL;

    for(int i = 1; i <= n; i++){
        Node *new_node = (Node*)malloc(sizeof(Node));
        new_node->number = i;
        new_node->next = new_node->prev = NULL;

        tail->next = new_node;
        new_node->prev = tail;

        tail = new_node;
    }

    head = dummy_head;
    show_list();
    return dummy_head;
}

Node *remove_node(Node *node){
    if(node == NULL || node == head) return NULL;

    if(node->next != NULL){node->next->prev = node->prev;}
    node->prev->next = node->next;
    
    return node;
}

void insert_node(Node *pos, Node *node){
    if(node == NULL || pos == NULL || node == head) return;

    node->next = pos->next;
    node->prev = pos;

    if(pos->next != NULL){pos->next->prev = node;}
    pos->next = node;
}

void move(Node *pos, Node *node){
    // When pos = node, they are both the tail of the list
    if(pos == node) return;

    remove_node(node);
    insert_node(pos, node);
}

void solve(int n, int m){
    if(head == NULL) return;

    for(int i = 0; i < m; i++){
        int A = 0, K = 0;
        scanf("%d %d", &A, &K);

        Node *temp = head, *target = NULL, *new_pos = NULL;

        for(int i = 0; i < A && temp != NULL; i++){
            temp = temp->next;
        }
        target = temp;

        for(int i = 0; i < K && temp != NULL; i++){
            if(temp->next == NULL) break;
            temp = temp->next;
        }

        // printf("Insert: %d -> %d: ", temp->number, target->number);
        // show_list();

        move(temp, target);

        show_list();
    }
}