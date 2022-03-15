#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#define MAX_EXPR_LEN 260

typedef struct node{
    char x;
    struct node *left, *right;
}Node;

class SyntaxTree{
    private:
    Node *root = NULL;
    int pos = 0;

    bool is_OP(char x){
        return x == '&' || x == '|';
    }

    bool is_ID(char x){
        return x >= 'A' && x <= 'D';
    }

    Node* create_node(char x){
        Node *new_node = (Node*)malloc(sizeof(Node));
        new_node->x = x;
        new_node->left = new_node->right = NULL;
        return new_node;
    }

    Node* parse_factor(char *s){
        char x = s[this->pos];
        // int temp = this->pos;
        this->pos--;

        if(this->is_OP(x) || this->is_ID(x)){
            // OP / ID
            // printf("Create [%d]: %c\n", temp, x);
            return this->create_node(x);
        }else if(x == ')'){
            // (EXPR)
            // printf("Left Paraphrase [%d]: %c\n", temp, x);
            Node *root = this->parse_expr(s);
            // printf("right Paraphrase [%d]: %c\n", this->pos, s[this->pos]);
            this->pos--;
            
            return root;
        }
        return NULL;
    }

    Node* parse_expr(char *s){
        Node *root = NULL;
        if(this->pos >= 0){
            root = this->parse_factor(s);
            if(this->pos >= 0 && (this->is_OP(s[this->pos]))){
                Node *factor = root;
                root = this->create_node(s[this->pos]);
                this->pos--;
                root->right = factor;
                root->left = this->parse_expr(s);
                // printf("[%d]: %c - ", this->pos, root->x);
            }
            
        }
        return root;
    }

    void print_prefix(Node *root){
        if(root == NULL) return;

        print_prefix(root->left);
        printf("%c", root->x);

        bool is_paraphrase = root->right != NULL && this->is_OP(root->right->x);
        if(is_paraphrase){
            printf("(");
        }
        print_prefix(root->right);
        if(is_paraphrase){
            printf(")");
        }
    }

    public:
    SyntaxTree(){
        this->root = NULL;
    }

    Node* from_infix(char *s, int len){
        this->pos = len - 1;
        return this->root = this->parse_expr(s);;
    }

    void to_infix(){
        print_prefix(this->root);
        // printf("\n");
    }
};

int main(){
    char s[MAX_EXPR_LEN] = {0};
    scanf("%s\n", s);
    SyntaxTree syt = SyntaxTree();
    syt.from_infix(s, strlen(s));
    syt.to_infix();
    return 0;
}