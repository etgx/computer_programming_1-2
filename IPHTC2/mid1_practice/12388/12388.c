#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

#define SIZE_OF_INT sizeof(int)
#define EXIST_MSG "We might as well eat it."
#define NOT_FOUND_MSG "No dinner tonight."

int main(){
    int n = 0, q = 0;
    scanf("%d\n", &n);
    int *sorted_arr = (int*)malloc(SIZE_OF_INT * n);
    for(int i = 0; i < n; i++){
        scanf("%d", &(sorted_arr[i]));
    }

    Node *root = NULL;
    build_tree(&root, sorted_arr, 0, n - 1);
    // print_inorder(root);
    // printf("------\n");

    scanf("%d\n", &q);
    for(int i = 0; i < q; i++){
        int x = 0;
        scanf("%d", &x);

        int is_exist = query_heatstroke(root, x);
        if(is_exist){
            // printf("X: %d, Exist\n", x);
            eat_rat(&root, x);
            printf("%s\n", EXIST_MSG);
        }else{
            // printf("X: %d, Not Exist\n", x);
            printf("%s\n", NOT_FOUND_MSG);
        }

        // print_inorder(root);
        // printf("------\n");
    }
    return 0;
}