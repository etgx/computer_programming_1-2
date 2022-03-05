#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED

typedef struct _Node{
    int number;
    struct _Node* prev;
    struct _Node* next;
}Node;

Node* head;
Node* createList(int n);
void solve(int n, int m);

#endif
