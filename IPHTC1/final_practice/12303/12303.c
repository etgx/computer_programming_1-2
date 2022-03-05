// NTHUOJ 12303 - Operation on Sequence   
// Description
// No description, literally. I'm tired.
// _(:3∠」)_
// You have a sequence a. Initially, a has exactly one integer. You're at the place of the 1st element.
// There are some operations below:
// insert <val1> <val2>: insert <val2> number of elements, all with value <val1>. Insert them next to your position.
// erase <val>: erase <val> number of elements next to you.
// move <value>: Move <value> number of indexes forward. Note that <value> might be negative, which means you might move forward or backward.
// show: Start from your position, output the sequence a. Each element separated by a space. Note that there should be no space at the end but a '\n'.
// For example: a = {2}, and execute operations below:
// insert 3 6 // a = {2,3,3,3,3,3,3}, you're at the 1st position.
// insert 1 1 // a = {2,1,3,3,3,3,3,3}, you're at the 1st position.
// erase 2 // a = {2,3,3,3,3,3}, you're at the 1st position. Erase 1 and 3.
// move 5 // a = {3,2,3,3,3,3}, you're at the 1st position. Originally was the 6th position.
// erase 3 // a = {3,3,3}, you're at the 1st position. Erase the first 2 and two 3.
// show // print 3 3 3. Note that there should be a '\n' at the end.

// Input
// The first line contains an integer x, indicates the first element in a.
// The next line contains an integer n, indicates the number of operations.
// There are n lines below. Each line contains exactly one operation.
// 1 <= n <= 3000. All numbers in a are in int range. We guaranteed that there must be at least 1 element in a, and the number of insert and erase elements won't exceed 3000.
// Also, the total elements of a won't exceed 3000.

// Output
// Output the correct a if there's show operation.

// Sample Input  
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

// Sample Output  
// 2 1 3 3 3 3 3 3
// 2 3 3 3 3 3
// 3 2 3 3 3 3
// 3 3 3

#include <stdio.h>
#include <stdlib.h>

// Double Circular linked List
typedef struct node{
    int value;
    struct node *next;
    struct node *prev;
}Node;

void insert(const int val, const int copies, Node *pos, int *count){
    Node *temp = pos;
    Node *posNext = pos->next;
    (*count) += copies;

    for(int i = 0; i < copies; i++){
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->value = val;
        newNode->prev = temp;

        temp->next = newNode;
        temp = newNode;
    }

    temp->next = posNext;
    posNext->prev = temp;
}

void erase(const int val, Node *pos, int *count){
    Node *nextTemp = pos->next;
    (*count) -= val;
    
    for(int i = 0; i < val; i++){
        Node *temp = nextTemp;
        nextTemp = nextTemp->next;
        free(temp);
    }

    pos->next = nextTemp;
    nextTemp->prev = pos;
}

void move(const int val, Node **pos, const int count){
    // Mod the move steps
    if(count <= 0) return;

    int modedVal = val % count;
    if(modedVal >= 0){
        for(int i = 0; i < modedVal; i++){
            (*pos) = (*pos)->next;
        }
    }else{
        for(int i = 0; i > modedVal; i--){
            (*pos) = (*pos)->prev;
        }
    }
    
}

void show(Node *pos, int *count){
    Node *temp = pos;

    printf("%d", pos->value);
    // while(temp->next != pos){
    for(int i = 0; i < (*count) - 1; i++){
        printf(" %d", temp->next->value);
        temp = temp->next;
    }
    printf("\n");
}

int main(){
    int x = 0, n = 0, count = 1;
    Node *init = (Node *)malloc(sizeof(Node));
    Node *pos = init;

    scanf("%d\n%d\n", &x, &n);
    init->value = x;
    init->next = init;
    init->prev = init;

    for(int i = 0; i < n; i++){
        char op[10] = {0};
        int val = 0, copies = 0;

        scanf("%s", op);
        // printf("%c\n", op[0]);

        switch (op[0]){
            case 'i': // Insert
                scanf("%d %d\n", &val, &copies);
                insert(val, copies, pos, &count);
                break;
            case 'e': // Erase
                scanf("%d\n", &val);
                erase(val, pos, &count);
                break;
            case 'm': // Move
                scanf("%d\n", &val);
                move(val, &pos, count);
                break;
            case 's': // Show
                show(pos, &count);
                break;
        }
    }

    return 0;
}