#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <set>
#include <queue>

// using namespace std;

// typedef struct node{
//     int x = 0, depth = 0;
//     std::set<int> adjs = std::set<int>();
// }Node;

class Node{
    private:

    public:
    int x = 0, depth = 0;
    std::set<int> adjs;

    Node(int x){
        this->x = x;
        this->depth = 0;
        this->adjs = std::set<int>();
    }
};

class Tree{
    private:
    int N = 0;
    Node *map = NULL;

    public:
    Tree(int N){
        this->N = N;
        this->map = (Node*)malloc(sizeof(Node) * (N + 1));
        for(int i = 0; i <= N; i++){
            this->map[i] = Node(i);
            // If use struct define the class Node, use following code to initialize the node;
            // this->map[i].depth = 0;
            // this->map[i].adjs = std::set<int>();
        }
    }

    ~Tree(){

    }

    void add_edge(int a, int b){
        // std::cout << this->map[a].adjs.size() << "\n";
        this->map[a].adjs.insert(b);
        this->map[b].adjs.insert(a);
    }

    bool is_leaf(int a){
        return this->map[a].adjs.size() <= 1;
    }

    void show(bool is_show_depth){
        printf("============================\n");
        for(int i = 1; i <= N; i++){
            Node *node = &(this->map[i]);
            printf("[%d(%d)]:", i, node->depth);
            for(std::set<int>::iterator it = node->adjs.begin(); it != node->adjs.end(); it++){
                printf(" %d", *it);
            }
            printf("\n");
        }
        printf("============================\n");
    }

    void show_queue(std::queue<int> q){
        int queue_size = q.size();
        printf("Queue(%d):", queue_size);
        for(int i = 0; i < queue_size; i++){
            int temp = q.front();
            q.pop();
            q.push(temp);
            printf(" %d", temp);
        }
        printf("\n");
    }

    Node *build_depth(){
        // Enqueue leaves
        std::queue<int> leaf_queue = std::queue<int>();
        for(int i = 1; i < N + 1; i++){
            Node *temp = &(this->map[i]);
            if(this->is_leaf(i)){
                temp->depth = 1;
                for(std::set<int>::iterator it = temp->adjs.begin(); it != temp->adjs.end(); it++){
                    leaf_queue.push(*it);
                }
            }
        }
        // show_queue(leaf_queue);

        // BFS
        Node *temp = NULL;
        for(; !leaf_queue.empty();){
            temp = &(map[leaf_queue.front()]);
            int current_depth = temp->depth, traversed_count = 0, adj_count = temp->adjs.size();
            leaf_queue.pop();
            // show_queue(leaf_queue);

            printf("[%d] Adjs:", temp->x);
            for(std::set<int>::iterator it = temp->adjs.begin(); it != temp->adjs.end(); it++){
                if(map[*it].depth >= 1){
                    traversed_count++;
                }
                printf(" %d", *it);
            }
            printf(" - traversed: %d | adjs: %d\n", traversed_count, adj_count);

            if(traversed_count < adj_count - 1){
                leaf_queue.push(temp->x);
            }else if(traversed_count ==  adj_count - 1){
                int max_depth = temp->depth;
                bool is_alter_max = false;
                for(std::set<int>::iterator it = temp->adjs.begin(); it != temp->adjs.end(); it++){
                    if(map[*it].depth < 1){
                        // map[*it].depth = current_depth + 1;
                        leaf_queue.push(*it);
                    }else{
                        if(max_depth < map[*it].depth){
                            max_depth = map[*it].depth;
                            is_alter_max = true;
                        }
                    }
                }
                // If the max depth change
                if(is_alter_max){
                    temp->depth = max_depth + 1;
                }
            }
            // show_queue(leaf_queue);
            this->show(true);
        }
        // Root
        int max_depth = temp->depth;
        for(std::set<int>::iterator it = temp->adjs.begin(); it != temp->adjs.end(); it++){
            if(max_depth < map[*it].depth){
                max_depth = map[*it].depth;
            }
        }
        temp->depth = max_depth + 1;
        return temp;
    }
};

int main(){
    int T = 0;
    std::cin >> T;

    for(int i = 0; i < T; i++){
        int N = 0, K = 0;
        scanf("%d %d\n", &N, &K);
        Tree tree(N);

        for(int j = 0; j < N - 1; j++){
            int u_i = 0, v_i = 0;
            scanf("%d %d\n", &u_i, &v_i);

            printf("T: %d | N: %d, K: %d | u_i: %d, v_i: %d\n", T, N, K, u_i, v_i);
            tree.add_edge(u_i, v_i);
        }
        tree.show(false);
        tree.build_depth();
        tree.show(true);
    }
    return 0;
}