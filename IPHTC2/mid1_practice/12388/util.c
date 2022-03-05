#include "function.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inorder(Node *root){
    if(root->left_child != NULL){
        inorder(root->left_child);
    }

    if(root->left_child != NULL && root->right_child != NULL){
        printf("[%d]: %d <[%d] [%d]> ", root->uid, root->level, root->left_child->uid, root->right_child->uid);
    }else if(root->left_child != NULL){
        printf("[%d]: %d <[%d] NULL> ", root->uid, root->level, root->left_child->uid);
    }else if(root->right_child != NULL){
        printf("[%d]: %d <NULL [%d]> ", root->uid, root->level, root->right_child->uid);
    }else{
        printf("[%d]: %d <NULL NULL> ", root->uid, root->level);
    }

    if(root->right_child != NULL){
        inorder(root->right_child);
    }
}

void print_inorder(Node *root){
    if(root == NULL){
        return;
    }
    printf("Inorder: ");
    inorder(root);
    printf("\n");
}