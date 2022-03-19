#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

class Node{
    public:
    int x = 0;
    Node *left = NULL, *right = NULL;

    Node(int x){
        this->x = x;
        this->left = this->right = NULL;
    }
};

class Tree{
    private:
    const int PREORDER_MODE = 0, INORDER_MODE = 1, POSTORDER_MODE = 2;
    std::vector<int> postorder, inorder;
    std::unordered_map<int, int> inorder_map;
    int n = 0;
    Node *root = NULL;

    Node* bulding_tree(int post_start, int post_end, int in_start, int in_end){
        // printf("-----------------\n");
        // printf("Post <%d %d> | In <%d %d>\n", post_start, post_end, in_start, in_end);
        if(post_end - post_start < 0 || in_end - in_start < 0) return NULL;

        int root_val = this->postorder[post_end];
        // printf("Root: %d ", root_val);
        Node *root = new Node(root_val);
        int root_inorder_idx = inorder_map[root_val];
        // printf("Idx: %d\n", root_inorder_idx);
        // printf("-----------------\n");
        int left_seg_size = root_inorder_idx - in_start, right_seg_size = in_end - root_inorder_idx;
        
        if(left_seg_size > 0){
            root->left = bulding_tree(post_start, post_start + left_seg_size - 1, in_start, in_start + left_seg_size - 1);
        }

        if(right_seg_size > 0){
            root->right = bulding_tree(post_end - right_seg_size, post_end - 1, root_inorder_idx + 1, root_inorder_idx + right_seg_size);
        }

        return root;
    }

    void answering(Node *root){
        if(root == NULL) return;

        if(root == this->root){
            printf("%d", root->x);
        }else{
            printf(" %d", root->x);
        }

        this->answering(root->left);
        this->answering(root->right);
    }

    void printing(Node *root, int mode){
        if(root == NULL) return;

        if(mode == this->PREORDER_MODE){
            printf("%d ", root->x);
        }

        this->printing(root->left, mode);

        if(mode == this->INORDER_MODE){
            printf("%d ", root->x);
        }

        this->printing(root->right, mode);

        if(mode == this->POSTORDER_MODE){
            printf("%d ", root->x);
        }
    }

    public:
    Tree(std::vector<int> postorder){
        this->inorder = std::vector<int>(postorder);
        this->postorder = postorder;
        std::sort(this->inorder.begin(), this->inorder.end());

        this->n = postorder.size();
        this->inorder_map = std::unordered_map<int, int>();
        for(int i = 0; i < this->n; i++){
            this->inorder_map[this->inorder[i]] = i;
        }

        this->root = NULL;
    }

    void build_tree(){
        this->root = this->bulding_tree(0, this->n - 1, 0, this->n - 1);
    }

    void preorder_print(){
        printf("\n==================\nPRE: ");
        this->printing(this->root, this->PREORDER_MODE);
        printf("\n==================\n");
    }

    void inorder_print(){
        printf("\n==================\nIN: ");
        this->printing(this->root, this->INORDER_MODE);
        printf("\n==================\n");
    }

    void postorder_print(){
        printf("\n==================\nPost: ");
        this->printing(this->root, this->POSTORDER_MODE);
        printf("\n==================\n");
    }

    void answer(){
        this->answering(this->root);
        printf("\n");
    }
};

int main(){
    int temp = 0;
    std::vector<int> postorder;

    while(scanf("%d", &temp) != EOF){
        postorder.push_back(temp);
    }

    Tree tree(postorder);
    tree.build_tree();
    // tree.preorder_print();
    // tree.inorder_print();
    // tree.postorder_print();
    tree.answer();
    return 0;
}