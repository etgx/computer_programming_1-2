// // NTHUOJ 12125 - Tired janitor   
// Description
// There were n rows of seats in the classroom. Each row of seats littered with ai unit of trash. 
// For example: first row contained a1 unit of trash
// The janitor wanted to know how many units of trash were littered among row l to row r?
// For example: If janitor ask you about row l = 3 to row r = 6. You should answer a3 + a4 + a5 + a6 unit of trash.
// There will be q queries, help janitor  find out the answer so janitor  can clean up the class room.
// Note that because janitor  is furious about picking up trash, each number will be follow by a symbol " (/`A`)/ ~I__I " without quotation mark and then there is a blank to separate from the next number.
// Note that if you use a loop to get the sum of al ~ ar at each query you will get an Time limit exceed. 
// You can use prefix sum to solve this problem

// Input
// input contains several lines.
// First line contains two integer n(1 <= n <= 106), q(1 <= q <= 105) -- the number of rows and the number of queries.
// Second line contains n integer a1 ~ an (0 <= ai <= 109), and each interger followed by a symbol " (/`A`)/ ~I__I " and then there is a blank to separate from the next number.
// The following q lines each lines contains two integers l, r ( 1 <= l <= r <= n )

// Output
// output contain q lines, to each query output the sum of al ~ ar. remember to print \n at the end of each line.

// Sample Input  
// 6 10
// 5(/`A`)/ ~I__I 1(/`A`)/ ~I__I 6(/`A`)/ ~I__I 7(/`A`)/ ~I__I 0(/`A`)/ ~I__I 9(/`A`)/ ~I__I
// 1 2
// 3 4
// 1 3
// 1 4
// 3 3
// 4 4
// 5 5
// 3 5
// 2 2
// 1 1

// Sample Output  
// 6
// 13
// 12
// 19
// 6
// 7
// 0
// 13
// 1
// 5


#include<stdio.h>
#include<stdlib.h>

long long int prefix_current_idx = 0;
long long int prefix_current_sum = 0;
long long int *prefix_sum = NULL;

long long int push_prefix(long long int input){
    if(prefix_sum == NULL){
        // printf("prefix_sum is NULL\n");
        return 0;
    }else{
        prefix_sum[prefix_current_idx] = input + prefix_current_sum;
        prefix_current_sum += input;
        prefix_current_idx++;
        return 1;
    }

}

long long int get_sum(long long int a, long long int b){
    long long int idx_a = a - 2;
    long long int idx_b = b - 1;
    if(prefix_sum != NULL){
        if(idx_a < 0){
            return prefix_sum[idx_b];
        }else{
            return prefix_sum[idx_b] - prefix_sum[idx_a];
        }
    }else{
        // printf("prefix_sum is NULL\n");
        return 0;
    }
}

long long int main(){
    long long int n = 0;
    long long int q = 0;

    scanf("%lld %lld", &n, &q);
    prefix_sum = (long long int *)malloc(sizeof(long long int) * n);

    for(long long int i = 0; i < n; i++){
        
        long long int input = 0;
        scanf("%lld(/`A`)/ ~I__I", &input);
        // if(i % 2 == 0){    
            
            // long long int k = 0;
            // char integer[1000];
            
            // while(input[k] != '('){
            //     integer[k] = input[k];
            //     k++;
            // }
            // push_prefix(atoi(integer));
            // printf("%lld\n", input);
            push_prefix(input);
            
        // }
    }

    for(long long int i = 0; i < q; i++){
        long long int qa = 0;
        long long int qb = 0;
        scanf("%lld %lld", &qa, &qb);
        printf("%lld\n", get_sum(qa, qb));
    }


    return 0;
}