// IPHTC2 Week7 Problem 2 | NTHUOJ 12435 - Go Down Chicken
// Description
// "Go Down Chicken is a vicious monster, it will hit you until you have cerebral concussion(腦震盪)." ~from an anonymous bestiary.
// To avoid from being attacked by Go Down Chicken, you need to solve the following problem.

// This question has multiple input in each testcase. The input end with EOF.
// Each input contain n numbers a_i(1 \leq i \leq n)  and q queries x_j(1 \leq j \leq q)
// Each number a_i  represents a game.
// The game is that you need to fill a 3 \times a_i tiles with the shape described in the picture below(The left one). 
// The shape can't overlap and no empty space allow. For each a_i you need to answer how many ways you can fill the tiles.
// The number of ways may be very large, therefore just answer the number mod 1000000007.

// Input

// The input is end with EOF
// Each input contains several lines.
// First line contains two integer n(1 \leq n \leq 10^6), q( 1 \leq q \leq 10^6)
// Second line contain nn integer a_i( 1 \leq a_i \leq 10^6).
// Each a_i is followed by a symbol "(/`A`)/ ~I__I" and separated by a blank from the next integer,
// The following qq lines each line contains one integer x_j

// Output
// For each query print that x_j is the result of which round of the games(start from 1).
// If there're multiple answers, answer the earliest round.
// If you can't find the answer, print "Go Down Chicken 404"

// Sample Input 1 

// 5 3
// 6(/`A`)/ ~I__I 9(/`A`)/ ~I__I 13(/`A`)/ ~I__I 4(/`A`)/ ~I__I 3(/`A`)/ ~I__I
// 0
// 4
// 1024
// 6 4
// 8(/`A`)/ ~I__I 2(/`A`)/ ~I__I 3(/`A`)/ ~I__I 8(/`A`)/ ~I__I 11(/`A`)/ ~I__I 12(/`A`)/ ~I__I
// 16
// 0
// 2
// 512

// Sample Output 1

// 2
// 4
// Go Down Chicken 404
// 1
// 3
// 2
// Go Down Chicken 404

// Hint

// Sample input explain:
// You have n = 5, q = 3
// Then you have 5 integer: 6, 9, 13, 4, 3
// If the tiles is 3\times 6: you have 8 ways to fill it.
// If the tiles is 3\times 9: you have 0 ways to fill it.
// If the tiles is 3\times 13: you have 0 ways to fill it.
// If the tiles is 3\times 4: you have 4 ways to fill it.
// If the tiles is 3\times 3: you have 0 ways to fill it.
// Then you have 3 queries: 0, 4, 1024
// There are multiple rounds turn out have 0 ways, but you need to answer the earliest round. The earliest round is second round.
// Therefore the answer is 2.
// The round that turns out have 44 ways is the forth round.
// Therefore the answer is 4.
// The round that turns out have 1024 ways can't be found.
// Therefore the answer is "Go Down Chicken 404".

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 1000000007
#define MAX_ARR_LENGTH 1000005
#define BITS_OF_BYTE 8
#define BITS_OF_LONG_LONG sizeof(long) * BITS_OF_BYTE
#define NOT_FOUND_MSG "Go Down Chicken 404"

typedef struct game{
    long ways;
    long pos;
}Game;

void show_arr(Game *arr, long n){
    for(long i = 0; i < n; i++){
        printf("%ld ", arr[i].ways);
    }
    printf("\n");
}

long fast_power(long x, long pow){
    long base = x % MOD, accum = 1;
    for(long i = 0; i < BITS_OF_LONG_LONG; i++){
        if((pow >> i) & 1){
            accum = (accum * base) % MOD;
        }
        base = (base * base) % MOD;
    }
    return accum;
}

long count_ways(long a_i){
    if((a_i % 2) == 1){
        return 0;
    }else{
        return fast_power(2, (a_i / 2));
    }
}

void swap(Game *a, Game *b){
    Game temp = *a;
    *a = *b;
    *b = temp;
}

int compare(Game a, Game b){
    if(a.ways < b.ways){
        return 1;
    }else{
        return 0;
    }
}

long partition(Game *arr, long l, long r){
    // Induction
    // Basis:
    // The partition would swap itself i == j until it meets anotehr number >= pivot.
    // When the partition meet a number >= pivot, i < j
    // The numbers of arr[i+1 : j-1] are all >= pivot befor swapping
    // Thus, if arr[j] < pivot(the swap condition), it would exchange arr[i+1] and arr[j]
    // It can guarantee that for the first swap of i != j, it would exchange arr[i+1] and arr[j] and arr[i+1] >= pivot and arr[j] < pivot.
    // Induction:
    // Since we can guarantee that the first swap of i != j is correct, and then, the condition that
    // the numbers of arr[i+1 : j-1] are all >= pivot will hold.

    Game pivot = arr[r];
    long i = l - 1, j = l;

    // printf("Partition [%ld : %ld] %ld : %ld\n", l, r, arr[l], arr[r]);
    // printf("Pivot [%ld]: %ld\n", r, pivot);
    for(; j < r; j++){
        if(compare(arr[j], pivot)){
            i++;
            // printf("Swap [%ld]: %ld <-> [%ld]: %ld\n", i, arr[i], j, arr[j]);
            swap(&(arr[i]), &(arr[j]));
        }
    }
    // printf("Final Swap [%ld]: %ld <-> [%ld]: %ld\n", i, arr[i], j, arr[j]);
    // printf("Finish Partition: ");
    // show_arr(&(arr[l]), r - l + 1);
    swap(&(arr[i + 1]), &(arr[r]));
    return i + 1;
}

