#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SEQ_SIZE 15

// int check_single(int *preorder, int *postorder, int node_preorder_id, int num_node){
//     int node = preorder[node_preorder_id];
//     int node_postorder_id = 0;

//     for(int i = 0; i < num_node; i++){
//         if(postorder[i] == node){
//             node_postorder_id = i;
//         }
//     }

//     int interset_map[MAX_SEQ_SIZE] = {0};
//     for(int i = node_preorder_id + 1; i < num_node; i++){
//         interset_map[preorder[i]]++;
//     }
//     for(int i = node_postorder_id - 1; i >= 0; i--){
//         interset_map[postorder[i]]++;
        
//     }

//     int interset_size = 0;
//     for(int i = 0; i < num_node; i++){
//         if(interset_map[i] > 1){
//             interset_size++;
//         }
//     }

//     if(interset_size == 1){
//         return 1;
//     }else{
//         return 0;
//     }
// }

typedef struct node{
    int val;
    struct node *left;
    struct node *right;
}Node;

int count_bst(int *preorder, int *postorder, int post_l, int post_r, int reset){
    static int idx = 0;
    if(reset){
        idx = 0;
        return 0;
    }
    if(post_r >= post_l){
        idx++;
        if(post_r == post_l){
            // printf("IDX%d [%d == %d] -> 1\n", idx, post_l, post_r);
            return 1;
        }else if(post_r - post_l == 1){ 
            // printf("IDX%d [%d - %d] -> 2\n", idx, post_l, post_r);
            return 2;
        }else{
            int left_root = preorder[idx], left_root_post_idx = 0;
            for(int i = post_l; i <= post_r; i++){
                if(postorder[i] == left_root){
                    left_root_post_idx = i;
                    break;
                }
            }
            // printf("IDX%d [%d : %d] -> LRoot: [%d]: %d | [%d]: %d | [%d %d] | [%d %d]\n", idx, post_l, post_r, idx, left_root, left_root_post_idx, postorder[left_root_post_idx], post_l, left_root_post_idx, left_root_post_idx + 1,  post_r - 1);
            int left_count = count_bst(preorder, postorder, post_l, left_root_post_idx, 0);
            int right_count = count_bst(preorder, postorder, left_root_post_idx + 1,  post_r - 1, 0);
            // printf("IDX%d [%d : %d] * [%d : %d] -> %d * %d -> %d\n", idx, post_l, left_root_post_idx, left_root_post_idx + 1, post_r - 1, left_count, right_count, left_count * right_count);

            return left_count * right_count;
        }
    }
    return 1;
}

// Node *build_bst(int *preorder, int *postorder, int post_l, int post_r){
//     if(post_r >= post_l){
//         int pivot = preorder[0];
//         Node *new = (Node*)malloc(sizeof(Node));
//         new->val = pivot;
//         new->left = NULL;
//         new->right = NULL;
        
//         int left_root = preorder[1], left_root_post_idx = -1;
//         for(int i = post_l; i <= post_r; i++){
//             if(postorder[i] == left_root){
//                 left_root_post_idx = i;
//                 break;
//             }
//         }
//         printf("Partition: [%d : %d] -> M [%d]: %d | L [%d %d]: %d %d | R [%d %d] %d %d\n", post_l, post_r, left_root_post_idx, postorder[left_root_post_idx], post_l, left_root_post_idx - post_l, postorder[post_l], postorder[left_root_post_idx - post_l], left_root_post_idx + 1,  post_r - 1, postorder[left_root_post_idx + 1],  postorder[post_r - 1]);
//         if(left_root_post_idx >= 0){
//             new->left = build_bst(&(preorder[1]), postorder, post_l, left_root_post_idx - post_l);
//             new->right = build_bst(&(preorder[1]), postorder, left_root_post_idx + 1,  post_r - 1);
//         }
        
//         // printf("[%d : %d] * [%d : %d] -> %d * %d -> %d\n", post_l, left_root_post_idx - post_l, left_root_post_idx + 1, post_r - 1, left_count, right_count, left_count * right_count);
//         return new;
//     }
//     return NULL;
// }

