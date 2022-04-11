#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
// #include <utility>
// #include <functional>

class Edge{
    public:
    int dest = 0, weight = 0;
    Edge(int dest, int weight){
        this->dest = dest;
        this->weight = weight;
    }
};

class Node{
    public:
    int x = 0, dia0 = 0, dia1 = 0, dis0 = 0, dis1 = 0, is_traversed = 0;
    std::vector<Edge> adj = std::vector<Edge>();
    Node(){
        this->x = this->dia0 = this->dia1 = this->dis0 = this->dis1 = this->is_traversed = 0;
        this->adj = std::vector<Edge>();
    }
    Node(int x){
        this->x = x;
        this->dia0 = this->dia1 = this->dis0 = this->dis1 = this->is_traversed = 0;
        this->adj = std::vector<Edge>();
    }
};

bool comp_dis(std::pair<int, int> a, std::pair<int, int> b){
    return a.second < b.second;
}

class Tree{
    private:
    int n = 0;
    Node *map = NULL;

    public:
    Tree(int n){
        this->n = n;
        this->map = new Node[this->n];
        for(int i = 0; i < this->n; i++){
            this->map[i].x = 0;
        }
    }

    void add_edge(int a, int b, int w){
        this->map[a].adj.push_back(Edge(b, w));
        this->map[b].adj.push_back(Edge(a, w));
    }

    void show(){
        for(int i = 0; i < this->n; i++){
            printf("[%d]:", i);
            for(std::vector<Edge>::iterator it = this->map[i].adj.begin(); it != this->map[i].adj.end(); it++){
                printf(" %d(%d)", (*it).dest, (*it).weight);
            }
            printf("\n");
        }
    }

    int build(Node *root){
        if(root != NULL) return 0;

        if(root->adj.size() == 0){
            // Leaf
            
        }else{
            for(std::vector<Edge>::iterator it = root->adj.begin(); it != root->adj.end(); it++){
                Node &node = this->map[(*it).dest];
                if(!node.is_traversed){
                    this->build(&node);
                }
            }

            // Sort Distance
            std::vector<std::pair<int, int>> dis_v;
            for(std::vector<Edge>::iterator it = root->adj.begin(); it != root->adj.end(); it++){
                Node &node = this->map[(*it).dest];
                if(node.is_traversed){
                    dis_v.push_back(std::make_pair(node.x, node.dis0));
                }
            }

            std::sort(dis_v.begin(), dis_v.end(), comp_dis);
            root->dis0 = dis_v.at(0).second;
            root->dis1 = dis_v.at(1).second;

            // Sort Distance
            std::vector<std::pair<int, int>> dis_v;
            for(std::vector<Edge>::iterator it = root->adj.begin(); it != root->adj.end(); it++){
                Node &node = this->map[(*it).dest];
                if(node.is_traversed){
                    dis_v.push_back(std::make_pair(node.x, node.dis0));
                }
            }

            std::sort(dis_v.begin(), dis_v.end(), comp_dis);
            root->dis0 = dis_v.at(0).second;
            root->dis1 = dis_v.at(1).second;

            // Sort Diameter
            std::vector<std::pair<int, int>> dia_v;
            for(std::vector<Edge>::iterator it = root->adj.begin(); it != root->adj.end(); it++){
                Node &node = this->map[(*it).dest];
                if(node.is_traversed){
                    dia_v.push_back(std::make_pair(node.x, node.dia0));
                }
            }

            std::sort(dia_v.begin(), dia_v.end(), comp_dis);
            root->dia0 = dia_v.at(0).second;
            root->dia1 = dia_v.at(1).second;
        }
        root->is_traversed = 1;
    }

    int solve(){

    }
};

int main(){
    int n = 0;
    scanf("%d\n", &n);
    Tree tree(n);
    for(int i = 0; i < n - 1; i++){
        int u_i = 0, v_i = 0, w_i = 0;
        scanf("%d %d %d\n", &u_i, &v_i, &w_i);
        // printf("%d %d %d\n", u_i, v_i, w_i);
        tree.add_edge(u_i, v_i, w_i);
    }
    tree.show();
    return 0;
}