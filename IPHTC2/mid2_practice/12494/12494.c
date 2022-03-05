// IPHTC2 Week8 Problem 3 | NTHUOJ 12494 - minimum mean of rectangle sum
// Description
// You are given a 2D matrix named AA with all slots are integers.
// Each element can be represented as A(i,j), while i,j indicate the line number of row and column, respectively.
// Now, we define a rectangle sum S(x_1,y_1,x_2,y_2) as follow:

// S(x_1,y_1,x_2,y_2)=\sum_{i=x_1}^{x_2}\sum_{i=y_1}^{y_2}A(i,j)

// And we define mean of rectangle sum M(x_1,y_1,x_2,y_2) as follow:

// M(x_1,y_1,x_2,y_2)=\frac{S(x_1,y_1,x_2,y_2)}{(x_2-x_1+1)(y_2-y_1+1)}
 
// You're going to calculate the minimum mean of rectangle sum in a given 2D matrix.

// That is, you need to get the answer of:

// \min_{x_1,y_1,x_2,y_2}M(x_1,y_1,x_2,y_2),\ \forall1\le x_1\le x_2\le n,\ 1\le y_1\le y_2\le m,\ \{x_1,y_1,x_2,y_2\}\subseteq\mathbb{N}

// while n, m indicate the number of row and column of matrix A, respectively.

// Input
// The first line contains 2 integers n,m indicate the number of row and column of matrix A, respectively.
// The next n lines contain the whole matrix A. The i-th line contains the i-th row of the matrix, m numbers for each line.
// 1\le n,m\le 10^3. All elements in AA will be in range of [-10^9,10^9]

// Output
// The output should contains only the value of minimum mean of rectangle sum.
// That is, find the answer of:
// \min_{x_1,y_1,x_2,y_2}M(x_1,y_1,x_2,y_2),\ \forall1\le x_1\le x_2\le n,\ 1\le y_1\le y_2\le m,\ \{x_1,y_1,x_2,y_2\}\subseteq\mathbb{N} and output its value.
// Remember to print a '\n' at the end of the output.

// Sample Input 1 

// 2 3
// -1 -1 8
// -1 0 2

// Sample Output 1

// -1

// Hint
// In the sample testcase the matrix AA is:

// A=\left[\begin{matrix}-1&-1&8\\-1&0&2\end{matrix}\right]

// Possible choices are:

// \begin{aligned} M(1,1,1,2)&=\frac{(-1)+(-1)}{(1-1+1)(2-1+1)}=-1\\ 
// M(1,2,2,3)&=\frac{(-1)+8+0+2}{(2-1+1)(2-1+1)}=4.5\\ 
// M(1,1,2,1)&=\frac{(-1)+(-1)}{(2-1+1)(1-1+1)}=-1\\ \end{aligned}
 
// You may choose either M(1,1,1,2) or M(1,1,2,1) as your answer, both of them are the minimum mean of rectangle sum.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROW_NUM 1001
#define MAX_COL_NUM 1001
#define MAX_VAL 1000000001

void prefix_sum(long long *row, long long m){
    for(long long i = 1; i <= m; i++){
        row[i] = row[i] + row[i - 1];
    }
}

void prefix_sum_2d(long long A[MAX_ROW_NUM][MAX_COL_NUM], long long n, long long m){
    for(long long i = 1; i <= n; i++){
        prefix_sum(A[i], m);
    }
}

int main(){
    long long n = 0, m = 0, min = MAX_VAL;
    scanf("%lld %lld\n", &n, &m);

    for(long long i = 1; i <= n; i++){
        for(long long j = 1; j <= m; j++){
            long long x = 0;
            scanf("%lld", &x);
            if(min > x){
                min = x;
            }
        }
    }
    printf("%lld\n", min);
    
    return 0;
}