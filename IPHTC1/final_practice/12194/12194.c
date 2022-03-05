// NTHUOJ 12194 - de way to home   
// Description
// Ovuvuevuevue Enyetuenwuevue Ugbemugbem Osas go out hunting some animals for survival. However, he accidentally found some Ugandan children lost their way home. 
// After investigation, Osas found that they all have the same first name as him, which is "Ovuvuevuevue Enyetuenwuevue Ugbemugbem", but with a number last name. Not too long he found their village. 
// In this village, all the house has its number id. Osas supposed that if a child's last name, which is a number, matches one id of that house, the child must live in this house. Osas also found that the ids of these house are sorted in ascending order. 
// Now, Osas would like to ask you, the invincible programming chief of the village, the home way of these children's. 
// Given a sequence <a> with n numbers, which are the id of these houses, in ascending order.
// Give you q queries, each query contains one number, you are going to answer if the number exists in the sequence <a>.
// If the number is in the sequence, output "I know de way to your home." Otherwise output "Wake up, you homeless poor."

// Input
// The first line contains exactly two numbers, indicates n and q described above. 
// The next line is the sequence <a> in ascending order, which contains exactly n integers. 
// Then there are q lines below. Each line contains exactly one integer, indicates the query. 
// 1 <= n <= 106, 1 <= q <= 106, 1 <= ai <= 109, each query won't larger than 109 or smaller than 1. 
// For the first 4 testcases, n will not exceed 100, while n of the last 2 testcases is up to 106.

// Output
// For each query, if the number exists in the sequence <a>, then output "I know de way to your home." Otherwise output "Wake up, you homeless poor."

// Sample Input  
// 10 5
// 1 3 6 8 9 11 20 31 36 48
// 9
// 15
// 37
// 1000000
// 48

// Sample Output  
// I know de way to your home.
// Wake up, you homeless poor.
// Wake up, you homeless poor.
// Wake up, you homeless poor.
// I know de way to your home.

#include<stdio.h>
#include<stdlib.h>

int binSearch(int *a, int q, int n){
    int start = 0, end = n - 1, mid = (n - 1) / 2;

    while(start != end){
        if(q < a[mid]){
            end = mid;
        }else if(q > a[mid]){
            start = mid + 1;
        }else{
            break;
        }
        mid = (start + end) / 2;
    }
    return mid;
}

int main(){
    int n = 0, q = 0;

    scanf("%d %d\n", &n, &q);
    int *a = (int *)malloc(sizeof(int) * n);
    
    for(int i = 0; i < n; i++){
        scanf("%d", &(a[i]));
    }

    for(int i = 0; i < q; i++){
        int query = 0;
        int res = 0;
        scanf("%d", &query);

        res = binSearch(a, query, n);
        if(a[res] == query){
            printf("I know de way to your home.\n");
        }else{
            printf("Wake up, you homeless poor.\n");
        }
    }
    return 0;
}