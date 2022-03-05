// NTHUOJ 11617 - pA - Arranging a Sequence   
// Description
// Source : ACM International Collegiate Programming Contest Asia Regional Contest, Tsukuba, 2016/10/16 
// You are given an ordered sequence of integers, (1,2,3,...,n). Then, a number of requests will be given. Each request specifes an integer in the sequence. You need to move the specied integer to the head of the sequence, leaving the order of the rest untouched. Your task is to find the order of the elements in the sequence after following all the requests successively.
// Sample Output Explanation : In Sample Input 1, the initial sequence is (1; 2; 3; 4; 5). The first request is to move the integer 4 to the head, that is, to change the sequence to (4; 1; 2; 3; 5). The next request to move the integer 2 to the head makes the sequence (2; 4; 1; 3; 5). Finally, 5 is moved to the head, resulting in (5; 2; 4; 1; 3).

// Input
// The input consists of a single test case of the following form.
// n m
// e1
// :
// em
// The integer n is the length of the sequence ( 1 <= n <= 200000 ). The integer m is the number of requests ( 1 <= m <= 100000 ). The following m lines are the requests, namely e1,...,em, one per line. Each request ei ( 1 <= i <= m ) is an integer between 1 and n, inclusive, designating the element to move. Note that, the integers designate the integers themselves to move, not their positions in the sequence.

// Output
// Output the sequence after processing all the requests. Its elements are to be output, one per line, in the order in the sequence.
// There should be a new line at the end of the output.

// Sample Input  
// 5 3
// 4
// 2
// 5

// Sample Output  
// 5
// 2
// 4
// 1
// 3

// 2020/05/01 SYC

#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int value;
    struct node *prev;
    struct node *next;
}Node;

typedef struct terminal{
    Node *head;
    Node *tail;
}Terminal;

Terminal *initTerminal(){
    Terminal *t = (Terminal *)malloc(sizeof(Terminal));
    t->head = NULL;
    t->tail = NULL;

    return t;
}

Node **initMap(int len){
    Node **nodeMap = (Node **)malloc(sizeof(Node *) * len);
    for(int i = 0; i < len; i++){
        nodeMap[i] = NULL;
    }

    return nodeMap;
}

// Add New Node into List at the Head
Node *push(Terminal *terminal, Node *node){
    if(terminal->head == NULL && terminal->tail == NULL){
        // Adapt New Head
        node->prev = NULL;
        node->next = NULL;

        // Adapt Terminal Tail
        terminal->tail = node;

        // Adapt Terminal Head
        terminal->head = node;
    }else{
        // Adapt New Head
        node->prev = NULL;
        node->next = terminal->head;

        // Adapt Old Terminal Head
        terminal->head->prev = node;

        // Adapt Terminal Head
        terminal->head = node;
    }

    return node;
}

// Add New Value into List at the Tail
Node *add(Terminal *terminal, Node **map, int value){
    // Adapt New Tail
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->value = value;
    newNode->prev = terminal->tail;
    newNode->next = NULL;

    // Adapt Map
    map[value] = newNode;

    if(terminal->head == NULL){
        // Adapt Terminal Head
        terminal->head = newNode;

        // Adapt Terminal Tail
        terminal->tail = newNode;
    }else{
        // Adapt Old Terminal Tail
        terminal->tail->next = newNode;

        // Adapt Terminal Tail
        terminal->tail = newNode;
    }

    return newNode;
}

// Remove The Node From List
Node *erase(Terminal *terminal, Node **map, int value){
    if(map[value] == terminal->head){
        terminal->head = map[value]->next;

        map[value]->prev = NULL;
        map[value]->next = NULL;
    }else if(map[value] == terminal->tail){
        terminal->tail = map[value]->prev;

        map[value]->prev = NULL;
        map[value]->next = NULL;
    }else{
        // Adapt The Next Node of Erasing Node 
        map[value]->prev->next = map[value]->next;
        // Adapt The Previous Node of Erasing Node 
        map[value]->next->prev = map[value]->prev;

        // Adapt The Erasing Node
        map[value]->prev = NULL;
        map[value]->next = NULL;
    }

    return map[value];
}

void showList(Terminal *terminal, int nodeNumber){
    Node *temp = terminal->head;
    for(int i = 0; i < nodeNumber; i++){
        printf("%d ", temp->value);
        temp = temp->next;
    }
    printf("\n");
}

void showListFormal(Terminal *terminal, int nodeNumber){
    Node *temp = terminal->head;
    for(int i = 0; i < nodeNumber; i++){
        printf("%d\n", temp->value);
        temp = temp->next;
    }
}

int main(){
    int n = 0, m = 0;
    scanf("%d %d\n", &n, &m);

    Terminal *terminal = initTerminal();
    Node **nodeMap = initMap(n);

    for(int i = 1; i <= n; i++){
        add(terminal, nodeMap, i);
    }

    // showList(terminal, n);

    for(int i = 0; i < m; i++){
        int em = 0;
        scanf("%d\n", &em);

        Node* erasedNode = erase(terminal, nodeMap, em);
        // showList(terminal, n-1);
        push(terminal, erasedNode);
        // showList(terminal, n);
    }

    showListFormal(terminal, n);

    return 0;
}