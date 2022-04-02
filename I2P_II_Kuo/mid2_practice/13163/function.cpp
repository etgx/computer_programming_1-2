/**
I2P - Kuo HW2 Problem 3 | NTHUOJ 13163 - KYてぇてぇ — Birthday Present（class）
Kuo-chan is given a sequence A and a constant K as his birthday present from Yang-chan.
Kuo-chan is allowed to perfrom the following operation:

push x - push x to the end of A
pop - remove the median value of A （the median value of A is A[ (|A|+1)/2 ]）
programming tanoshi - for 1 <= i <= |A|, assign A[ i ] % K to A[ i ]

For example, if A = [4, 3, 5], K = 2
push 11　=>　A = [4, 3, 5, 11]
pop　=>　A = [4, 5, 11]
pop　=>　A = [4, 11]
programming tanoshi　=>　A = [0, 1] 
Yang-chan is curious about what A is after Kuo-chan performs some operations to it.
Help him find it out!

Input
The first line contains three integers N K Q — the length of A, the constant Yang-chan gives Kuo-chan, the number of operations Kuo-chan performs.
The second line contains N integers a1, a2, ..., aN （1 <= ai <= N） — the elements of A. 
Each of the next Q lines describes the operations. Each line is one of three types:
push x （1 <= x <= N）
pop
programming tanoshi
 

Different testcases have different constraints.
N <= 103, Q <=   N, K <= N, operations: {pop}
N <= 103, Q <= 2N, K <= N, operations: {pop, push}
N <= 103, Q <= 2N, K <= N, operations: {pop, push, programming tanoshi}
N <= 105, Q <=   N, K <= N, operations: {pop}
N <= 105, Q <= 2N, K <= N, operations: {pop, push}
N <= 105, Q <= 2N, K <= N, operations: {pop, push, programming tanoshi}

Output
You should print one line containing the elements of A after the operations. For 1 <= i <= |A|, the i-th number should be A[ i ].


Sample Input  
5 3 10
3 1 4 4 2
pop
pop
push 4
programming tanoshi
push 1
push 2
pop
pop
pop
push 7

Sample Output  
0 1 2 7 
**/

#include <iostream>
#include "function.h"

Node* createNode(Node *prev, Node *next, int val, int tag){
    Node *newNode = new Node;
    newNode->prev = prev;
    newNode->next = next;
    newNode->val = val;
    newNode->tag = tag;
    return newNode;
}

void removeNode(Node *node){
    node->next->prev = node->prev;
    node->prev->next = node->next;
    delete node;
}

KuoYangPresent::KuoYangPresent(int k){
    this->head = createNode(NULL, NULL, 0, 0);
    this->tail = createNode(this->head, this->head, 0, 0);
    this->head->next = this->head->prev = this->tail;
    this->mid = this->head;

    this->k = k;
    this->sz = 0;
}

void KuoYangPresent::Push(int x){
    Node *newNode = createNode(this->tail->prev, this->tail, x, 0);
    this->tail->prev->next = newNode;
    this->tail->prev = newNode;
    if(this->sz % 2 == 0){
        this->mid = this->mid->next;
    }
    this->sz++;
}

void KuoYangPresent::Pop(){
    if(this->mid == NULL || this->mid == this->head || this->mid == this->head) return;

    Node *delNode = this->mid;
    if(this->sz % 2 == 0){
        this->mid = this->mid->next;
        removeNode(delNode);
    }else{
        this->mid = this->mid->prev;
        removeNode(delNode);
    }
    this->sz--;
}

void KuoYangPresent::ProgrammingTanoshi(){
    if(this->tail == NULL) return;
    
    Node *temp = this->tail->prev;
    for(; temp != this->head && temp != NULL && temp->tag <= 0; temp = temp->prev){
    // for(; temp != this->head && temp != NULL; temp = temp->prev){
        temp->val = temp->val % this->k;
        temp->tag = 1;
    }
}

void KuoYangPresent::KuoYangTeTe(){
}

void KuoYangPresent::PrintList(){
    if(this->head == NULL) return;
    Node *temp = this->head->next;

    for(; temp != this->tail && temp != NULL; temp = temp->next){;
        std::cout << temp->val << " ";
    }
    std::cout << std::endl;
}