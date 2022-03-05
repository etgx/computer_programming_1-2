// I2P - Kuo Week1 Problem 3 | NTHUOJ 13435 - Longest path on a tree   
// Description
// Mr. Kuo is an adventurer. One day, he finds a maze.
// The maze has N rooms. There may be tunnel between rooms.
// There are exactly one simple path between any two different rooms. That is, the maze is a "tree".
// Mr. Kuo is curious about the length of the longest path in this maze. 
// Take the sample test as the example：
// The longest path of the 1st test case is (2 → 1 → 3), whose length is 2.
// The longest path of the 2nd test case is (1 → 2 → 3), whose length is 2.
// The longest path of the 3rd test case is (5 → 7 → 3 → 1 → 4 → 2), whose length is 5.

// Input
// The first line contains one integer T — the number of test cases. Description of the test cases follows.
// The first line of each test cases contains an integer N — the number of rooms in the maze.
// Each of the next_adjacent N - 1 lines contains two integers u_i and v_i — there is a tunnel between ui and vi.
// For each test：
// T ≤ 10, N ≤ 10
// T ≤ 10, N ≤ 100
// T ≤ 10, N ≤ 500
// T ≤ 10, N ≤ 1000
// T ≤ 10, N ≤ 10000
// T ≤ 30, N ≤ 20000
 

// Output
// For each test case print an integer — the length of the longest path in the maze.

// Sample Input  

// 3
// 3
// 1 2
// 1 3

// 3
// 2 1
// 3 2

// 8
// 2 4
// 5 7
// 6 4
// 4 1
// 1 3
// 7 3
// 3 8

// Sample Output  

// 2
// 2
// 5

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PARAM_N 2
#define DIS_MODE 3

typedef struct node{
    int x;
    int dis_from_root[DIS_MODE];
    struct node *adjacent, *next_adjacent;
}Node;

void print_intention(int iten){
    for(int i = 0; i < iten; i++){
        printf("-");
    }
}

void print_tree(Node *root){
    if(root == NULL) return;
    printf("[%d] -> ", root->x);
    Node *temp = root->adjacent;
    for(; temp != NULL;){
        printf("[%d] ", temp->x);
        temp = temp->next_adjacent;
    }
    printf("\n");

    temp = root->adjacent;
    for(; temp != NULL;){
        print_tree(temp);
        temp = temp->next_adjacent;
    }
}

void add_adjacent(Node *target, Node *adjacent){
    if(target->adjacent == NULL){
        target->adjacent = adjacent;
    }else{
        Node *temp = target->adjacent;
        for(; temp->next_adjacent != NULL;){
            temp = temp->next_adjacent;
        }
        adjacent->next_adjacent = temp->next_adjacent;
        temp->next_adjacent = adjacent;
    }
}

void add_adjacent_both(Node *a, Node *b){
    add_adjacent(a, b);
    add_adjacent(b, a);
}

Node* init_new_node(int x){
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->x = x;
    for(int i = 0; i < DIS_MODE; i++){
        new_node->dis_from_root[i] = 0;
    }
    new_node->adjacent = new_node->next_adjacent = NULL;
    return new_node;
}

void add_node(int a, int b, Node **head, Node **map){
    int ab[PARAM_N] = {a, b};
    for(int i = 0; i < PARAM_N; i++){
        if(map[ab[i]] == NULL){
            Node *new_node = init_new_node(ab[i]);
            map[ab[i]] = new_node;
        }
    }

    if(*head == NULL){
        *head = map[a];
    }

    add_adjacent_both(map[a], map[b]);
}

typedef struct queue_struct{
    Node *node;
    struct queue_struct *next, *prev;
}QueueStruct;

void show_queue(QueueStruct *head, QueueStruct *tail){
    QueueStruct *temp = head->next;
    printf("Queue: ");
    for(; temp != tail;){
        printf("[%d] -> ", temp->node->x);
        temp = temp->next;
    }
    printf("\n");
}

