// NTHUOJ 12302 - Uncle Huang choose Tutor(Hard version)   
// Description
// Uncle Huang wants to find a tutor. He has n students to choose from. 
// Students are indexed 1, 2, . . . , n and standing in a circle. 
// Uncle Huang will count every k-th students in clock-wise.  
// The k-th student is going to be chosen but the student will disappear(Nobody know why!) therefore Uncle Huang will continue his counting and start from the next student.
// The last remaining student will be his tutor.
// Tell Uncle Huang the index of the student who will be his tutor.
// example: If n = 5, k = 7

// Hint: 約瑟夫斯問題(https://zh.wikipedia.org/wiki/%E7%BA%A6%E7%91%9F%E5%A4%AB%E6%96%AF%E9%97%AE%E9%A2%98)

// Note:
// This is the hard version, if you use link list to solve this problem you will get TLE.
// If you use recursion to solve this problem you will get MLE for the testcase 6.
// The idea for solving this problem: 
// If we already know the position that will be the last remaining for n = m-1( if n==1 then the answer is obvious. The answer will be 1 ), can we use this clue to calculate the answer for n = m?

// Input
// The input will end by EOF
// Every testcase only contains two integer n(1<= n <= 107) and k(1 <= k <= 109)

// Output
// For every testcase print the index of the student who last remaining.
// remember to print \n at the end of every output.

// Sample Input  
// 10 2
// 3 1
// 5 7

// Sample Output  
// 5
// 3
// 4

#include <stdio.h>
#include <stdlib.h>

long long josephus_recursive(long long n, long long k){
    if(n == 1){
        return 1;
    }else{
        // We should start counting from 0 to avoid the edge case like n = k
        // So, we need to mnius 1 to make the index count from 0, and then, plus 1 to recover to correct order.
        return (josephus_recursive(n - 1, k) + k - 1) % n + 1;
    }
}

long long josephus_for(long long n, long long k){
    // The index should start from 0, otherwisw, the modular arithemetic would encouter some errors
    long long survivor = 0;
    // Start from n = 2
    for(int i = 2; i <= n; i++){
        // The last survivor of (n, k) is (n - 1, k) % n, since we need to remove 1 person and shift the original index right with k.
        // Then, take modular to avoid the index exceed n
        survivor = (survivor + k) % i;
    }
    // Recompute the survivor from index = 1
    return survivor + 1;
}

int main(){
    long long n = 0, k = 0;
    while(scanf("%lld %lld", &n, &k) != EOF){
        long long survivor = josephus_for(n, k);
        printf("%lld\n", survivor);
    }
    return 0;
}