#include "function.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Correct
void bst_build(Node **root, int *arr, int l, int r){
    // static int uid_count = 0;

    int pivot = (l + r) / 2;
    int val = arr[pivot];
    Node *node = (Node*)malloc(sizeof(Node));
    node->level = val;
    // node->uid = uid_count;
    node->left_child = NULL;
    node->right_child = NULL;
    (*root) = node;
    // printf("<%d %d> - [%d]: %d UID: %d\n", l, r, pivot, val, uid_count);
    // uid_count++;

    if((l + pivot) / 2 != pivot){
        bst_build(&(node->left_child), arr, l, pivot);
    }
    if((pivot + r) / 2 != pivot){
        bst_build(&(node->right_child), arr, pivot+1, r);
    }
}

// Correct, but more clear
void bst_build2(Node **root, int *arr, int l, int r){
    if(l <= r){
        int pivot = (l + r) / 2;
        int val = arr[pivot];
        Node *node = (Node*)malloc(sizeof(Node));
        node->level = val;
        node->left_child = NULL;
        node->left_child = NULL;
        (*root) = node;

        bst_build2(&(node->left_child), arr, l, pivot - 1);
        bst_build2(&(node->right_child), arr, pivot + 1, r);
    }
}

void build_tree(Node **now, int *arr, int l, int r){
    // bst_build(now, arr, l, r + 1);
    bst_build2(now, arr, l, r);
}

typedef struct node_pair{
    Node *node;
    Node *parent;
}NodePair;

// Correct
NodePair find(Node *root, int x){
    NodePair pair;
    pair.node = root;
    pair.parent = NULL;

    while(1){
        if(pair.node->level == x){
            break;
        }else if(pair.node->level > x && pair.node->left_child != NULL){
            pair.parent = pair.node;
            pair.node = pair.node->left_child;
        }else if(pair.node->level < x && pair.node->right_child != NULL){
            pair.parent = pair.node;
            pair.node = pair.node->right_child;
        }else{
            pair.parent = NULL;
            pair.node = NULL;
            break;
        }
    }
    return pair;
}

// Correct
Node* find2(Node *root, int x){
    if(root == NULL){
        return NULL;
    }
    if(root->level > x){
        return find2(root->left_child, x);
    }else if(root->level < x){
        return find2(root->right_child, x);
    }else{
        return root;
    }
}

int query_heatstroke(Node *now, int x){
    if(now == NULL){
        return 0;
    }
    // NodePair res = find(now, x);
    // if(res.node == NULL){
    //     return 0;
    // }else{
    //     return 1;
    // }
    Node *res = find2(now, x);
    if(res == NULL){
        return 0;
    }else{
        return 1;
    }
}

// NodePair find_max(Node *root, Node *root_parent){
//     NodePair pair;
//     pair.node = root;
//     pair.parent = root_parent;

//     while(pair.node->right_child != NULL){
//         pair.parent = pair.node;
//         pair.node = pair.node->right_child;
//     }
//     return pair;
// }

NodePair find_min(Node *root, Node *root_parent){
    NodePair pair;
    pair.node = root;
    pair.parent = root_parent;

    while(pair.node->left_child != NULL){
        pair.parent = pair.node;
        pair.node = pair.node->left_child;
    }
    return pair;
}

void eat_rat(Node **root, int x){
    if(*root == NULL){
        return;
    }
    
    NodePair pair = find(*root, x);
    Node *res = pair.node, *res_parent = pair.parent;

    if(res == NULL){
        return;
    }else{
        NodePair substitute_pair;
        if(res->left_child == NULL && res->right_child == NULL){
            if(res_parent != NULL){
                // Edge case: When res == root, res_parent is NULL
                if(res_parent->left_child == res){
                    res_parent->left_child = NULL;
                }else if(res_parent->right_child == res){
                    res_parent->right_child = NULL;
                }
            }else{
                *root = NULL;
            }
            // printf("L = R = NULL\n");
            free(res);
        }else if(res->left_child == NULL){
            Node *delete_node = res->right_child;
            res->level = delete_node->level;
            res->left_child = delete_node->left_child;
            res->right_child = delete_node->right_child;
            free(delete_node);
        }else if(res->right_child == NULL){
            Node *delete_node = res->left_child;
            res->level = delete_node->level;
            res->left_child = delete_node->left_child;
            res->right_child = delete_node->right_child;
            free(delete_node);
        }else{
            substitute_pair = find_min(res->right_child, res);
            if(substitute_pair.parent->left_child == substitute_pair.node){
                substitute_pair.parent->left_child = substitute_pair.node->right_child;
            }else{
                // Edge case: If substitute_pair.parent == res, we don't know whether kill right/left child
                substitute_pair.parent->right_child = substitute_pair.node->right_child;
            }
            // printf("Search Right, Find Min, Sub [%d]: %d -> [%d]: %d\n", res->uid, res->level, substitute_pair.node->uid, substitute_pair.node->level);
            res->level = substitute_pair.node->level;
            // printf("R = NULL\n");
            free(substitute_pair.node);
        }
    }
}