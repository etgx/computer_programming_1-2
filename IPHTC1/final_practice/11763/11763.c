// NTHUOJ 11763 - F - Bipartite Graph   
// Description
// Writer: jjjjj19980806       Description: pclightyear        Difficulty: ★★★★☆
// Given an undirected graph G, you have to check whether it is a bipartite graph (二分圖) or not.

// Input
// The first line contains an integer T, representing the number of test cases.
// For each test case:
// The first line contains two integers n, m, representing the number of vertices and the number of edges.
// The next m lines contain two integers u, v, representing that there is an undirected edge between vertex u and vertex v.
// It is guaranteed that:
// 1 ≤ T ≤ 10
// 2 ≤ n ≤ 1000
// n-1 ≤ m ≤ n2
// 1 ≤ u, v ≤ 1000
// NO multiple edge
// NO self cycle
// the graph is connected
 

// Output
// For each graph G, if G is a bipartite graph, please output "Yes", otherwise please output "No".

// Sample Input  
// 3

// 2 1
// 1 2

// 4 4
// 1 2
// 2 3
// 3 4
// 4 1

// 3 3
// 1 2
// 1 3
// 2 3

// Sample Output  
// Yes
// Yes
// No

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Red 1
#define Blue 2
#define Unlabel 0

typedef struct node{
    int data;
    struct node *next;
}Node;

typedef struct queue{
    Node *head;
    Node *tail;
}Queue;

Queue *newQueue(){
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->head = (Node *)malloc(sizeof(Node));
    q->tail = q->head;
    // Set up dump head node
    q->head->data = 0;
    q->head->next = NULL;
    return q;
}

int push(Queue *q, const int data){
    // Allocate new Node
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    
    // Push new node to tail
    q->tail->next = newNode;
    q->tail = newNode;
    // printf("Push: %d, Head: %d\n", q->tail->data, q->head->data);
    return data;
}

int pop(Queue *q){
    if(q->head == q->tail){return -1;}

    Node *del = q->head->next;
    int delData = del->data;

    // printf("Del: %d\n", delData);
    if(q->head->next == q->tail){
        q->tail = q->head;
    }
    q->head->next = del->next;
    free(del);

    return delData;
}

int isEmpty(Queue *q){
    return q->head == q->tail;
}

void **malloc2d(const int unitSize, const int rows, const int cols){
    void **mat = (void **)malloc(sizeof(void*) * rows);
    for(int i = 0; i < rows; i++){
        mat[i] = (void *)malloc(unitSize * cols);
        memset(mat[i], 0, sizeof(int) * cols);
    }
    return mat;
}

void free2d(void **mat ,const int rows){
    for(int i = 0; i < rows; i++){
        free(mat[i]);
    }
}

int reverseColor(const int currentColor){
    if(currentColor == Red){return Blue;}
    else if(currentColor == Blue){return Red;}
    else{return Unlabel;}
}

int solve(int **graph, const int n){
    // Color: Red, Blue
    int current = 0;
    int *record = (int *)malloc(sizeof(int) * n);
    Queue *q = newQueue();

    memset(record, 0, sizeof(int) * n);
    record[current] = Red;
    push(q, current);
    while(!isEmpty(q)){
        int drawingColor = 0;

        current = pop(q);
        // printf("Current: %d with Color: %d\n", current, record[current]);
        drawingColor = reverseColor(record[current]);
        
        for(int i = 0; i < n; i++){
            if(current == i || graph[current][i] == 0){continue;}
            if(!record[i]){
                // printf("Drawing Node: %d with Color: %d\n", i, drawingColor);
                record[i] = drawingColor;
            }else if(record[i] == record[current]){

                return 0;
            }

            graph[current][i] = graph[i][current] = 0;
            push(q, i);
            // printf("Push vertex: %d\n", i);
        }
    }

    return 1;
}

int main(){
    int T = 0;
    scanf("%d\n", &T);
    // printf("TestCase: %d\n", T);
    for(int i = 0; i < T; i++){
        // Read number of Vertice(n) and number of Edges(m)
        int n = 0, m = 0;
        scanf("%d %d\n", &n, &m);
        // printf("======================\nVertice: %d Edges: %d\n", n, m);
        int **graph = (int **)malloc2d(sizeof(int), n, n);

        // Read Edges
        for(int j = 0; j < m; j++){
            int a = 0, b = 0;
            scanf("%d %d\n", &a, &b);
            // printf("Edge: (%d, %d)\n", a, b);
            graph[a - 1][b - 1] = graph[b - 1][a - 1] = 1;
        }

        int res = solve(graph, n);
        if(res){
            printf("Yes\n");
        }else{
            printf("No\n");
        }

        free2d((void **)graph, n);
    }


    return 0;
}