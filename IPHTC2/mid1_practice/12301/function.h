typedef struct _Node{
    int number;
    struct _Node* next;
}Node;

Node *createList(int n);

void freeList(Node* head);

int solveJosephus(Node **head, int step);
