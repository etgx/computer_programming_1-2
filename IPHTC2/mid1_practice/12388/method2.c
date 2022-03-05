// IPHTC2 Week6 Problem 3 | NTHUOJ 12388 - Heatstroke Bamboo Rats
// Description
// This bamboo rat seems to have heatstroke, we might as well ......
// ── Brothers HuaNong
// Brothers HuaNong feed a lot of bamboo rats. They do love to eat bamboo rats! However, some of the rats seems to have heatstroke. Brothers HuaNong couldn't bear to watch them suffer, and we all know how Brothers HuaNong treat those heatstroke rats...
// rat
// Every bamboo rat has its level of heatstroke(中暑程度), Brother HuaNong would randomly choose a number xx. If there's a rat with level of heatstroke equals to xx, Brother HuaNong would think that the rat has heatstroke and eat it.
// You are hired by Brothers HuaNong. Brothers HuaNong will give you the level of heatstroke of every bamboo rats and several numbers xx. Your task is to help them find out if there's rats that have heatstroke.
// Hint: construct a binary search tree.
// This problem is partial judge. You are going to implement the following functions:

// void build_tree(Node **now, int *arr, int l, int r)
// When this function is called, you should build a binary search tree by the array arr. Main function will call build_tree(&root, arr, 0, n-1).
// Note that l and r indicates the index range of arr (in open interval), which means all elements from arr[l] to arr[r] are valid datas.

// int query_heatstroke(Node *now, int x)
// This function is used to ask if there exists a node with level equals to xx. Main function will call query_heatstroke(root, x).
// If the desired node exists, return 1, otherwise return 0.

// void eat_rat(Node **root, int x)
// This function will delete one node with level equals to xx. Main function will call eat_rat(&root, x).

// Input
// The first line is an integer nn, which indicates the number of bamboo rats.
// The next line contains nn integers, indicate the level of heatstroke of every bamboo rat sorted in ascending order.
// The third line is an integer qq, which means there are qq queries below.
// There are qq lines below. Each line contains exactly one integer xx.
// 1 <= n <= 10^6, 1 <= q <=10^6, 1 <= x <= 10^9, the level of bamboo rats have the same range as xx.

// Output
// For each query xx, output "We might as well eat it." if there's a rat with level of heatstroke x, otherwise output "No dinner tonight."

// Sample Input 1 
// 8
// 1 2 3 6 8 10 10 309
// 5
// 8
// 10
// 10
// 200
// 10

// Sample Output 1
// We might as well eat it.
// We might as well eat it.
// We might as well eat it.
// No dinner tonight.
// No dinner tonight.

// Hint
// The struct Node is defined as:

// typedef struct _NODE {
//     int level;
//     struct _NODE *left_child, *right_child;
// } Node;

// Take sample as an example, initially, the level of heatstroke of the rats would be (1,2,3,6,8,10,10,309).
// Firstly, x=8, they will eat a rat with level equals 8. The sequence becomes (1,2,3,6,10,10,309).
// x=10: eat a rat with level equals to 10. The sequence becomes (1,2,3,6,10,309).
// x=10: eat a rat with level equals to 10. The sequence becomes (1,2,3,6,309).
// x=200: no rat with level equals to 200.
// x=10: no rat with level equals to 10(since all rats with level 10 are eaten).

#include "function.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ALL correct
// Compile with bash script: bash compile.sh 2
// Correct, but more clear
void bst_build(Node **root, int *arr, int l, int r){
    // static int uid_count = 0;
    if(l <= r){
        int pivot = (l + r) / 2;
        int val = arr[pivot];
        Node *node = (Node*)malloc(sizeof(Node));
        node->level = val;
        node->left_child = NULL;
        node->left_child = NULL;
        // node->uid = uid_count;
        (*root) = node;
        // printf("<%d %d> - [%d]: %d UID: %d\n", l, r, pivot, val, uid_count);
        // uid_count++;

        bst_build(&(node->left_child), arr, l, pivot - 1);
        bst_build(&(node->right_child), arr, pivot + 1, r);
    }
}

void build_tree(Node **now, int *arr, int l, int r){
    bst_build(now, arr, l, r);
}

Node* find(Node *root, int x){
    if(root == NULL){
        return NULL;
    }
    if(root->level > x){
        return find(root->left_child, x);
    }else if(root->level < x){
        return find(root->right_child, x);
    }else{
        return root;
    }
}

int query_heatstroke(Node *now, int x){
    if(now == NULL){
        return 0;
    }
    Node *res = find(now, x);
    if(res == NULL){
        return 0;
    }else{
        return 1;
    }
}

int remove_node(Node **root){
    // printf("RM [%d]: %d\n", (*root)->uid, (*root)->level);
    if((*root) == NULL){
        return 0;
    }
    if((*root)->left_child != NULL && (*root)->right_child != NULL){
        Node **current = &((*root)->right_child);
        while((*current)->left_child != NULL){
            current = &((*current)->left_child);
        }
        (*root)->level = (*current)->level;
        // printf("Removing Min of Right Subtree [%d]: %d\n", (*current)->uid, (*current)->level);
        remove_node(current);
    }else if((*root)->left_child != NULL){
        // Has left subtree only
        Node *delete_node = (*root)->left_child;
        (*root)->level = delete_node->level;
        (*root)->left_child = delete_node->left_child;
        (*root)->right_child = delete_node->right_child;
        // printf("Removed Left [%d]: %d\n", delete_node->uid, delete_node->level);
        free(delete_node);
    }else if((*root)->right_child != NULL){
        // Has right subtree only
        Node *delete_node = (*root)->right_child;
        (*root)->level = delete_node->level;
        (*root)->left_child = delete_node->left_child;
        (*root)->right_child = delete_node->right_child;
        // printf("Removed Right [%d]: %d\n", delete_node->uid, delete_node->level);
        free(delete_node);
    }else{
        // No subtree
        // printf("Removed Leaf [%d]: %d\n", (*root)->uid, (*root)->level);
        free(*root);
        (*root) = NULL;
    }
    return 1;
}

int delete(Node **root, int x){
    if(*root == NULL){
        return 0;
    }else{
        if((*root)->level > x){
            delete(&((*root)->left_child), x);
        }else if((*root)->level < x){
            delete(&((*root)->right_child), x);
        }else{
            remove_node(root);
        }
        return 1;
    }
}

void eat_rat(Node **root, int x){
    delete(root, x);
}