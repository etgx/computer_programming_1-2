#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <queue>

#define NULL_NODE -1

class Node{
    private:

    public:
    int x = 0, depth = 0;
    std::unordered_set<int> adjs;

    Node(){
        this->x = NULL_NODE;
        this->depth = 0;
        this->adjs = std::unordered_set<int>();
    }

    Node(int x){
        this->x = x;
        this->depth = 0;
        this->adjs = std::unordered_set<int>();
    }
};

class Tree{
    private:
    int N = 0, remain_nodes = 0, leaves_counter = 0;
    std::unordered_map<int, Node> map;

    bool is_null_node(int x){
        return this->map[x].x == NULL_NODE;
    }

    bool is_leaf(int a){
        return this->map[a].adjs.size() <= 1;
    }

    void remove_node(int x){
        Node *node = &(this->map[x]);
        for(std::unordered_set<int>::iterator it = node->adjs.begin(); it !=  node->adjs.end(); it++){
            this->map[*it].adjs.erase(x);
        }
        this->map.erase(x);
    }

    public:
    Tree(int N){
        this->N = N;
        this->remain_nodes = this->leaves_counter = 0;
        this->map = std::unordered_map<int, Node>();
    }

    ~Tree(){
        for(int i = 0; i <= this->N; i++){
            this->map[i].adjs.clear();
        }
    }

    void add_edge(int a, int b){
        this->map[a].adjs.insert(b);
        this->map[b].adjs.insert(a);

        if(this->is_null_node(a)){
            this->remain_nodes++;
            this->map[a].x  = a;
        }
        if(this->is_null_node(b)){
            this->remain_nodes++;
            this->map[b].x  = b;
        }
    }    

    void show(bool is_show_depth){
        printf("============================\n");
        printf("Remain: %d\n", this->remain_nodes);
        printf("----------------------------\n");
        for(int i = 1; i <= N; i++){
            if(this->map.find(i) == this->map.end()) continue;

            Node *node = &(this->map[i]);
            printf("[%d(%d)]:", i, node->depth);
            for(std::unordered_set<int>::iterator it = node->adjs.begin(); it != node->adjs.end(); it++){
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

    int get_virtual_prune_remain(){
        return this->map.size();
    }

    void virtual_prune(int K){
        // Enqueue leaves
        std::queue<int> leaf_queue = std::queue<int>();
        for(int i = 1; i < N + 1; i++){
            Node *temp = &(this->map[i]);

            if(this->is_leaf(i) && (!this->is_null_node(i))){
                temp->depth = 1;
                if(temp->depth <= K){
                    leaf_queue.push(i);
                }
            }
        }
        // show_queue(leaf_queue);

        // BFS
        Node *temp = NULL;
        int iter = 0;
        for(; !leaf_queue.empty();){
            int front = leaf_queue.front();
            leaf_queue.pop();
            if(this->map.find(front) == this->map.end()) continue;

            temp = &(map[front]);
            int adj_count = temp->adjs.size(), temp_x = temp->x, temp_depth = temp->depth;
            std::unordered_set<int> temp_adjs(temp->adjs);

            // printf("Iter: %d -> [%d]: %d\n", iter, temp_x, temp_depth);
            this->remove_node(temp_x);
            // show_queue(leaf_queue);
            
            for(std::unordered_set<int>::iterator it = temp_adjs.begin(); it != temp_adjs.end(); it++){
                // Adjacents of temp
                if(this->is_leaf(*it)){
                    int max_depth = this->map[*it].depth > temp_depth? this->map[*it].depth : temp_depth;
                    // printf("[%d]: depth: %d | ADJS: ", *it, max_depth);
                    // // Adjacents of adjacents of temp
                    // for(std::unordered_set<int>::iterator it_it = this->map[*it].adjs.begin(); it_it != this->map[*it].adjs.end(); it_it++){
                    //     printf(" [%d]: %d,", *it_it, map[*it_it].depth);
                    // }

                    // If the max depth change
                    this->map[*it].depth = max_depth + 1;
                    // printf(" | -> [%d]: max depth: %d ", *it, this->map[*it].depth);
                    if(this->map[*it].depth <= K){
                        // printf(" ENQUEUE\n");
                        leaf_queue.push(*it);
                    }else{
                        // printf("\n");
                    }
                }
            }
            // this->show(true);
            iter++;
            
        }
    }
};

int main(){
    int T = 0;
    scanf("%d", &T);

    for(int i = 0; i < T; i++){
        int N = 0, K = 0;
        scanf("%d %d\n", &N, &K);
        Tree tree(N);

        for(int j = 0; j < N - 1; j++){
            int u_i = 0, v_i = 0;
            scanf("%d %d\n", &u_i, &v_i);

            // printf("T: %d | N: %d, K: %d | u_i: %d, v_i: %d\n", T, N, K, u_i, v_i);
            tree.add_edge(u_i, v_i);
        }
        
        tree.virtual_prune(K);
        printf("%d\n", tree.get_virtual_prune_remain());
    }
    return 0;
}