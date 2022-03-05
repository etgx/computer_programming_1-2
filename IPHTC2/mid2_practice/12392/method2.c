// IPHTC2 Week8 Problem 1 | NTHUOJ 12392 - Heatstroke Bamboo Rats 2
// Description
// This bamboo rat seems to have heatstroke, we might as well ......
// ── Brothers HuaNong
// Brothers HuaNong feed a lot of bamboo rats. They do love to eat bamboo rats! However, some of the rats seems to have heatstroke. Brothers HuaNong couldn't bear to watch them suffer, and we all know how Brothers HuaNong treat those heatstroke rats... rat
// Every bamboo rat has its level of heatstroke(中暑程度), Brother HuaNong would randomly choose a number x. If there's a rat with level of heatstroke equals to x, Brother HuaNong would think that the rat has heatstroke and eat it.
// You are hired by Brothers HuaNong. Brothers HuaNong will give you the level of heatstroke of every bamboo rats and several numbers xx. Your task is to help them find out if there's rats that have heatstroke.
// This problem is partial judge. You are going to implement the following functions:

// void build_tree(Node **now, int *arr, int l, int r)
// When this function is called, you should build a binary search tree by the array arr. Main function will call build_tree(&root, arr, 0, n-1).
// Note that l and r indicates the index range of arr (in open interval), which means all elements from arr[l] to arr[r] are valid datas.

// int query_heatstroke(Node *now, int x)
// This function is used to ask if there exists a node with level equals to xx. Main function will call query_heatstroke(root, x).
// If the desired node exists, return 1, otherwise return 0.

// void eat_rat(Node **root, int x)
// This function will delete one node with level equals to xx. Main function will call eat_rat(&root, x).

// void buy_rat(Node **root, int x)
// This function will insert a node with level equals to xx. Main function will call buy_rat(&root, x).

// Input
// The first line is an integer n, which indicates the number of bamboo rats.
// The next line contains n integers, indicate the level of heatstroke of every bamboo rat sorted in ascending order.
// The third line is an integer q, which means there are q queries below.
// In each queries, there are two operations:

// heatstroke x: eat a rat with level equals to if there exists one.

// buy x: buy a rat with level equals to x.
// 0\le n\le10^4, 1\le q\le10^4, 1\le x\le10^9, the level of bamboo rats have the same range as x.

// Output
// For each heatstroke operation, output "We might as well eat it." if there's a rat with the corresponding level, otherwise output "No dinner tonight."

// Sample Input 1 

// 3
// 1 8 309
// 6
// heatstroke 8
// heatstroke 8
// heatstroke 1
// heatstroke 309
// buy 5
// heatstroke 5

// Sample Output 1

// We might as well eat it.
// No dinner tonight.
// We might as well eat it.
// We might as well eat it.
// We might as well eat it.

// Hint
// The struct Node is defined as:

// typedef struct _NODE {
//     int level;
//     struct _NODE *left_child, *right_child;
// } Node;

// Take sample as an example, initially, the level of heatstroke of the rats would be (1,8,309).
// heatstroke 8: exists a rat with level equals to 8, eat it. The sequence becomes (1,309).
// heatstroke 8: no such rat exists.
// heatstroke 1: exists a rat with level equals to 1, eat it. The sequence becomes (309).
// heatstroke 309: exists a rat with level equals to 309, eat it. The sequence is now empty.
// buy 5: buy a new rat with level 5. The sequence becomes (5).
// heatstroke 5: there exists a rat with level equals to 5, eat it. The sequence is now empty.

#include "function.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ALL correct
// Compile with bash script: bash compile.sh 2
// Correct, but more clear
Node* bst_build(int *arr, int l, int r){
    if(l <= r){
        int m = (l + r) / 2, pivot = arr[m];
        Node *new_node = (Node*)malloc(sizeof(Node));
        new_node->level = pivot;
        new_node->left_child = bst_build(arr, l, m - 1);
        new_node->right_child = bst_build(arr, m + 1, r);

        return new_node;
    }
    return NULL;
}

void build_tree(Node **now, int *arr, int l, int r){
    *now = bst_build(arr, l, r);
}

Node* find(Node *root, int x){
    if(root == NULL) return NULL;

    if(x > root->level){
        return find(root->right_child, x);
    }else if(x < root->level){
        return find(root->left_child, x);
    }else{
        return root;
    }
}

int query_heatstroke(Node *now, int x){
    Node *found = find(now, x);
    if(found == NULL){
        return 0;
    }else{
        return 1;
    }
}

int remove_node(Node **root){
    if((*root) == NULL) return 0;
    
    if((*root)->left_child != NULL && (*root)->right_child != NULL){
        // root has left and right subtrees. Choose largest node in left subtree to replace.
        Node **delete_node = &(*root)->left_child;
        while((*delete_node)->right_child != NULL){
            delete_node = &(*delete_node)->right_child;
        }
        (*root)->level = (*delete_node)->level;
        // NOTICE: The delete_node may have left subtree
        remove_node(delete_node);
    }else if((*root)->left_child != NULL){
        // root has left subtree
        Node *subtree = (*root)->left_child;
        free(*root);
        *root = subtree;
    }else if((*root)->right_child != NULL){
        // root has right subtree
        Node *subtree = (*root)->right_child;
        free(*root);
        *root = subtree;
    }else{
        // root is leaf node
        free(*root);
        *root = NULL;
    }
    return 1;
}

int delete(Node **root, int x){
    if((*root) == NULL) return 0;
    
    if(x > (*root)->level){
        return delete(&(*root)->right_child, x);
    }else if(x < (*root)->level){
        return delete(&(*root)->left_child, x);
    }else{
        return remove_node(root);
    } 
}

void eat_rat(Node **root, int x){
    delete(root, x);
}

int insert(Node **root, int x){
    Node **current = root;
    while(*current != NULL){
        if(x > (*current)->level){
            current = &(*current)->right_child;
        }else{
            current = &(*current)->left_child;
        }
    }
    *current = (Node*)malloc(sizeof(Node));
    (*current)->level = x;
    (*current)->right_child = (*current)->left_child = NULL;

    return 1;
}

void buy_rat(Node **root, int x){
    insert(root, x);
}