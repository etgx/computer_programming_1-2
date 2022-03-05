// I2P - Kuo Week1 Problem 4 | NTHUOJ 13137 - binary search tree   
// Description
// There's an empty binary search tree, you have to implement two functions:

// 1. add_node: 
// If the tree is empty, the node will be the root node of this tree.
// Otherwise, start to compare with the root node, if the new node is smaller than it, compare with the leftchild, otherwise, compare with the rightchild, until there is no node to compare, place the new node.
// For example:
// There is a binary search tree
// add 7 to this tree
// compare with the root
// 7 >= 5, compare with the rightchild
// 7 < 10, compare with the leftchild
// 7 <= 8 and node 8 has no leftchild, so put 7 to the leftchild of node 8, the tree will be like:

// 2. showtree: output this tree in in-order

// Input
// The first line contains a integer n, means how many node to add.
// The second line contains n number a1 ~ an, means the value of n node.
// testcases:
// 1. n <= 1000, 0 <= ai <= 109, the sequence of n numbers is increasing.
// 2. n <= 1000, 0 <= ai <= 109, the sequence of n number is decreasing.
// 3. n <= 1000, 0 <= ai <= 109.

// Output
// The output has only one line, contains n numbers, the in-order traversal of binary search tree.
// please output a whitespace after every number.

// Sample Input  

// Sample Input 1:
// 5
// 1 2 3 4 5
// Sample Input 2:
// 5
// 5 8 3 4 7

// Sample Output  

// Sample Output 1:
// 1 2 3 4 5
// Sample Output 2:
// 3 4 5 7 8

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

void add_node(int n){
    Tree_Node *temp = NULL;
    Tree_Node **temp_next = &tree_head;
    Tree_Node *new_node = (Tree_Node*)malloc(sizeof(Tree_Node));
    new_node->number = n;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->parent = NULL;

    for(; *temp_next != NULL;){
        temp = *temp_next;

        if(n > temp->number){
            temp_next = &(temp->right);
        }else if(n < temp->number){
            temp_next = &(temp->left);
        }
    }
    new_node->parent = temp;
    *temp_next = new_node;
    
    // printf("=====================\n");
    // printf("Insert: %d\n", n);
    // printf("---------------------\n");
    // showtree(tree_head);
    // printf("\n=====================\n");
}

void showtree(Tree_Node* treenow){
    if(treenow == NULL) return;

    showtree(treenow->left);
    printf("%d ", treenow->number);
    showtree(treenow->right);
}