#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>
#define MAX_FACTOR_BITS 40

typedef enum operator_type {AND, OR, NONE} OperatorType;
typedef enum token_type {OP, FACTOR} TokenType;

typedef struct token{
    int factor;
    OperatorType op;
    TokenType type;
}Token;

typedef struct node{
    Token token;
    int val;
    struct node *left, *right, *parent;
}Node;

class BooleanTree{
    private:
    const char SYMBOLS[3] = {'&', '|', '\0'};
    Node *root = NULL, **map = NULL;
    std::vector<Token> prefix;
    int building_idx = 0, N = 0;

    Node* create_node(Token t){
        Node *new_node = (Node*)malloc(sizeof(Node));
        new_node->token = t;
        new_node->val = 0;
        new_node->left = new_node->right = new_node->parent = NULL;
        return new_node;
    }

    Node* building_tree(Node *parent){
        // printf("HELLO %d : %d\n", this->building_idx, (int)this->prefix.size());
        if(this->building_idx >= this->prefix.size()) return NULL;
        // printf("HI\n");

        Token t = this->prefix[this->building_idx];
        Node *new_node = create_node(t);
        if(t.type == FACTOR){
            // IMPORTANT: If current node is an factor, only build the single node.
            this->map[t.factor] = new_node;
        }
        new_node->parent = parent;
        this->building_idx++;

        if(t.type == OP){
            // IMPORTANT: If current node is an operator, build the subtrees of it.
            new_node->left = this->building_tree(new_node);
            new_node->right = this->building_tree(new_node);
        }
        return new_node;
    }

    void printing_tree(Node *root){
        if(root == NULL) return;
        // printf("[%d]\n", root->token.factor);
        this->printing_tree(root->left);

        if(root->token.type == OP){
            // IMPORTANT: You should print the operators with SYMBOLS array.
            printf("%c", this->SYMBOLS[root->token.op]);
        }else{
            printf("%d", root->token.factor);
        }

        bool is_paraphrase =  root->right != NULL && root->right->token.type == OP;

        if(is_paraphrase){
            printf("(");
        }
        this->printing_tree(root->right);
        if(is_paraphrase){
            printf(")");
        }
    }

    void printing_val(Node *root){
        if(root == NULL) return;

        this->printing_val(root->left);
        this->printing_val(root->right);

        if(root->left != NULL && root->right != NULL){
            if(root->left->token.type == OP){
                printf("%d", root->left->val);
            }else if(root->left->token.type == FACTOR){
                printf("[%d]: %d", root->left->token.factor, root->left->val);
            }

            printf(" %c ", this->SYMBOLS[root->token.op]);

            if(root->right->token.type == OP){
                printf("%d", root->right->val);
            }else if(root->right->token.type == FACTOR){
                printf("[%d]: %d", root->right->token.factor, root->right->val);
            }

            printf(" -> %d\n", root->val);
        }
    }

    void flipping(Node *node){
        // printf("[%d]: %d -> %d\n",node->token.factor, node->val, node->val ^ 1);
        if(node == NULL) return;

        node->val = node->val ^ 1;
        if(node->parent != NULL && node->parent->left != NULL && node->parent->right != NULL){
            int parent_val = node->parent->val, parent_left_val = node->parent->left->val, parent_right_val = node->parent->right->val;
            OperatorType op = node->parent->token.op;

            // if(op == AND){
            //     printf("[%d]: %d <- %d = [%d]: %d & [%d]: %d\n", node->parent->token.factor, parent_val, parent_left_val & parent_right_val, node->parent->left->token.factor, parent_left_val, node->parent->right->token.factor, parent_right_val);
            // }

            // if(op == OR){
            //     printf("[%d]: %d <- %d = [%d]: %d | [%d]: %d\n", node->parent->token.factor, parent_val, parent_left_val | parent_right_val, node->parent->left->token.factor, parent_left_val, node->parent->right->token.factor, parent_right_val);
            // }
            // printf("Flipping\n");
            // this->show_val();

            // IMPORTANT: Notice that you should add paraphrases in the statement or the statement would be wrong.
            if((op == AND && (parent_val != (parent_left_val & parent_right_val))) ||
               (op == OR && (parent_val != (parent_left_val | parent_right_val)))){
                   this->flipping(node->parent);
            }
        }
    }

    void del_tree(Node *root){
        if(root == NULL) return;

        del_tree(root->left);
        del_tree(root->right);
        free(root);
    }

    public:
    static bool is_operator(char x){
        return x == '&' || x == '|';
    }

    static Token create_token(char op){
        Token t;
        if(op == '&'){
            t.op = AND;
        }else if(op == '|'){
            t.op = OR;
        }else{
            t.op = NONE;
        }
        t.factor = 0;
        t.type = OP;
        return t;
    }

    static Token create_token(int factor){
        Token t;
        t.op = NONE;
        t.factor = factor;
        t.type = FACTOR;
        return t;
    }

    BooleanTree(int N){
        this->root = NULL;
        this->prefix = std::vector<Token>();
        this->N = N;
        map = (Node**)malloc(sizeof(Node*) * 100001);
        memset(map, 0, sizeof(Node*) * 100001);
    }

    ~BooleanTree(){
        free(map);
        this->del_tree(this->root);
    }

    void add_operator(char op){
        this->prefix.push_back(BooleanTree::create_token(op));
    }

    void add_factor(int factor){
        this->prefix.push_back(BooleanTree::create_token(factor));
    }

    Node* build_tree(){
        this->building_idx = 0;
        return this->root = this->building_tree(NULL);
    }

    void show_infix(){
        this->printing_tree(this->root);
        printf("\n");
    }

    void show_prefix(){
        printf("Len: %ld - ", this->prefix.size());
        for(std::vector<Token>::iterator it = this->prefix.begin(); it != this->prefix.end(); it++){
            if((*it).type == OP){
                printf("%c", this->SYMBOLS[(*it).op]);
            }else if((*it).type == FACTOR){
                printf("%d", (*it).factor);
            }
        }
        printf("\n");
    }

    void show_val(){
        printf("\n===============\n");
        this->printing_val(this->root);
        printf("===============\n");
    }

    void flip(int i){
        if(i > this->N) return;

        Node *temp = this->map[i];
        this->flipping(temp);
    }

    int eval(){
        if(this->root == NULL) return 0;
        return this->root->val;
    }
};

int main(){
    int T = 0;
    scanf("%d\n", &T);

    for(int i = 0; i < T; i++){
        int N = 0, M = 0;
        scanf("%d %d\n", &N, &M);
        BooleanTree tree = BooleanTree(N);

        char c = getchar();
        for(; c != '\n'; ){
            // printf("%c\n", c);
            if(BooleanTree::is_operator(c)){
                tree.add_operator(c);
            }else if(c == '['){
                char buff[MAX_FACTOR_BITS] = {0};
                c = getchar();

                for(int k = 0; c >= '0' && c <= '9' && c != ']'; k++){
                    buff[k] = c;
                    c = getchar();
                }
                tree.add_factor(atoi(buff));
            }
            c = getchar();
        }
        tree.build_tree();
        // tree.show_infix();
        // tree.show_prefix();

        for(int j = 0; j < M; j++){
            int flip = 0;
            scanf("%d", &flip);

            tree.flip(flip);
            // tree.show_val();
            printf("%d\n", tree.eval());
        }
    }

    return 0;
}