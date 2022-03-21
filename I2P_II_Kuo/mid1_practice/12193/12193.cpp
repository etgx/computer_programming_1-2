#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

typedef struct node{
    int level, x;
    struct node *right, *left;
}Node;

class Tree{
    private:
    const int ROOT_LEVEL = 1;
    int max_level;
    struct node* root;

    int adding_node(Node **root, int x, int level){
        if(root == NULL) return level - 1;

        if(*root == NULL){
            Node *new_node = (Node*)malloc(sizeof(Node));
            new_node->level = level;
            new_node->x = x;
            new_node->left = new_node->right = NULL;

            *root = new_node;
            return level;
        }else{
            if(x > (*root)->x){
                return adding_node(&((*root)->right), x, level + 1);
            }else if(x < (*root)->x){
                return adding_node(&((*root)->left), x, level + 1);
            }else{
                // @IMPORTANT: Ignore the replicated number
                return 0;
            }
        }
    }

    void printing_tree(Node *root){
        if(root == NULL) return;

        printing_tree(root->left);
        printf("%d ", root->x);
        printing_tree(root->right);
    }

    int summing_level(Node *root, int level){
        if(root == NULL) return 0;

        int sum = 0;
        if(root->level == level){
            sum += root->x;
        }else if(root->level < level){
            sum += summing_level(root->left, level);
            sum += summing_level(root->right, level);
        }
        return sum;
    }

    void averaging_level(Node *root, int *sum, int *count, int level){
        if(root == NULL) return;

        if(root->level == level){
            (*sum) += root->x;
            (*count) += 1;
        }else if(root->level < level){
            averaging_level(root->left, sum, count, level);
            averaging_level(root->right, sum, count, level);
        }
    }

    void del_tree(Node *root){
        if(root == NULL) return;

        del_tree(root->left);
        del_tree(root->right);
        free(root);
    }

    public:
    Tree(){
        this->max_level = 0;
        this->root = NULL;
    }

    ~Tree(){
        del_tree(this->root);
    }

    void add_node(int x){
        int level = adding_node(&(this->root), x, this->ROOT_LEVEL);
        if(level > this->max_level){
            this->max_level = level;
        }
    }

    void print_tree(){
        if(this->root == NULL){
            printf("NULL\n");
        }else{
            printing_tree(this->root);
            printf("\n");
        }
    }

    int get_max(){
        return this->max_level;
    }

    int sum_level(int level){
        // @IMPORTANT: Check both case (1) Exceed the maximum level (2) Smaller than the root level 
        if(level > this->max_level || level < this->ROOT_LEVEL) return 0;
        return summing_level(this->root, level);
    }

    float average_level(int level){
        // @IMPORTANT: Check both case (1) Exceed the maximum level (2) Smaller than the root level 
        if(level > this->max_level || level < this->ROOT_LEVEL) return 0;
        int sum = 0, count = 0;
        averaging_level(this->root, &sum, &count, level);
        if(sum == 0 || level == 0) return (float)0;
        return (float)sum / (float)count;
    }
};

int main(){
    int N = 0, M = 0;
    Tree tree = Tree();
    scanf("%d", &N);

    for(int i = 0; i < N; i++){
        int x = 0;
        scanf("%d", &x);
        tree.add_node(x);
    }

    scanf("%d", &M);
    for(int i = 0; i < M; i++){
        char op[10] = {0};
        int x = 0;
        float avg = 0;

        scanf("%s", op);

        switch(op[0]){
            case 'A':
                scanf("%d\n", &x);
                avg = tree.average_level(x);
                if(avg == 0){
                    printf("0\n");    
                }else{
                    printf("%.3f\n", avg);
                }
                break;
            case 'S':
                scanf("%d\n", &x);
                printf("%d\n", tree.sum_level(x));
                break;
            case 'P':
                tree.print_tree();
                break;
            case 'G':
                printf("%d\n", tree.get_max());
                break;
        }
    }

    return 0;
}