// NTHUOJ 11662 - Fill containers with water   
// Description
// Suppose that you have an infinite number of containers with different sizes, already filled with water. Given another empty container with size N liters, you need to find the best way to fill this N-liter empty container using the provided smaller containers. By ‘best’, we mean that the total number of used containers should be as small as possible. For example, assume that we have containers in 1, 5, and 10 liters. To get the 17 liters of water, we need 2 containers of 1 liter, 1 container of 5 liters, and 1 container of 10 liters. Another example: assume that we have containers in 1, 5, 10 and 50 liters. To get the 57 liters of water, we need 1 container of 50 liters, 1 container of 5 liters, and 2 containers of 1 liter. Note that, to avoid water wastage, if you choose to use a container, all the water in this container should be poured.
// The following is an excerpt of incomplete code:
// #include <stdio.h>
// #define MAXNV 5
// int DONE = 0;
// int liters[MAXNV];
// int numbers[MAXNV];
// void show(int nv);
// void filling(int amount, int cur, int nv);
// int j=0;
// int water;
// int min=100;
// int min_numbers[MAXNV]={0};
// int main(void)
// {
//     int nv, i;

//     scanf("%d", &nv);
//     for (i=0; i<nv; i++) {
//         scanf("%d", &liters[i]);
//     }
//     scanf("%d", &water);
//     filling(water, 0, nv);

//     for(i=0;i<nv;i++)
//         numbers[i]=min_numbers[i];
//     show(nv);
//     return 0;
// }

// void show(int nv)
// {
//     int i;
//     printf("(%d", numbers[0]);
//     for (i=1; i<nv; i++) {
//         printf(",%d", numbers[i]);
//     }
//     printf(")\n");
// }

// void filling(int amount, int cur, int nv)
// {
//     /* your code */
// }

// Input
// The input contains three lines.
// The first line contains an integer N, indicating that how many containers you have.
// The second line gives you each container's size.
// The last line is the total amount of water you have to pour.

// Output
// The result can be displayed by calling the function show().
// Only the best way to fill the empty container should be displayed.

// Sample Input  
// 4
// 50 10 5 1
// 57

// Sample Output  
// (1,0,1,2)
 
// 2020/05/19 SYC

#include<stdlib.h>
#include<stdio.h>
#define Inf 2147483647

typedef struct container{
    int idx;
    int size;
    int used_times;
}Container;

typedef struct best_sol{
    int *cons_used_times;
    int pours;
}Best_Sol;

Best_Sol sol;

void showCon(const Container *con_arr, const int N){
    printf("\nSize: ");
    for(int i = 0; i < N; i++){
        printf(" %d\t", con_arr[i].size);
    }

    printf("\nUsed: ");
    for(int i = 0; i < N; i++){
        printf(" %d\t", con_arr[i].used_times);
    }
    printf("\n=======================================\n");
}

void showBestSol(const Best_Sol sol, const Container *con_arr, const int N){
    int used_total = 0;
    printf("\nSize: ");
    for(int i = 0; i < N; i++){
        printf(" %d\t", con_arr[i].size);
    }

    printf("\nUsed: ");
    for(int i = 0; i < N; i++){
        printf(" %d\t", con_arr[i].used_times);
        used_total += con_arr[i].used_times;
    }
    printf(" => %d", used_total);
    used_total = 0;

    printf("\nBest: ");
    for(int i = 0; i < N; i++){
        printf(" %d\t", sol.cons_used_times[i]);
        used_total += sol.cons_used_times[i];
    }
    printf(" => %d", used_total);
    printf("\n=======================================\n");
}

// int cmpSize(const Container *a, const Container *b){
//     return a->size < b->size;
// }

// int cmpIdx(const Container *a, const Container *b){
//     return a->idx > b->idx;
// }

int fill(Container *con_arr, int target, int layer, int con_num, int accum_pour){
    // All water has been done
    if(target == 0){
        if(accum_pour < sol.pours){
            sol.pours = accum_pour;
            for(int i = 0; i < con_num; i++){
                sol.cons_used_times[i] = con_arr[i].used_times;
            }
        }
        // showBestSol(sol, con_arr, con_num);
        return 1;
    }else if(target < 0 || layer >= con_num){
        return 0;
    }

    int max = target / con_arr[layer].size;

    for(int i = max; i >= 0; i--){
        con_arr[layer].used_times = i;
        // showCon(con_arr, con_num);
        fill(con_arr, target - (i * con_arr[layer].size), layer + 1, con_num, i + accum_pour);
    }
    con_arr[layer].used_times = 0;
    
    return 0;
}

int main(){
    int N = 0, target = 0;
    scanf("%d", &N);

    Container *con_arr = (Container *)malloc(sizeof(Container) * N);
    sol.cons_used_times = (int *)malloc(sizeof(int) * N);
    sol.pours = Inf;

    for(int i = 0; i < N; i++){
        scanf("%d", &(con_arr[i].size));
        con_arr[i].used_times = 0;
        con_arr[i].idx = i;

        sol.cons_used_times[i] = 0;
    }
    scanf("%d", &target);

    // The method that "Sort decreasingly and use larger number as many as you can" is not correct
    // Sometimes you shouldn't use largest bucket because you may need more small buckets to fill the requirement
    // EX: 10 5 3 to fill 32 => Best Sol: (10) * 2 + (3) * 4
    // EX: 9 8 1 to fill 32 => Best Sol: (8) * 4
    // qsort(con_arr, N, sizeof(Container), (int (*)(const void *, const void *))cmpSize);
    fill(con_arr, target, 0, N, 0);
    // qsort(con_arr, N, sizeof(Container), (int (*)(const void *, const void *))cmpIdx);

    printf("(");
    for(int i = 0; i < N - 1; i++){
        printf("%d,", sol.cons_used_times[i]);
    }
    printf("%d)\n", sol.cons_used_times[N - 1]);

    return 0;
}