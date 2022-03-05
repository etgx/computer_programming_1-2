typedef struct _NODE
{
    int number;
    struct _NODE *ptr_to_right_node;
    struct _NODE *ptr_to_left_node;
} Node;

Node* buildTree(int* Inorder, int* Preorder, int inorder_start, int inorder_end);

void showPostorder(Node* root);

void freeTree(Node *root);