void quick_sort(Game *arr, long l, long r){
    if (l < r){
        long pivot = partition(arr, l, r);
        quick_sort(arr, l, pivot - 1);
        quick_sort(arr, pivot + 1, r);
    }
}

void merge(Game *arr, long l, long mid, long r){
    long l_arr_leng = mid - l + 1, r_arr_leng = r - mid;
    long temp_arr_leng = l_arr_leng + r_arr_leng;
    Game *temp_arr = (Game*)malloc(sizeof(Game) * temp_arr_leng);

    // printf("Merging Len: %ld | Mid [%ld]: %ld - L [%ld]: %ld - R [%ld]: %ld = \n", temp_arr_leng, mid, arr[mid].ways, l, arr[l].ways, r, arr[r].ways);
    for(long l_arr_idx = l, r_arr_idx = mid + 1, temp_arr_idx = 0; temp_arr_idx < temp_arr_leng; temp_arr_idx++){
        if(l_arr_idx <= mid && (!(r_arr_idx <= r) || arr[l_arr_idx].ways <= arr[r_arr_idx].ways)){
            // printf("L [%ld]: %ld <- [%ld]: %ld\n", temp_arr_idx, temp_arr[temp_arr_idx].ways, l_arr_idx, arr[l_arr_idx].ways);
            temp_arr[temp_arr_idx] = arr[l_arr_idx];
            l_arr_idx++;
        }else{
            // printf("R [%ld]: %ld <- [%ld]: %ld\n", temp_arr_idx, temp_arr[temp_arr_idx].ways, r_arr_idx, arr[r_arr_idx].ways);
            temp_arr[temp_arr_idx] = arr[r_arr_idx];
            r_arr_idx++;
        }
    }
    // printf("\n");
    // printf("Merged Len: %ld | Mid [%ld]: %ld - L [%ld]: %ld - R [%ld]: %ld = ", temp_arr_leng, mid, arr[mid].ways, l, arr[l].ways, r, arr[r].ways);
    for(long i = l, j = 0; j < temp_arr_leng; i++, j++){
        // printf("%ld ", temp_arr[j].ways);
        arr[i] = temp_arr[j];
    }
    // printf("\n---\n");
    free(temp_arr);
}

void merge_sort(Game *arr, long l, long r){
    if(l < r){
        long mid = (l + r) / 2;
        merge_sort(arr, l, mid);
        merge_sort(arr, mid + 1, r);
        merge(arr, l, mid, r);
    }
}

void sort(Game *arr, long size){
    // quick_sort(arr, 0, size - 1);
    merge_sort(arr, 0, size - 1);
}

long binary_search(Game *arr, long l, long r, long x){
    long pivot = (l + r) / 2;
    
    // printf("L [%ld]: %ld | R [%ld]: %ld | Pivot [%ld]: %ld\n", l, arr[l].ways, r, arr[r].ways, pivot, arr[pivot].ways);

    if(r - l <= 2){
        if(arr[l].ways == x){
            return l;
        }else if(arr[l + 1].ways == x){
            return l + 1;
        }else{
            return -1;
        }
    }
    
    if(x <= arr[pivot].ways){
        return binary_search(arr, l, pivot + 1, x);
    }else{
        return binary_search(arr, pivot + 1, r, x);
    }
}

long find(Game *arr, long n, long x){
    long target_game_idx = binary_search(arr, 0, n, x);
    return arr[target_game_idx].pos;
}

int main(){
    long n = 0, q = 0;
    // long *arr = (long*)malloc(sizeof(long) * MAX_ARR_LENGTH);
    // Game *ways_arr = (Game*)malloc(sizeof(Game) * MAX_ARR_LENGTH);
    long arr[MAX_ARR_LENGTH] = {0};
    Game ways_arr[MAX_ARR_LENGTH] = {0};

    while(scanf("%ld %ld", &n, &q) != EOF){
        // printf("n: %ld q: %ld\n", n, q);    
        // long *arr = (long*)malloc(sizeof(long) * n);
        // Game *ways_arr = (Game*)malloc(sizeof(Game) * n);
        memset(arr, 0, sizeof(long) * MAX_ARR_LENGTH);
        memset(ways_arr, 0, sizeof(Game) * MAX_ARR_LENGTH);

        for(long i = 0; i < n; i++){
            scanf("%ld(/`A`)/ ~I__I", &(arr[i]));
            ways_arr[i].pos = i + 1;
            ways_arr[i].ways = count_ways(arr[i]);
        }
        // for(long i = 0; i < n; i++){
        //     scanf("%ld", &(ways_arr[i]));
        // }

        // show_arr(ways_arr, n);
        sort(ways_arr, n);
        // show_arr(ways_arr, n);

        for(long i = 0; i < q; i++){
            long x_j = 0;
            scanf("%ld\n", &x_j);
            long round = find(ways_arr, n, x_j);
            if(round == 0){
                // printf("NOT FOUND\n");
                printf("%s\n", NOT_FOUND_MSG);
            }else{
                // printf("FOUND\n");
                printf("%ld\n", round);
            }
        }

        // free(arr);
        // free(ways_arr);
    }

    return 0;
}