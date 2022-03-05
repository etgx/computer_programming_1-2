// IPHTC2 Week5 Problem 1 | NTHUOJ 12390 - Construct tree by inorder and preorder
// Description
// This problem is partial judge!
// We will give you the "inorder" and "preorder" of a tree.
// You need to construct a tree by the "inorder" and "preorder" we give you and
// print the "postorder".
// There are three function you need to complete.
// Node* buildTree(int *inorder, int *preorder, int *inorder_start, int inorder_end*);
// function to construct the tree.
// void showPostorder(Node *root)
// function to print the postorder
// void freeTree(Node *root)
// function to free the tree
// Notice that the the final testcase has small memory limit. If you don't free your tree you will get memory limit exceeded

// Input
// There are multiple testcases. The testcases will end with EOF.
// Each testcase contains three lines.
// First line only contains one integer n(1 <= n <= 100) which means the number of nodes in the tree.
// Second line contains n integers which in the range of int. Standing for the "inorder".
// Third line contains n integers which in the range of int. Standing for the "preorder".

// Output
// For each testcase output the "postorder" of the tree.
// Each number should be followed by a single blank(even the last number).

// Sample Input 1 
// 9
// 1 2 3 4 5 6 7 8 9
// 5 3 2 1 4 7 6 8 9
// 9
// 3 7 8 6 11 2 5 4 9
// 2 7 3 6 8 11 5 9 4

// Sample Output 1
// testcase1: 1 2 4 3 6 9 8 7 5 
// testcase2: 3 8 11 6 7 4 9 5 2 

// Hint
// The main function:

// int n;
// int main(void)
// {
//     int id = 1;
//     while( ~scanf( "%d", &n ) )
//     {
//         int inorder[100], preorder[100];
//         for( int i = 0; i < n; i++ )
//             scanf( "%d", &inorder[i] );
//         for( int i = 0; i < n; i++ )
//             scanf( "%d", &preorder[i] );
//         Node *root = buildTree( inorder, preorder, 0, n-1 );
//         printf( "testcase%d: ", id++ );
//         showPostorder( root );
//         printf( "\n" );
//         freeTree( root );
//     }
//     return 0;
// }

// The structure:

// typedef struct _NODE
// {
//     int number;
//     struct _NODE *ptr_to_right_node;
//     struct _NODE *ptr_to_left_node;
// } Node;

#include "function.h"
#include <stdlib.h>
#include <stdio.h>

#define PAUSE printf("Press Enter key to continue..."); fgetc(stdin);

Node* buildTree(int* Inorder, int* Preorder, int inorder_start, int inorder_end){
    Node *root = (Node*)malloc(sizeof(Node));
    int root_inorder_idx = 0;
    // int is_found = 0;
    root->number = Preorder[0];
    root->ptr_to_left_node = NULL;
    root->ptr_to_right_node = NULL;

    // printf("Created Node: %d\n", root->number);

    if(inorder_end == inorder_start)
        return root;

    for(int i = inorder_start; i <= inorder_end; i++){
        if(root->number == Inorder[i]){
            root_inorder_idx = i;
            // is_found = 1;
            break;
        }
    }
    // if(!is_found){
    //     printf("%d not found in [%d, %d]\n", root->number, inorder_start, inorder_end);
    //     return root;
    // }
        
    if(inorder_start <= root_inorder_idx - 1){
        // printf("Left[%d, %d] of Root[%d]: %d - Inorder [%d, %d]\n", inorder_start, root_inorder_idx - 1, root_inorder_idx, Inorder[root_inorder_idx], inorder_start, inorder_end);
        root->ptr_to_left_node = buildTree(Inorder, &(Preorder[1]), inorder_start, root_inorder_idx - 1);
    }
    if(root_inorder_idx + 1 <= inorder_end){
        // printf("Right[%d, %d] of Root[%d]: %d - Inorder [%d, %d]\n", root_inorder_idx + 1, inorder_end, root_inorder_idx, Inorder[root_inorder_idx], inorder_start, inorder_end);
        root->ptr_to_right_node = buildTree(Inorder, &(Preorder[1 + root_inorder_idx - inorder_start]), root_inorder_idx + 1, inorder_end);
    }
    return root;
}

void showPostorder(Node* root){
    if(root->ptr_to_left_node != NULL){
        showPostorder(root->ptr_to_left_node);
    }
    if(root->ptr_to_right_node != NULL){
        showPostorder(root->ptr_to_right_node);
    }
    printf("%d ", root->number);
}

void freeTree(Node *root){
    if(root->ptr_to_left_node != NULL){
        freeTree(root->ptr_to_left_node);
    }
    if(root->ptr_to_right_node != NULL){
        freeTree(root->ptr_to_right_node);
    }
    free(root);
}