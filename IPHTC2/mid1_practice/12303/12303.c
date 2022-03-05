// IPHTC2 Week3 Problem 1 | NTHUOJ 12303 - Operation on Sequence
// Description
// No description, literally. I'm tired.
// _(:3」∠)_
// You have a circular sequence a. Initially, a has exactly one integer. You're at the place of the 1st element.
// There are some operations below:
// insert <val1> <val2>: Insert <val2> number of elements, all with value <val1>. Insert them next to your position.
// erase <val>: Erase <val> number of elements next to you.
// move <value>: Move <value> number of indexes forward. Note that <value> might be negative, which means you might move forward or backward.
// show: Start from your position, output the sequence a. Each element separated by a space. Note that there should be no space at the end but a '\n'.
// You may refer to "Hint" section to understand the operations clearly.

// Input
// The first line contains an integer x, indicates the first element in a.
// The next line contains an integer n, indicates the number of operations.
// There are n lines below. Each line contains exactly one operation.
// 1 &lt;= n &lt;= 30001<=n<=3000. All numbers in a are in int range. The number of inserted / erased elements is a positive integer, while the steps of move operation is also in int range.
// We guaranteed that there must be at least 1 element in a, and the number of insert and erase elements won't exceed 3000.
// The total elements of a won't exceed 3000.

// Output
// Output the sequence a if there's show operation.

// Sample Input 1 
// 2
// 9
// insert 3 6
// insert 1 1
// show
// erase 2
// show
// move 5
// show
// erase 3
// show

// 2021/10/07 SYC 

#include <stdlib.h>
#include <stdio.h>

typedef struct node{
    int val;
    struct node *prev;
    struct node *next;
} Node;

void insert(Node *a, const int val1, const int val2, int *seq_len){
    (*seq_len) = (*seq_len) + val2;
    Node *p = a;
    for(int i = 0; i < val2; i++){
        Node *prev_node = p;
        Node *next_node = p->next;

        // New a node
        Node *new_node = (Node*)malloc(sizeof(Node));
        new_node->val = val1;
        new_node->prev = prev_node;
        new_node->next = next_node;

        // Insert to list
        next_node->prev = new_node;
        prev_node->next = new_node;

        p = new_node;
    }
}

void erase(Node *a, const int val, int *seq_len){
    (*seq_len) = (*seq_len) - val;
    Node *p = a;
    for(int i = 0; i < val; i++){
        Node *delete_node = p->next;
        Node *new_next_node = delete_node->next;
        p->next = new_next_node;
        new_next_node->prev = p;

        // Delete
        free(delete_node);
    }
}

void move(Node **a, const int value, int seq_len){
    // In order to modify the value of the pointer, we need to pass the pointer of the pointer
    if(value > 0){
        int mod_value = value % seq_len;
        for(int i = 0; i < mod_value; i++){
            (*a) = (*a)->next;
        }
    }else if(value < 0){
        int mod_value = (-value % seq_len);
        for(int i = 0; i < mod_value; i++){
            (*a) = (*a)->prev;
        }
    }
}

void show(Node *a){
    Node *head = a;
    Node *p = a;
    int counter = 0;
    do{
        if(counter > 0)
            printf(" ");
        printf("%d", p->val);
        p = p->next;
        counter++;
    }while(p != head);
    printf("\n");
}

int main(){
    int x = 0, n = 0, seq_len = 1;
    Node *a = (Node*)malloc(sizeof(Node));
    scanf("%d", &x);
    scanf("%d", &n);
    // printf("x: %d n: %d\n", x, n);
    a->val = x;
    a->prev = a;
    a->next = a;

    for(int i = 0; i < n; i++){
        char op[10] = {0};
        int val1 = 0, val2 = 0;
        scanf("%s", op);

        switch (op[0]){
            case 'i':
                scanf("%d %d", &val1, &val2);
                // printf("Insert: %s %d %d\n", op, val1, val2);
                insert(a, val1, val2, &seq_len);
                break;
            case 'e':
                scanf("%d", &val1);
                // printf("Erase: %s %d\n", op, val1);
                erase(a, val1, &seq_len);
                break;
            case 'm':
                scanf("%d", &val1);
                // printf("Move: %s %d\n", op, val1);
                move(&a, val1, seq_len);
                break;
            case 's':
                // printf("Show: %s\n", op);
                show(a);
                break;
        }
    }

    return 0;
}