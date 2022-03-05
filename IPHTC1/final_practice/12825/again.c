// Another AC Version
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define StrSize 1005
#define RecordSize 130

typedef struct node{
    char str[StrSize];
    int label; // if = 0, no one visit before. If >= 1, represent the Label of the group belongs to.
    // char *record;
}Node;

void strComp(char *dest, char *str){ // String Compression
    char record[RecordSize] = {0};
    for(int i = 0; str[i] != '\0' && i < StrSize; i++){
        record[str[i]] = 1;
    }
    int strCount = 0;
    for(int i = 0; i < RecordSize; i++){
        if(record[i]){
            dest[strCount] = i;
            strCount++;
        }
    }
    dest[strCount] = '\0';
}

void recordStr(Node *a, char *record){
    for(int k = 0; a->str[k] != '\0'; k++){
        record[a->str[k]] = 1;
    }
}

int isJoin(Node *a, char *record){
    for(int i = 0; a->str[i] != '\0' && i < RecordSize; i++){
        if(record[a->str[i]]){
            return 1;
        }
    }
    return 0;
}

int dfs(Node *nodes, const int n, const int startIdx, char *record, const int label){
    if(nodes[startIdx].label) return 0;
    nodes[startIdx].label = label;
    recordStr(&(nodes[startIdx]), record);

    int nodeSum = 1;
    for(int i = 0; i < n; i++){
        if(nodes[i].label) continue;
        if(isJoin(&(nodes[i]), record)){
            nodeSum += dfs(nodes, n, i, record, label);
        }
    }

    return nodeSum;
}

int solve(Node *nodes, const int n){
    int labelCount = 0;
    
    for(int i = 0; i < n; i++){
        if(!nodes[i].label){
            char record[RecordSize] = {0};
            int dfsRes = 0;
            labelCount++;
            dfsRes = dfs(nodes, n, i, record, labelCount);
            // memset(record, sizeof(char) * RecordSize, 0);
        }
    }
    printf("%d\n", labelCount);
}

int main(){
    int t = 0;
    scanf("%d\n", &t);

    for(int i = 0; i < t; i++){
        int n = 0;
        scanf("%d\n", &n);
        Node nodes[2005] = {0};
        // Node *nodes = (Node *)malloc(sizeof(Node) * n);
        // memset(nodes, sizeof(Node) * n, 0);

        for(int j = 0; j < n; j++){
            char temp[StrSize] = {0};
            scanf("%s\n", temp);
            strComp(nodes[j].str, temp);
        }

        solve(nodes, n);

        // free(nodes);
    }

    return 0;
}