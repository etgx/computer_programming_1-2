// I2P - Kuo Mid Practice Problem 2 | NTHUOJ 10968 - Prefix to infix   
// Description
// Given an prefix Boolean expression, which has at most 4 variables ‘A’, ’B’, ‘C’, and ‘D’, and two operators ‘&’ and ‘|’. Output its infix presentation with necessary parenthesis.
// Ex: input: ||A&BCD
// output: A|(B&C)|D
// Hint : About necessary parenthesis, you can observe the syntax tree which has been constructed, then you will find out the rule. For example, the infix expression of |&|AB&CDA with necessary parenthesis is A|B&(C&D)|A, rather than (A|B)&(C&D)|A .
// Syntax tree of |&|AB&CDA
// You will be provided with main.c and function.h, and asked to implement function.c.
// For OJ submission:
//         Step 1. Submit only your function.c into the submission block.(Please choose C compiler)
//         Step 2. Check the results and debug your program if necessary.

// Input
// The first line will have a number N with the number of test cases, followed by N lines of input, each contain the prefix Boolean expression.

// Output
// There are N lines infix expression with necessary parenthesis.

// Sample Input  

// 4
// ||A&BCD
// ||BC&|AB&CD
// &A|BC
// &||BC&AD||CB&AB

// Sample Output  

// A|(B&C)|D
// B|C|(A|B&(C&D))
// A&(B|C)
// B|C|(A&D)&(C|B|(A&B))

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

/** Important!!
 * In OJ 10968, you only need to implement the ``printInfix`` function, nothing else.
*/

Node* ceate_node(char data, Node *left, Node *right){
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->left = left;
    new_node->right = right;
    return new_node;
}

void constructTree(Node **head){
    char data = getchar();
    *head = NULL;

    if(data == '&' || data == '|'){
        // Operator
        Node *new_node = *head = ceate_node(data, NULL, NULL);
        constructTree(&(new_node->left));
        constructTree(&(new_node->right));
        // printf("New Node: [%c] -> [%c] - [%c]\n", data, new_node->left->data, new_node->right->data);
    }else if(data == 'A' || data == 'B' || data == 'C' || data == 'D'){
        // Symbol
        Node *new_node = *head = ceate_node(data, NULL, NULL);
        // printf("New Node: [%c]\n", data);
    }
}

void printInfix(Node *root){
    if(root == NULL) return;

    printInfix(root->left);
    printf("%c", root->data);

    int is_parenthesis = 0;
    if(root->right != NULL && (root->right->data == '&' || root->right->data == '|')){
        printf("(");
        is_parenthesis = 1;
    }
    printInfix(root->right);
    if(is_parenthesis){
        printf(")");
    }
}

void freeTree(Node *root){
    if(root == NULL) return;

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}