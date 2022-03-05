// NTHUOJ 12823 - Nyan Cat Crisis   
// Description
// Previous episode: 12155
// After the "blackhole" incident, scientists accidentally found the potential energy of blackholes that created by the collision of multiple cat-toasts: the energy productivity of cat-toast blackhole is far more larger than cat-toasts.
// By observing the cat-toast blackhole near the event horizon, they found that the collided cat-toasts weren't teared into slices but spinning around the blackhole. The scientists decided to call it "Nyan Cat". The Nyan Cat blackhole soon be wildly spread to the whole world.
// You have to login in order to see the image.
// Nyan Cat spinning around the blackhole
// Recently, the scientists found that if there are too many Nyan Cat spinning around one blackhole, the huge angular momentum will form an unstable energy field, which would cause the Nyan Cat blackhole system crash, then all the nearby substance will be inhaled.
// They soon set up a team to deal with the potential threat. If a cat-toast blackhole contains too many Nyan Cat spinning around it, they'll use catnip(貓薄荷) to lure it out.

// You are in a power plant, whose energy source is the cat-toast blackhole. The power plant engineer gives you the original cat-toast location before they collide into a blackhole. You need to figure out the number of blackholes that is safety, and the number of blackholes that contains too many Nyan Cat.
// There are  nodes on an 2D-plane. If the distance of two nodes are equal to or closer than r, they are in the same group.
// You are given a number k. You have to find out:
// The number of groups with size less than k.
// The number of groups with size equal to or greater than k.
// Note that the distance between two nodes  and  is: ((xi - xj) ^ 2 + (yi - yj) ^ 2) ^ (1 / 2)
// where (xi, yi) and (xj, yj) are the coordinate of the two nodes, respectively.

// Input
// The first line contains an integer t, indicates the number of testcases.

// In each testcase:

// The first line contains n, r, and k.
// There are  lines below. The -th line of the  lines contains the coordinate of -th node: .
// .

// .

// Output
// Output two numbers:
// The number of groups with size less than  ,and the number of groups with size equal to or greater than , seperate with a space.
// Remember to print a newline at the end of the output.

// Sample Input  
// 2
// 6 4 2
// 1 7
// 1 3
// 5 3
// 5 15
// 1 15
// 500 500
// 10 6 3
// 0 0
// 5 5
// 3 4
// 103 1
// 102 5
// 999 999
// 199 -199
// -10000 10000
// -9999 9999
// -9993 9999

// Sample Output  
// 1 2
// 3 2

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int x;
    int y;
    int isVisited; // if = 0, no one visit before. If >= 1, represent the Label of the group belongs to.
}Node;

int dfs(Node *ps, const int startIdx, const int n, const int r, const int label){
    if(label <= 0) return -1;
    int sumOfNodes = 0;

    if(!ps[startIdx].isVisited){
        ps[startIdx].isVisited = label;
        sumOfNodes++;

        for(int i = 0; i < n; i++){
            int disSq = (ps[startIdx].x - ps[i].x) * (ps[startIdx].x - ps[i].x) + (ps[startIdx].y - ps[i].y) * (ps[startIdx].y - ps[i].y);

            if(disSq <= r * r && i != startIdx){
                sumOfNodes += dfs(ps, i, n, r, label);
            }
        }
    }

    return sumOfNodes;
}

void solve(Node *ps, const int n, const int r, const int k){
    int groupS = 0; // The number of groups that size < k
    int groupL = 0; // The number of groups that size >= k
    int labelCount = 1;

    for(int i = 0; i < n; i++){
        int groupSize = dfs(ps, i, n, r, labelCount);
        if(groupSize > 0) labelCount++;
        if(groupSize > 0){
            if(groupSize < k){
                groupS++;
            }else{
                groupL++;
            }
        }
    }

    printf("%d %d\n", groupS, groupL);
}

int main(){
    int t = 0;
    scanf("%d\n", &t);
    for(int i = 0; i < t; i++){
        int n = 0, r = 0, k = 0;
        
        scanf("%d %d %d\n", &n, &r, &k);
        Node *ps = (Node *)malloc(sizeof(Node) * n);

        for(int j = 0; j < n; j++){
            scanf("%d %d\n", &(ps[j].x), &(ps[j].y));
            ps[j].isVisited = 0;
        }

        solve(ps, n, r, k);
    }

    return 0;
}