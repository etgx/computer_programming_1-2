// NTHUOJ 12289 - after rain   
// Description
// After rain comes sunshine and rainbow.
// 5/17 is the International Day Against Homophobia, Transphobia and Biphobia(國際不再恐同日), which is also the day that legislative committees trial the special law about LGBT. They eventually pass a draft that fully in line with the referendum, which make Taiwan be the first Asia country that pass a law for LGBT.

// Knuckles is on his way of finding his queen. When he arrived Taiwan and see a lot of rainbow flags, he wondered that these rainbow flags might be a clue of the location of his queen. He will give some operations about these flags, you are going to help him, or he'll spit on you.

// There are colors on these flags. The colors include: "Red", "Orange", "Yellow", "Green", "Blue", "Purple", which are the color of rainbow.
// Knuckles has a sequence of colors. Initially, the sequence is empty.
// Knuckles has several operations: insert, erase1, erase2, reverse, show.
// insert <color> <dest>: means insert <color> after the location of <dest>. For example, insert Yellow 5 means insert a "Yellow" after the 5-th location. If <dest> is larger than the length of the sequence, just regard it as the last location of the sequence.
// erase1 <dest>: means erase the color locates at <dest>. For example, erase1 4 will erase the 4-th color in the sequence. If <dest> is larger than the length of the sequence, just regard it as the last location of the sequence.
// erase2 <color>: means erase all <color> in the sequence. For example, erase2 Purple will erase all the "Purple" in the sequence. After the operation, There should be no "Purple" in the sequence.
// reverse <dest1> <dest2>: means reverse the elements from <dest1> to <dest2>. If the order was originally {"Yellow", "Purple", "Blue"}, after reversing, the order should become {"Blue", "Purple", "Yellow"}. If <dest1> or <dest2> is larger than the length of the sequence, just regard it as the last location of the sequence.
// show: show the sequence according to the order.
// You are going to implement a linked list that support these operations. We have implemented show operation, what you have to do is to implement the remaining operations: insert, erase1, erase2, reverse.
// If you have further questions, please reference to the sample I/O.

// Input
// The first line contains an integer n, indicates the number of operations.
// There are n lines below. Each line contains one operations described above.
// <color> will only appear the 6 colors described above.
// insert: 0 <= <dest> <= 10000
// erase1: 1 <= <dest> <= 10000
// reverse: 1 <= <dest1>, <dest2> <= 10000
// 1 <= n <= 5000

// Output
// When show operation is called, you should output the correct sequence after operating.

// Sample Input  
// 15
// insert Red 0
// insert Blue 10
// show
// insert Purple 1
// insert Blue 3
// insert Blue 1
// show
// erase1 3
// show
// insert Yellow 4
// insert Purple 6
// reverse 3 5
// show
// erase2 Blue
// show

// Sample Output  
// Red Blue 
// Red Blue Purple Blue Blue 
// Red Blue Blue Blue 
// Red Blue Yellow Blue Blue Purple 
// Red Yellow Purple 

// Partial Judge Code
// 12289.c

// Partial Judge Header
// 12289.h

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

typedef struct _NODE
{
	char color[10];
	struct _NODE *next;
} Node;

void insert(Node** head, char* color, int dest){ // insert <color> <dest>
    Node *temp = (*head);
    Node *newNode = (Node*)malloc(sizeof(Node));

    for(int i = 0; i < dest; i++){
        if(temp->next == NULL){break;}
        temp = temp->next;
    }

    strncpy(newNode->color, color, sizeof((*head)->color));
    newNode->next = temp->next;
    temp->next = newNode;
}

void erase1(Node** head, int dest){ // erase1 <dest>
    Node *temp = (*head);
    Node *deleted = (*head)->next;

    if(deleted == NULL){return;}

    for(int i = 1; i < dest; i++){
        if(deleted->next == NULL){break;}
        temp = temp->next;
        deleted = deleted->next;
    }

    temp->next = deleted->next;
    free(deleted);
}

void erase2(Node** head, char* color){ // erase2 <color>
    Node *temp = (*head);
    Node *deleted = (*head)->next;

    while(deleted != NULL){
        if(strcmp(deleted->color, color) == 0){
            temp->next = deleted->next;
            free(deleted);
            deleted = temp->next;
        }else{
            temp = temp->next;
            deleted = deleted->next;
        }
    }
}

void reverse(Node** head, int dest1, int dest2){ // reverse <dest1> <dest2>
    Node *dest1Node = (*head)->next;
    Node *dest2Node = (*head)->next;

    if(dest1 == dest2 || dest1Node == NULL){return;}
    // Make dest2 larger than dest1
    if(dest1 > dest2){
        int t = dest2;
        dest2 = dest1;
        dest1 = t;
    }

    int i = 0, j = 0;

    for(i = 1; i < dest1; i++){
        if(dest1Node->next == NULL){break;}
        dest1Node = dest1Node->next;
    }
    
    for(j = 1; j < dest2; j++){
        if(dest2Node->next == NULL){break;}
        dest2Node = dest2Node->next;
    }
    int buffSize = j - i + 1;
    Node *buff = (Node *)malloc(sizeof(Node) * buffSize);
    Node *tempNode = dest1Node;
    for(int k = i, c = 0; k <= j; k++, c++){
        buff[c] = *tempNode;
        tempNode = tempNode->next;
    }
    tempNode = dest1Node;
    for(int k = i, c = buffSize - 1; k <= j; k++, c--){
        strncpy(tempNode->color, buff[c].color, 10);
        tempNode = tempNode->next;
    }
    free(buff);
}