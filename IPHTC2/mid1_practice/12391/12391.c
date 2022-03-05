// IPHTC2 Week6 Problem 2 | NTHUOJ 12391 - Lucky Ghoul Dawn baby
// Description
// A famous streamer once said: "I will definitely hit you! I will definitely break your bridge!". The streamer asked you to remember those who annoyed him. They are represented as numbers. When the streamer ask you, you should answer the position of the one the streamer wants to hit.
// You will got nn numbers in increasing order and qq for the number of queries.
// Suppose the nn numbers are stored in an array whose index start from 1.

// Each query will give you an integer a_ia 
// i
// ​
//   , then you need to answer the position of a_ia 
// i
// ​
//   in the array.

// If you can't find the number in the array, you need to output "Break your bridge!".

// Input
// Input end with EOF.

// Each testcase contains several lines.

// First line contains two integer n(1 \leq n \leq 2\times 10^6)n(1≤n≤2×10 
// 6
//  ) and q(1\leq q\leq 2\times 10^6)q(1≤q≤2×10 
// 6
//  )

// Second line contains nn integer. Each integer range in 1\sim10^91∼10 
// 9
 

// The following are qq lines. Each line contains one integer a_i(1 \leq a_i \leq 10^9)a 
// i
// ​
//  (1≤a 
// i
// ​
//  ≤10 
// 9
//  )

// Output
// For each query print the position of a_ia 
// i
// ​
//  .

// If you can't find a_ia 
// i
// ​
//   in the array, print "Break your bridge!"

// Remember to print \n at the end of each output.

// Sample Input 1 

// 10 5
// 4 7 9 20 31 46 50 56 76 96
// 19
// 50
// 96
// 7
// 100
// 6 3
// 4 7 9 20 31 34
// 4
// 1
// 20
// Sample Output 1

// Break your bridge!
// 7
// 10
// 2
// Break your bridge!
// 1
// Break your bridge!
// 4
// Hint

// example:

// 6 3 // n = 6, q = 3
// 4 7 9 20 31 34 // n numbers
// 4 // answer the position of 4
// 1 // answer the position of 1
// 20 // answer the position of 20
// In this example you can find "4" in the first place, therefore you should answer "1".

// You can't find "1" in the array, therefore you should answer "Break your bridge!".

// You can find "20" in the forth place, therefore you should answer "4".

// You can use the following sample code to solve the problem. It's better you write your own code:

// typedef struct _NODE {
//     int num, id;
//     struct _NODE *left, *right;
// } Node;
// void build_tree(Node **now, Num *arr, int l, int r) {
//     if(l>r) return;
//     (*now) = (Node*)malloc(sizeof(Node));
//     if(l==r) {
//         /*do it your self*/
//     }
//     else {
//         /*do it your self*/
//     }
// }
// int search(Node *now, int x) {
//     if(now==NULL) return 0;
//     /*do it your self*/
// }
// void insert(Node **root, int x) {
//     /*do it your self*/
// }
// void freeBST(Node *root){
//     if(root == NULL) return;
//     /*do it your self*/
// }

// 2021/10/30 SYC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_OF_LONG_LONG sizeof(long long)
#define NOT_FOUND_MSG "Break your bridge!"

// Correct, Hancraft one
long long bst_search(long long *arr, long long l, long long r, long long a_i){
    long long pivot = (l + r) / 2;

    if(arr[pivot] == a_i){
        return pivot;
    }else if(arr[pivot] > a_i){
        // a_i is at the left of the pivot
        if(r == pivot){return -1;}
        return bst_search(arr, l, pivot, a_i);
    }else if(arr[pivot] < a_i){
        // a_i is at the right of the pivot
        if(l == pivot){return -1;}
        return bst_search(arr, pivot + 1, r, a_i);
    }else{
        return -1;
    }
}

// Correct, refers to https://www.geeksforgeeks.org/binary-search/
long long bst_search2(long long *arr, long long l, long long r, long long a_i){
    long long pivot = (l + r) / 2;
    if(r >= l){
        if(arr[pivot] > a_i){
            return bst_search2(arr, l, pivot - 1, a_i);
        }else if(arr[pivot] < a_i){
            return bst_search2(arr, pivot + 1, r, a_i);
        }else{
            return pivot;
        }
    }
    return -1;
}

// Correct, refers to https://en.wikipedia.org/wiki/Binary_search_algorithm
long long bst_search3(long long *arr, long long n, long long a_i){
    long long l = 0, r = n - 1;
    long long pivot = 0;

    while(l <= r){
        pivot = (l + r) / 2;
        if(arr[pivot] > a_i){
            r = pivot - 1;
        }else if (arr[pivot] < a_i){
            l = pivot + 1;
        }else{
            return pivot;
        }
    }
    return -1;
}

long long search(long long *arr, long long n, long long a_i){
    return bst_search(arr, 1, n + 1, a_i);
    // return bst_search2(arr, 1, n, a_i);
    // return bst_search3(&(arr[1]), n, a_i) + 1;
}

int main(){
    long long n = 0, q = 0;
    while(scanf("%lld %lld\n", &n, &q) != EOF){
        long long *arr = (long long*)malloc(SIZE_OF_LONG_LONG * (n + 1));

        for(long long i = 1; i <= n; i++){
            scanf("%lld", &(arr[i]));
        }

        long long a_i = 0;
        for(long long i = 0; i < q; i++){
            scanf("%lld", &a_i);
            long long p_i = search(arr, n, a_i);
            if(p_i > 0){
                printf("%lld\n", p_i);
            }else{
                printf("%s\n", NOT_FOUND_MSG);
            }
        }

        free(arr);
    }

    return 0;
}