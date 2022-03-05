// NTHUOJ 11679 - Flattening the Tree   

// Description
// Writer : jjjjj19980806
// Description : pclightyear

// In this problem, we want you to use an array A to implement a perfect binary tree (a kind of binary tree which all interior nodes have two children and all leaves have the same depth or same level.). Given the level order sequence of the tree, please output the sequence of number after the tree is flattened.
// For example, a perfect binary tree with level order sequence 4 2 6 1 3 5 7 looks like : 
// After flattening, so you should output 1 2 3 4 5 6 7.
// Here is some tips for you guys to implement a binary tree.
// 1. A[1] is the root of the tree.
// 2. For the node locates in A[k], its left child locates in A[2k] and its right child locates in A[2k+1].
// 3. You can write a recursive function "find_seq" which takes the root index as its argument.

// Input
// The first line contains one integer n, representing the number of nodes in the tree.
// The second line contains n integer ai, representing the level order of the tree.
// It is guaranteed that :
// n = 2k - 1
// 1 ≤ k ≤ 10
// a1 ~ an is a permutation of 1 ~ n

// Output
// Please output the sequence of the number after the tree is flattened. Each number is separated by a whitespace.
// You need to print ‘\n’ at the end of the output.

// Sample Input  
// 7
// 4 2 6 1 3 5 7

// Sample Output  
// 1 2 3 4 5 6 7

// 2020/05/26 SYC

#include<stdio.h>
#include<stdlib.h>

void postOrder(int *seq, int current, int num){
    if(2 * current <= num){
        postOrder(seq, 2 * current, num);
    }

    printf("%d", seq[current]);

    if(current == num){
        printf("\n");
    }else{
        printf(" ");
    }
    
    if(2 * current + 1 <= num){
        postOrder(seq, 2 * current + 1, num);
    }
}

int main(){
    int k = 0;
    int seq[1500] = {0};
    scanf("%d", &k);

    for(int i = 1; i <= k; i++){
        scanf("%d", &(seq[i]));
    }

    postOrder(seq, 1, k);

    return 0;
}