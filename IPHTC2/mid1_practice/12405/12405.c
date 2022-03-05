// IPHTC2 Week3 Problem 3 | NTHUOJ 12405 - Construct tree by inorder and postorder
// Description
// We will give you the "inorder" and "postorder" of a tree.
// You need to print the "preorder" of this tree we give you.
// Note that the the testcases has low memory limit. If you don't free your tree you will get memory limit exceeded.

// Input
// There are multiple testcases. The testcases will end with EOF.
// Each testcase contains three lines.
// First line only contains one integer n\ (1\le n\le 100)n (1≤n≤100), which means the number of nodes in the tree.
// Second line contains nn integers which in the range of int, standing for the "inorder".
// Third line contains nn integers which in the range of int, standing for the "postorder".

// Output
// For each testcase output the "preorder" of the tree, you have to output in this form:
// testcase<id>: <preorder sequence>
// Replace <id> and <preorder sequence> into the ii-th testcase and the correct preorder sequence.
// Each number in preorder sequence should be followed by a single blank(even the last number).
// If you have further questions, please refer to sample output.

// Sample Input 1 
// 9
// 1 2 3 4 5 6 7 8 9
// 1 2 4 3 6 9 8 7 5
// 9
// 3 7 8 6 11 2 5 4 9
// 3 8 11 6 7 4 9 5 2

// Sample Output 1
// testcase1: 5 3 2 1 4 7 6 8 9 
// testcase2: 2 7 3 6 8 11 5 9 4 

// Hint
// Tree of sample input 1:
// Tree of sample input 2:

// Refers to https://www.geeksforgeeks.org/construct-a-binary-tree-from-postorder-and-inorder/

// SYC 2021 / 11 / 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ORDER_LENGTH 105

typedef struct node{
    int val;
    struct node *left;
    struct node *right;
}Node;

void show_arr(int *arr, int n){
    printf("Arr: ");
    for(int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void reverse(int *arr, int n){
    for(int i = 0, j = n - 1; i < n / 2; i++, j--){
        swap(&(arr[i]), &(arr[j]));
    }
}

Node *build_tree(int *inorder, int *postorder, int inorder_l, int inorder_r){
    Node *root = (Node*)malloc(sizeof(Node));
    int root_val = postorder[0], root_idx = 0;
    root->val = root_val;
    root->left = NULL;
    root->right = NULL;

    for(int i = inorder_l; i <= inorder_r; i++){
        if(inorder[i] == root_val){
            root_idx = i;
        }
    }

    // printf("Inorder [%d %d %d] | Root %d\n", inorder_l, root_idx, inorder_r, root_val);

    if(root_idx + 1 <= inorder_r){
        root->right = build_tree(inorder, &(postorder[1]), root_idx + 1, inorder_r);
    }
    int right_subtree_size = inorder_r - root_idx;
    if(inorder_l <= root_idx - 1){
        root->left = build_tree(inorder, &(postorder[right_subtree_size + 1]), inorder_l, root_idx - 1);
    }

    return root;
}

void preorder_traverse(Node *root, int *preorder, int reset){
    static int counter = 0;
    if(reset){
        counter = 0;
        return;
    }
    if(root != NULL){
        preorder[counter++] = root->val;

        if(root->left != NULL){
            preorder_traverse(root->left, preorder, 0);
        }
        if(root->right != NULL){
            preorder_traverse(root->right, preorder, 0);
        }
        free(root);
    }
}

void build_preorder(int *inorder, int *postorder, int *preorder, int n){
    // show_arr(postorder, n);
    reverse(postorder, n);
    // show_arr(postorder, n);
    Node *root = build_tree(inorder, postorder, 0, n - 1);
    preorder_traverse(root, preorder, 1);
    preorder_traverse(root, preorder, 0);
}

int main(){
    int n = 0, tc_count = 1;
    while(scanf("%d", &n) != EOF){
        int inorder[MAX_ORDER_LENGTH] = {0}, 
            postorder[MAX_ORDER_LENGTH] = {0},
            preorder[MAX_ORDER_LENGTH] = {0};

        // Scan Inorder
        for(int i = 0; i < n; i++){
            scanf("%d", &(inorder[i]));
        }
        // Scan Postorder
        for(int i = 0; i < n; i++){
            scanf("%d", &(postorder[i]));
        }

        build_preorder(inorder, postorder, preorder, n);

        // Print Preorder
        printf("testcase%d: ", tc_count++);
        for(int i = 0; i < n; i++){
            printf("%d ", preorder[i]);
        }
        printf("\n");
    }

    return 0;
}