Node *build_bst(int *preorder, int *postorder, int reset){
    static int preorder_idx = 0, postorder_idx = 0;
    if(reset){
        preorder_idx = 0;
        postorder_idx = 0;
        return NULL;
    }

    Node *new = (Node*)malloc(sizeof(Node));
    new->val = preorder[preorder_idx++];
    new->left = NULL;
    new->right = NULL;
    if(new->val != postorder[postorder_idx]){
        new->left = build_bst(preorder, postorder, 0);
    }
    if(new->val != postorder[postorder_idx]){
        new->right = build_bst(preorder, postorder, 0);
    }
    postorder_idx++;
    return new;
}

void get_preorder(Node *root, int *arr, Node **node_arr, int reset){
    static int i = 0;
    if(reset){
        i = 0;
        return;
    }
    if(root == NULL){
        return;
    }
    // arr[i] = root->val;
    // node_arr[i] = root;
    i++;
    printf("%d ", root->val);
    if(root->left != NULL){
        get_preorder(root->left, arr, node_arr, 0);
    }
    if(root->right != NULL){
        get_preorder(root->right, arr, node_arr, 0);
    }
}

void get_postorder(Node *root, int *arr, Node **node_arr, int reset){
    static int i = 0;
    if(reset){
        i = 0;
        return;
    }
    if(root == NULL){
        return;
    }
    if(root->left != NULL){
        get_preorder(root->left, arr, node_arr, 0);
    }
    if(root->right != NULL){
        get_preorder(root->right, arr, node_arr, 0);
    }
    // arr[i] = root->val;
    // node_arr[i] = root;
    i++;
    printf("%d ", root->val);
}

void get_inorder(Node *root, int *arr, Node **node_arr, int reset){
    static int i = 0;
    if(reset){
        i = 0;
        return;
    }
    if(root == NULL){
        return;
    }
    if(root->left != NULL){
        get_preorder(root->left, arr, node_arr, 0);
    }
    arr[i] = root->val;
    node_arr[i] = root;
    i++;
    printf("%d ", root->val);
    if(root->right != NULL){
        get_preorder(root->right, arr, node_arr, 0);
    }
}

void show_seq(int *arr, int n){
    for(int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int count_possible(int *preorder, int *postorder, int num_node){
    // build_bst(NULL, NULL, 1);
    // get_preorder(NULL, NULL, NULL, 1);
    // get_postorder(NULL, NULL, NULL, 1);

    // Node *root = build_bst(preorder, postorder, 0);
    
    // int *preorder_arr = (int*)malloc(sizeof(int) * num_node), *postorder_arr = (int*)malloc(sizeof(int) * num_node);
    // Node **preorder_node_arr = (Node**)malloc(sizeof(Node*) * num_node), **postorder_node_arr = (Node**)malloc(sizeof(Node*) * num_node);
    // int preorder_arr[MAX_SEQ_SIZE] = {0}, postorder_arr[MAX_SEQ_SIZE] = {0};
    // Node *preorder_node_arr[MAX_SEQ_SIZE] = {0}, *postorder_node_arr[MAX_SEQ_SIZE] = {0};
    
    // printf("\nPreorder: ");
    // get_preorder(root, preorder_arr, preorder_node_arr, 0);
    // printf("\nPostorder: ");
    // get_postorder(root, postorder_arr, postorder_node_arr, 0);
    // printf("\n");

    // printf("Preorder: ");
    // show_seq(preorder_arr, num_node);
    // printf("Postorder: ");
    // show_seq(postorder_arr, num_node);

    count_bst(NULL, NULL, 0, 0, 1);
    return count_bst(preorder, postorder, 0, num_node - 1, 0);
    // return 4;
}

int main(){
    int n = 0;
    
    while(scanf("%d", &n) != EOF){
        int preorder[MAX_SEQ_SIZE] = {0};
        int postorder[MAX_SEQ_SIZE] = {0};

        for(int i = 0; i < n; i++){
            scanf("%d", &(preorder[i]));
            // printf("%d ", preorder[i]);
        }
        // printf("\n");

        for(int i = 0; i < n; i++){
            scanf("%d", &(postorder[i]));
            // printf("%d ", postorder[i]);
        }
        // printf("\n");

        // printf("4\n");
        printf("%d\n", count_possible(preorder, postorder, n));
    }

    return 0;
}