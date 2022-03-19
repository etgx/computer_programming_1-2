#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <list>
#include <queue>

#define NULL_NODE -1

class Node{
    private:

    public:
    int x = 0, depth = 0, adj_n = 0;
    std::unordered_set<int> adjs;

    Node(){
        this->x = NULL_NODE;
        this->depth = this->adj_n = 0;
        this->adjs = std::unordered_set<int>();
    }

    Node(int x){
        this->x = x;
        this->depth = this->adj_n = 0;
        this->adjs = std::unordered_set<int>();
    }
};

class Tree{
    private:
    int N = 0, remain_nodes = 0, leaves_counter = 0;
    // std::unordered_map<int, Node> map;
    Node *map = NULL;

    bool is_null_node(int x){
        return this->map[x].x == NULL_NODE;
    }

    void set_null_node(int x){
        if(!this->is_null_node(x)){
            this->remain_nodes--;    
        }
        this->map[x].adjs.clear();
        this->map[x].x = NULL_NODE;
        this->map[x].depth = 0;
    }

    bool is_leaf(int a){
        return this->map[a].adj_n <= 1;
        // return this->map[a].adjs.size() <= 1;
    }

    void del_node(int x){
        Node *node = &(this->map[x]);
        for(std::unordered_set<int>::iterator it = node->adjs.begin(); it !=  node->adjs.end(); it++){
            this->map[*it].adjs.erase(x);
        }
        this->set_null_node(x);
    }

    void remove_node(int x){
        Node *node = &(this->map[x]);
        for(std::unordered_set<int>::iterator it = node->adjs.begin(); it !=  node->adjs.end(); it++){
            // this->map[*it].adjs.erase(x);
            this->map[*it].adj_n--;
        }
        // this->map.erase(x);
        this->set_null_node(x);
    }

    public:
    Tree(int N){
        this->N = N;
        this->remain_nodes = this->leaves_counter = 0;
        this->map = new Node[N+1];
        // this->map = std::unordered_map<int, Node>();
    }

    ~Tree(){
        for(int i = 0; i <= this->N; i++){
            this->map[i].adjs.clear();
        }
        delete [](this->map);
    }

    void add_edge(int a, int b){
        this->map[a].adjs.insert(b);
        this->map[a].adj_n++;
        this->map[b].adjs.insert(a);
        this->map[b].adj_n++;

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
            // if(this->map.find(i) == this->map.end()) continue;
            if(this->is_null_node(i)) continue;

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

    void remove_leaves(){
        std::unordered_set<int> del_nodes;
        for(int i = 1; i <= this->N; i++){;
            if((!this->is_null_node(i)) && this->is_leaf(i)){
                del_nodes.insert(i);
            }
        }
        for(std::unordered_set<int>::iterator it = del_nodes.begin(); it != del_nodes.end(); it++){
            this->del_node(*it);
        }
        del_nodes.clear();
    }

    int get_remain_nodes(){
        // Method 1.
        // int counter = 0;
        // for(int i = 1; i <= this->N; i++){
        //     if(!this->is_null_node(i)){
        //         counter++;
        //     }
        // }
        // return counter;

        // Method 2.
        return this->remain_nodes;
    }

    int get_k_round_remain_nodes(int K){
        // Method 1.
        int counter = 0;
        for(int i = 1; i <= this->N; i++){
            int d = this->map[i].depth;
            if(d > K || d == 0){
            // if(d > K){
                counter++;
            }
        }
        return counter;

        // Method 2.
        // return this->N - this->leaves_counter;
    }

    void build_depth(int K){
        // Enqueue leaves
        std::queue<int> leaf_queue = std::queue<int>();
        for(int i = 1; i < N + 1; i++){
            Node *temp = &(this->map[i]);
            if(this->is_leaf(i)){
                temp->depth = 1;
                for(std::unordered_set<int>::iterator it = temp->adjs.begin(); it != temp->adjs.end(); it++){
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
            if(temp->depth >= 1) continue;
            // show_queue(leaf_queue);

            // printf("[%d] Adjs:", temp->x);
            for(std::unordered_set<int>::iterator it = temp->adjs.begin(); it != temp->adjs.end(); it++){
                if(map[*it].depth >= 1){
                    traversed_count++;
                }
                // printf(" %d", *it);
            }
            // printf(" - traversed: %d | adjs: %d\n", traversed_count, adj_count);

            // if(traversed_count < adj_count - 1){
            //     leaf_queue.push(temp->x);
            // }else 
            if(traversed_count ==  adj_count - 1){
                int max_depth = temp->depth;
                bool is_alter_max = false;
                for(std::unordered_set<int>::iterator it = temp->adjs.begin(); it != temp->adjs.end(); it++){
                    if(map[*it].depth < 1){
                        // map[*it].depth = current_depth + 1;
                        leaf_queue.push(*it);
                    }else{
                        if(max_depth < map[*it].depth){
                            max_depth = map[*it].depth;
                            // is_alter_max = true;
                        }
                    }
                }
                // If the max depth change
                // if(is_alter_max){
                    temp->depth = max_depth + 1;
                // }
                // if(temp->depth > K + 1) return;
            }
            // show_queue(leaf_queue);
            // this->show(true);
        }
        // Root
        if(temp == NULL) return;
        int max_depth = temp->depth;
        for(std::unordered_set<int>::iterator it = temp->adjs.begin(); it != temp->adjs.end(); it++){
            if(max_depth < map[*it].depth){
                max_depth = map[*it].depth;
            }
        }
        temp->depth = max_depth + 1;
        // return temp;
    }

    int get_virtual_prune_remain(){
        // int counter = 0;
        // for(int i = 1; i <= this->N; i++){
        //     if(!this->is_null_node(i)){
        //         counter++;
        //     }
        // }
        // return counter;

        return this->remain_nodes;

        // return this->map.size();
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
            // if(this->map.find(front) == this->map.end()) continue;
            if(this->is_null_node(front)) continue;

            temp = &(map[front]);
            int adj_count = temp->adjs.size(), temp_x = temp->x, temp_depth = temp->depth;
            std::unordered_set<int> temp_adjs(temp->adjs);

            // printf("Iter: %d -> [%d]: %d\n", iter, temp_x, temp_depth);
            this->remove_node(temp_x);
            // show_queue(leaf_queue);
            
            for(std::unordered_set<int>::iterator it = temp_adjs.begin(); it != temp_adjs.end(); it++){
                // Adjacents of temp
                if((!this->is_null_node(front)) && this->is_leaf(*it)){
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

    int method1(int K){
        int last_remain_node = this->get_remain_nodes();
        for(int k = 0; k < K; k++){
            this->remove_leaves();
            if(this->get_remain_nodes() == last_remain_node) break;
            last_remain_node = this->get_remain_nodes();
        }
        printf("%d\n", this->get_remain_nodes());
        return this->get_remain_nodes();
    }

    int method2(int K){
        this->build_depth(K);
        printf("%d\n", this->get_k_round_remain_nodes(K));
        return this->get_k_round_remain_nodes(K);
    }

    int method3(int K){
        this->virtual_prune(K);
        printf("%d\n", this->get_virtual_prune_remain());
        return this->get_virtual_prune_remain();
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
        
        // tree.method1(K);
        // tree.method2(K);
        tree.method3(K);
    }
    return 0;
}