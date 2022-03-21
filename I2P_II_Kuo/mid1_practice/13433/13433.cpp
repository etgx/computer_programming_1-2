#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <list>

// Method 1: STD List
// int main(){
//     int T = 0, N = 0;

//     scanf("%d\n", &T);
//     for(int i = 0; i < T; i++){
//         scanf("%d\n", &N);
//         // std::list<int> seq(1, 0);
//         std::list<int> seq = {0};
//         std::list<int>::iterator it = seq.begin();
//         // it++;

//         for(int j = 1; j <= N; j++){
//             char s_i = 0;
//             scanf("%c", &s_i);

//             if(s_i == 'R'){
//                 it++;
//             }

//             seq.insert(it, j);
//             it--;
//         }

//         for(std::list<int>::iterator it = seq.begin(); it != seq.end(); it++){
//             printf("%d ", *it);
//         }
//         printf("\n");
//     }
//     return 0;
// }

// Method 2: Implement Doubly Linked List
typedef struct node{
    int x;
    struct node *next, *prev;
}Node;

class DoublyList{
    private:
    Node *head = NULL, *tail = NULL, *temp = NULL;

    Node* create_node(int x, Node *prev, Node* next){
        Node *new_node = (Node*)malloc(sizeof(Node));
        new_node->x = x;
        new_node->prev = prev;
        new_node->next = next;
        return new_node;
    }

    void init(){
        this->head = this->create_node(0, this->tail, this->tail);
        this->tail = this->create_node(0, this->head, this->head);
    }

    Node* insert_between(int x, Node *prev, Node *next){
        Node *new_node = this->create_node(x, prev, next);
        prev->next = next->prev = new_node;
        return new_node;
    }

    public:
    DoublyList(int i){
        this->init();
        this->insert_between(i, this->head, this->tail);
        this->temp = this->head->next;
    }

    ~DoublyList(){
        for(Node *temp = this->head->next; temp != this->tail;){
            Node *del_node = temp;
            temp = temp->next;
            free(del_node);
        }

        this->head->next = this->tail;
        this->tail->prev = this->head;
    }

    Node* insert_right(int x){
        Node *new_node = this->insert_between(x, this->temp, this->temp->next);
        this->temp = new_node;
        return new_node;
    }

    Node* insert_left(int x){
        Node *new_node = this->insert_between(x, this->temp->prev, this->temp);
        this->temp = new_node;
        return new_node;
    }

    void show(){
        for(Node *temp = this->head->next; temp != this->tail; temp = temp->next){
            printf("%d ", temp->x);
        }
        printf("\n");
    }
};

int main(){
    int T = 0, N = 0;

    scanf("%d\n", &T);
    for(int i = 0; i < T; i++){
        scanf("%d\n", &N);
        DoublyList circular_list = DoublyList(0);

        for(int j = 1; j <= N; j++){
            char s_i = 0;
            scanf("%c", &s_i);

            if(s_i == 'L'){
                circular_list.insert_left(j);
            }else if(s_i == 'R'){
                circular_list.insert_right(j);
            }
        }
        circular_list.show();
    }
    return 0;
}