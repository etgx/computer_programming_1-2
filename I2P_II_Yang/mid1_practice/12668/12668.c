#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    char c;
    struct node *prev, *next;
}Node;

void init_list(Node **head, Node **tail){
    (*head) = (Node*)malloc(sizeof(Node));
    (*tail) = (Node*)malloc(sizeof(Node));

    (*head)->c = (*tail)->c = 0;
    (*head)->prev = (*tail)->next = NULL;
    (*head)->next = *tail;
    (*tail)->prev = *head;
}

void right(Node **cursor, Node *head, Node *tail){
    if((*cursor) == NULL || head == NULL || tail == NULL) return;
    if((*cursor)->next != tail && (*cursor)->next != NULL) *cursor = (*cursor)->next;
}

void left(Node **cursor, Node *head, Node *tail){
    if((*cursor) == NULL || head == NULL || tail == NULL) return;
    if((*cursor)->prev != NULL) *cursor = (*cursor)->prev;
    // printf("[%c]",(*cursor)->c);
}

void backspace(Node **cursor, Node *head, Node *tail){
    if((*cursor) == NULL || head == NULL || tail == NULL || (*cursor) == head || (*cursor) == tail) return;
    Node *del_node = (*cursor);
    del_node->next->prev = del_node->prev;
    del_node->prev->next = del_node->next;
    // Move forward
    *cursor = del_node->prev;
    free(del_node);
}

void insert(Node **cursor, char c, Node *head, Node *tail){
    if(*cursor == NULL || head == NULL || tail == NULL || (*cursor) == tail) return;
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->c = c;
    new_node->next = (*cursor)->next;
    new_node->prev = (*cursor);

    new_node->next->prev = new_node->prev->next = new_node;
    // Move forward
    *cursor = new_node;
}

void show_list(Node *head, Node *tail){
    Node *temp = head->next;
    for(; temp != tail;){
        printf("%c", temp->c);
        temp = temp->next;
    }
    printf("\n");
}

void free_list(Node **head, Node **tail){
    Node *temp = (*head);
    for(; temp != NULL;){
        Node *del = temp;    
        temp = temp->next;
        free(del);
    }
    (*head) = (*tail) = NULL;
}

int main(){
    int T = 0, N = 0;
    scanf("%d", &T);

    for(int i = 0; i < T; i++){
        scanf("%d\n", &N);
        
        Node *head = NULL, *tail = NULL, *cursor = NULL;
        init_list(&head, &tail);
        cursor = head;
        for(int j = 0; j < N; j++){
            char c = 0;
            scanf("%c", &c);

            switch (c){
                case 'B':
                    backspace(&cursor, head, tail);
                    break;
                case 'L':
                    left(&cursor, head, tail);
                    break;
                case 'R':
                    right(&cursor, head, tail);
                    break;
                default:
                    // Insert
                    insert(&cursor, c, head, tail);
                    break;
            }
        }
        show_list(head, tail);
        free_list(&head, &tail);
    }
    return 0;
}
