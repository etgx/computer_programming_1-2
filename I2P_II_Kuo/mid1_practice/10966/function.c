#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

#define SYMBOL_A_ID 0
#define SYMBOL_B_ID 1
#define SYMBOL_C_ID 2
#define SYMBOL_D_ID 3
#define SYMBOL_AND_ID 4
#define SYMBOL_OR_ID 5

BTNode* EXPR(){
    BTNode *root = NULL;
    int temp = 0;
    if(pos >= 0){
        BTNode *factor = FACTOR();
        if(pos >= 0 && (expr[pos] == '&' || expr[pos] == '|')){
                root = makeNode(expr[pos]);
                temp = pos;
                pos--;
                root->left = EXPR();
                root->right = factor;
                // printf("[%c] -> [EXPR] -> [%c]\n", root->data, factor->data);
        }else{
            root = factor;
            // printf("[%c]\n", root->data);
        }

        // if(root == NULL){
        //     printf("Pos: %d | Root is NULL\n", temp);
        // }
        // printf("[%c] Pos: (%d) EXPR: ",sym[root->data], temp);
        // printPrefix(root);
        // printf("\n");
    }
    return root;
}
BTNode* FACTOR(){
    if(pos < 0) return NULL;

    char data = expr[pos];
    BTNode *new_node = NULL;
    int temp = pos;
    pos--;

    if(data == sym[OP_AND] || data == sym[OP_OR]){
        // OP
        new_node = makeNode(data);
        // printf("<- [%c]\n", new_node->data);
        // printf("Factor: [%c] Pos: %d EXPR: ", sym[new_node->data], temp);
        // printPrefix(new_node);
        // printf("\n");
    }else if(data >= sym[ID_A] && data <= sym[ID_D]){
        // ID
        new_node = makeNode(data);
        // printf("<- [%c]\n", new_node->data);
        // printf("Factor: [%c] Pos: %d EXPR: ", sym[new_node->data], temp);
        // printPrefix(new_node);
        // printf("\n");
    }else if(data == ')'){
        // (EXPR)
        new_node = EXPR();
        pos--;
        // if(new_node == NULL){
        //     printf("Pos: %d | new_node is NULL\n", temp);
        // }

        // printf("[%c] Pos: %d (EXPR): ", sym[new_node->data], temp);
        // printPrefix(new_node);
        // printf("\n");
    }
    // printPrefix(new_node);
    return new_node;
}
BTNode* makeNode(char c){
    BTNode *new_node = (BTNode*)malloc(sizeof(BTNode));
    if(c == sym[ID_A]){
        new_node->data = ID_A;
    }else if(c == sym[ID_B]){
        new_node->data = ID_B;
    }else if(c == sym[ID_C]){
        new_node->data = ID_C;
    }else if(c == sym[ID_D]){
        new_node->data = ID_D;
    }else if(c == sym[OP_AND]){
        new_node->data = OP_AND;
    }else if(c == sym[OP_OR]){
        new_node->data = OP_OR;
    }else{
        // printf("Occur an excepttion character: %c at Pos: %d\n", c, pos);
        new_node->data = 0;
    }
    
    new_node->left = new_node->right = NULL;
    // printf("New node: %c\n", new_node->data);
    return new_node;
}