void init_queue(QueueStruct **head, QueueStruct **tail){
    *head = (QueueStruct*)malloc(sizeof(QueueStruct));
    *tail = (QueueStruct*)malloc(sizeof(QueueStruct));

    // Set up head
    (*head)->node = NULL;
    (*head)->prev = NULL;
    (*head)->next = *tail;
    // Set up tail
    (*tail)->node = NULL;
    (*tail)->prev = *head;
    (*tail)->next = NULL;
}

void enqueue(QueueStruct *head, QueueStruct *tail, Node *node){
    QueueStruct *new_struct = (QueueStruct*)malloc(sizeof(QueueStruct));
    new_struct->node = node;
    new_struct->prev =  tail->prev;
    new_struct->next =  tail;

    tail->prev->next = new_struct;
    tail->prev = new_struct;
}

Node *dequeue(QueueStruct *head, QueueStruct *tail){
    if(head->next == tail) return NULL;
    QueueStruct *del_struct = head->next;
    Node *ret_node = del_struct->node;

    head->next->next->prev = head;
    head->next = head->next->next;
    free(del_struct);

    return ret_node;
}

Node *peek(QueueStruct *head, QueueStruct *tail){
    if(head->next == tail) return NULL;
    else return head->next->node;
}

int is_queue_empty(QueueStruct *head, QueueStruct *tail){
    if(head->next == tail) return 1;
    else return 0;
}

Node *find_farthest(Node *root, int dis_mode){
    if(root == NULL) return NULL;

    // Queue
    int dis_from_root = 1;
    QueueStruct *head = NULL, *tail = NULL;
    root->dis_from_root[dis_mode] = dis_from_root;
    init_queue(&head, &tail);
    enqueue(head, tail, root);

    // printf("(%d) ENQUEUE ROOT ", dis_from_root);
    // show_queue(head, tail);

    // BFS
    Node *temp = NULL;
    for(; !is_queue_empty(head, tail);){
        temp = dequeue(head, tail);
        dis_from_root = temp->dis_from_root[dis_mode] + 1;
        Node *temp_adj = temp->adjacent;

        // printf("(%d) DEQUEUE HEAD ", dis_from_root);
        // show_queue(head, tail);
        
        // Enqueue adjacent nodes
        for(; temp_adj != NULL;){
            if(temp_adj->dis_from_root[dis_mode] <= 0){
                temp_adj->dis_from_root[dis_mode] = dis_from_root;
                enqueue(head, tail, temp_adj);
                
                // printf("(%d) ENQUEUE ADJ ", dis_from_root);
                // show_queue(head, tail);
            }
            temp_adj = temp_adj->next_adjacent;
        }

        // printf("=================\n");
    }

    return temp;
}

int get_longest_path(Node **root){
    // printf("Find SRC\n");
    Node *src = find_farthest(*root, 0);
    // printf("Find DEST\n");
    Node *dest = find_farthest(src, 1);
    return dest->dis_from_root[1] - 1;
}

void del_tree(Node **head){
    if(*head == NULL) return;
    const int dis_mode = 2;

    // Mark as traversed
    (*head)->dis_from_root[dis_mode] = 1;

    Node *temp = (*head)->adjacent;
    for(; temp != NULL;){
        if(!temp->dis_from_root[dis_mode]){
            Node **del_node = &temp;
            del_tree(del_node);
        }
        temp = temp->next_adjacent;
    }
    free(*head);
}

int main(){
    int T = 0;

    scanf("%d\n", &T);
    for(int i = 0; i < T; i++){
        int N = 0;
        scanf("%d\n", &N);

        Node **map = (Node**)malloc(sizeof(Node*) * (N + 1));
        for(int i = 0; i <= N; i++){
            map[i] = NULL;
        }
        Node *root = NULL;

        for(int j = 0; j < N - 1; j++){
            int u_i = 0, v_i = 0;
            scanf("%d %d\n", &u_i, &v_i);

            add_node(u_i, v_i, &root, map);
        }

        // printf("\n================\n");
        // print_tree(root);
        // printf("\n================\n");

        printf("%d\n", get_longest_path(&root));
        // del_tree(&root);
        free(map);
    }
}