// NTHUOJ 12662 - I got a perfect body   
// Description
// I got a young body.
// ~by anonymous coroner
// You are a coroner, and you need to buy some Formalin to keep your body in good condition. There're n kinds of Formalin, and you have p dollars. Luckily the Formalin is on sale. If you buy exactly k kinds of Formalin, you only need to pay the most expensive one of them.
// You got n products and p dollars.
// Everytime you buy exactly k products at once, you only need to pay the most expensive product among the k products.
// For the i-th product, the price equals to ai.
// Find the maximum number of products you can buy with p dollars.

// Example:
// If n=5 and you got p=6 dollars.
// If you buy exactly k=2 products, you only need to pay the most expensive one of them.
// Products' price: 2, 4, 3, 5, 7.
// In this case, you can buy products of price 4, 3 then you only need to pay 4 dollars.
// You left with 2 dollars, then you can buy products of price 2.
// The maximum number of products you can buy in this case is 3.

// Input
// The input start with t(1<= t <=10) means number of testcases.
// Each testcase contains two lines.
// First line contains three numbers n(2<=n<=3*10^5), p(1<= p <= 10^9), k(2 <= k <= n).
// Second line contains n integer ai(1 <= ai <= 10000).

// Output
// For each testcase print the maximum number of products you can buy with p dollars.
// Remember to print \n at the end of each output.

// Sample Input  
// 8
// 5 6 2
// 2 4 3 5 7
// 5 11 2
// 2 4 3 5 7
// 3 2 3
// 4 2 6
// 5 2 3
// 10 1 3 9 2
// 2 10000 2
// 10000 10000
// 2 9999 2
// 10000 10000
// 4 6 4
// 3 2 3 2
// 5 5 3
// 1 2 2 1 2

// Sample Output  
// 3
// 4
// 1
// 1
// 2
// 0
// 4
// 5

// 2020/06/19 SYC

#include<stdio.h>
#include<stdlib.h>

int cmp(const int *a, const int *b){
    return (*a) > (*b);
}

void showArrLong(long long int *a, const int n){
    for(int i = 0; i < n; i++){
        printf("%lld ", a[i]);
    }
    printf("\n");
}

void showArr(int *a, const int n){
    for(int i = 0; i < n; i++){
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main(){
    int t = 0;
    scanf("%d\n", &t);

    for(int i = 0; i < t; i++){
        int n = 0, k = 0;
        long long int p = 0;
        scanf("%d %lld %d\n", &n, &p, &k);
        // printf("N: %d P: %lld K: %d\n", n, p, k);

        int *a = (int *)malloc(sizeof(int) * n);
        long long int *prefixSum = (long long int*)malloc(sizeof(long long int) * n);
        for(int j = 0; j < n; j++){
            scanf("%d", &(a[j]));
            // printf("%d ", a[j]);
        }
        // printf("\n");

        qsort(a, n, sizeof(int), (int (*)(const void *, const void *))cmp);
        // showArr(a, n);

        prefixSum[0] = (long long int)a[0];
        prefixSum[k - 1] = (long long int)a[k - 1];
        for(int i = 1; i < k - 1; i++){
            prefixSum[i] = prefixSum[i - 1] + (long long int)a[i];
        }
        
        // showArrLong(prefixSum, n);

        for(int i = 0; i < k; i++){ // Item [0] ~ [k - 1]
            long long int sum = prefixSum[i];
            for(int j = i + k; j < n; j += k){
                sum = sum + (long long int)a[j];
                prefixSum[j] = sum;
            }
        }
        // printf("PrfixSum of Cost: ");
        // showArrLong(prefixSum, n);

        for(int i = n - 1; i >= -1; i--){
            if(prefixSum[i] <= p){
                printf("%d\n", i + 1);
                break;
            }else if(i < 0){
                printf("0\n");
            }
        }

        free(a);
        free(prefixSum);
    }

    return 0;
}