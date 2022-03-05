// IPHTC2 Week9 Problem 3 | NTHUOJ 12155 - Cat-Toast Crisis
// Description
// Recently, scientists finally find a way to produce unlimited energy. The scientists call it "Cat-Toast".
// In case that someone might not know:
// While buttered toast falls onto the ground, it will always land with its buttered side - Falling Toast Theorem(FTT)
// While cats fall onto the ground, they will always land with their four feets. - Falling Cat Theorem(FCT)
// By FTT, we can assume that if we put butter on both sides of the toast, we might create a perpetual motion machine, because by FTT, we know that the buttered side will land onto the ground. However, there are two buttered sides. If any side of the toast lands, there will be a contradiction, so the toast will never fall and continue spinning around. We can apply the same way on FCT.
// However, there is a big problem. if we just put two buttered toasts or two cats together, there will be no momentum, and obviously it won't spin except for any external force, which cannot be a perpetual motion machine. This problem had confused scientists for centuries.
// Recently, scientists finally got a breakthrough progress. They combined a cat and a buttered toast and it just spins by itself! Due to the difference mass of a cat and a buttered toast, the machine itself will provide the momentum to spin, and it will never fall onto the ground (due to the contradiction we proved before), the first perpetual motion machine was born!
// The original video is here.

// Scientists found that if two cat-toasts' distance are equal to or closer than rr, there will be a collision which cause a small black hole and soon disappear, which may cause an irreversible destruction. Thus, cat-toasts must be secured separately. Also, if there are multiple cat-toasts that will collide, those cat-toasts will all collide together and spawn exactly one black hole. You may refer to Sample I/O for more details. One day in NTHU, a servitor just carries a lot of cat-toasts, each with a secured box. He accidently falls down and all the cat-toasts just drop out of their own boxes. Now given rr and all the coordinates of all cat-toasts, the servitor wants to know how many cat-toasts remains after some destructive collisions and how many black holes spawned.
// Note that the distance of two cat-toasts is \sqrt{(x_1-x_2)^2+(y_1-y_2)^2}, where (x_1,y_1) and (x_2,y_2)  are the coordinates of the two cat-toasts.

// Input
// The first line contains two integers n, r, indicate the number of cat-toast, the distance r described above. The next n lines, each line contains two integers x_i, y_i, indicate the location of the ii-th cat-toast.
// 1\le n\le 1000,1\le r\le 10^4
// 1\le x_i,y_i\le 10^4
 
// Output
// The first line of the output is the total number of cat-toasts that still remains and the total number of black holes after collisions, separated by a space. Remember to print a '\n' at the end of the output.

// Sample Input 1 

// 7 4
// 1 7
// 1 3
// 5 3
// 5 15
// 7 3
// 1 15
// 500 500

// Sample Output 1

// 1 2

// Hint
// The visualization of sample testcase is shown below:
// The remained cat-toast is contained in the blue circle, and the collisions happened in the red circle, which also spawn blackholes.

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CATTOAST_NUM 1005

typedef struct cattoast{
    int cluster;
    int x, y;
}CatToast;

int compute_dist(CatToast a, CatToast b){
    return ((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void dfs(CatToast *seq, int *cluster_size, int i, int r, int n){
    int current_cluter_id = seq[i].cluster;
    for(int j = 0; j < n; j++){
        if(seq[j].cluster == 0 && compute_dist(seq[i], seq[j]) <= r * r){
            seq[j].cluster = current_cluter_id;
            cluster_size[current_cluter_id]++;
            dfs(seq, cluster_size, j, r, n);
        }
    }
}

void merge(CatToast *seq, int *cluster_size, int r, int n){
    int cluster_id = 1;

    for(int i = 0; i < n; i++){
        int current_cluter_id = cluster_id;
        if(seq[i].cluster == 0){
            seq[i].cluster = current_cluter_id;
            cluster_size[current_cluter_id]++;
            cluster_id++;
            dfs(seq, cluster_size, i, r, n);
        }
    }
}

int main(){
    int n = 0, r = 0, black_hole_num = 0, cat_toast_num = 0;
    CatToast seq[MAX_CATTOAST_NUM] = {0};
    int cluster_size[MAX_CATTOAST_NUM] = {0};
    scanf("%d %d\n", &n, &r);
    for(int i = 0; i < n; i++){
        seq[i].cluster = 0;
        scanf("%d %d\n", &(seq[i].x), &(seq[i].y));
    }

    merge(seq, cluster_size, r, n);

    for(int i = 1; i <= n; i++){
        if(cluster_size[i] == 1){
            cat_toast_num++;
        }else if(cluster_size[i] > 1){
            black_hole_num++;
        }
    }

    printf("%d %d\n", cat_toast_num, black_hole_num);

    return 0;
}