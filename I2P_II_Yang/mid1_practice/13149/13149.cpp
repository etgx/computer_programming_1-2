#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#define MAX_INT_BUF 100
#define MAX_EXPR_BUF 

class Node{
    private:

    public:
    Node *left = NULL, *right = NULL;
    int id = 0, val = 0;

    Node(int id){
        this->id = id;
        this->val = 0;
        this->left = this->right = NULL;
    }
};

class TernaryTree{
    private:
    Node *root = NULL;
    int N = 0, pos = 0, max_id = 0;
    int *bins = NULL;

    Node *create_node(int id, Node *left, Node *right){
        Node *new_node = new Node(id);
        new_node->left = left;
        new_node->right = right;
        return new_node;
    }

    Node *create_node(int id){
        return this->create_node(id, NULL, NULL);
    }

    Node* parse_ternary(){
        char int_buf[MAX_INT_BUF] = {0};
        char c = getchar();

        for(int i = 0; c <= '9' && c >= '0' && i < MAX_INT_BUF; i++){
            int_buf[i] = c;
            c = getchar();
        }

        int id = atoi(int_buf);
        if(id > this->max_id){
            this->max_id = id;
        }
        Node *new_node = this->create_node(id);

        if(c == '?'){
            new_node->left = this->parse_ternary();
            // c = getchar();
            // if(c == ':'){
                new_node->right = this->parse_ternary();
            // }
        }

        return new_node;
    }

    void printing(Node *root){
        if(root == NULL) return;
        bool is_ternary = (root->right != NULL) && (root->left != NULL);

        printf("%d", root->id);
        if(is_ternary){
            printf("?");
        }
        this->printing(root->left);
        if(is_ternary){
            printf(":");
        }
        this->printing(root->right);
    }

    int eval(Node *root){
        if(root == NULL) return 0;

        int l = 0, r = 0, p = this->bins[root->id];
        if((root->left != NULL) && (root->right != NULL)){
            l = this->eval(root->left);
            r = this->eval(root->right);
            return p? l : r;
        }
        return p;
    }

    public:
    TernaryTree(){
        this->root = NULL;
        this->N = this->pos = this->max_id = 0;
        this->bins = NULL;
    }

    void show(){
        printf("\n==================\n");
        this->printing(this->root);
        printf("\n==================\n");
    }

    Node* parse(){
        return this->root = this->parse_ternary();
    }

    int testcase(){
        if(this->root == NULL) return 0;

        this->bins = new int[this->max_id+1];
        this->bins[0] = 0;

        for(int i = 1; i <= this->max_id; i++){
            char c = 0;
            scanf("%c", &c);

            if(c == '0'){
                this->bins[i] = 0;
            }else if(c == '1'){
                this->bins[i] = 1;
            }
        }
        scanf("\n");

        return this->eval(this->root);
    }
};

int main(){
    TernaryTree tree;
    tree.parse();
    // tree.show();

    int T = 0;
    scanf("%d\n", &T);
    for(int i = 0; i < T; i++){
        printf("%d\n", tree.testcase());
    }
    return 0;
}