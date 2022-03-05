// IPHTC2 Week7 Problem 2 | NTHUOJ 12254 - Thanos' Dilemma   
// Description
// In "Avengers 3", we know that Thanos wants to eliminate half of the world to keep the world in a good balance. But, have you ever wondered about how he choose "1/2" ? Why don't he choose "1/3", "1/4", or "253/502" ? 
// He knows that the population of this world would just keep growing, so he calculated the formula of population of this world:
// On the i-th year from the start of the world, the population of this world P(i) would be: P(i-1) + 2 * P(i-2) + P(i-3).
// From this formula, he concluded that P(1)=1, P(2)=12, P(3)=13.
// According to this formula, he could estimate the populations of the world on every year, so that he could choose the percentage of the population he would like to eliminate. (We don't know how he choose)
// Because Thanos has a lot of planets to conquer, he asks you to calculate P(x), while x is given by him.
// The world has lived for so many years, so he might ask you P(x) where x would be very large. And in case of P(x) is super large, the number should mod 109+7.
// "Thanos Thinking About This Problem"
// If you click on this picture, something might happen...
// Given t, indicates the number of testcases.
// P(i) = P(i-1) + 2*P(i-2) + P(i-3)
// P(1)=1, P(2)=12, P(3)=13
// Given x, you are going to calculate P(x)%(109+7) of every testcase.
// Hint: use fpw(快速冪) to solve this problem!
// If we rewrite the equation into matrix form, we could get the following formula:
// With this formula, we can do something more:

// Now, we can implement fpw(快速冪) method on the matrix power part. For those n<=3, just output the answer.
// Note that you are encouraged to implement a "matrix" struct to solve this easier.

// Input
// The first line contains one integer t, indicates the number of testcases.
// There are t lines below, each line contains one integer x.
// 1 <= t <= 20, 1 <= x <= 1018.

// Output
// For each testcase, output exactly one integer P(x)%(109+7).
// Remember to output a '\n' at the end of every testcase.

// Sample Input  
// 5
// 2
// 3
// 10
// 15
// 30

// Sample Output  
// 12
// 13
// 3513
// 160609
// 345389283

// 2021/10/31 SYC

// Reference: https://en.wikipedia.org/wiki/Exponentiation_by_squaring

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VECTOR_SIZE 3
#define MOD 1000000007
#define TRANSITION {{{1, 2, 1}, {1, 0, 0}, {0, 1, 0}}}
#define IDENTITY {{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}}
#define INIT {{13, 12, 1}}
#define BITS_OF_BYTE 8
#define BITS_OF_LONG_LONG sizeof(long long) * BITS_OF_BYTE

typedef struct vector{
    long long v[VECTOR_SIZE];
}Vector;

typedef struct matrix{
    long long m[VECTOR_SIZE][VECTOR_SIZE];
}Matrix;

long long prod(long long a, long long b){
    return ((a % MOD) * (b % MOD)) % MOD;
}

long long add(long long a, long long b){
    return ((a % MOD) + (b % MOD)) % MOD;
}

Matrix mat_prod(Matrix a, Matrix b){
    Matrix m;
    for(int r = 0; r < VECTOR_SIZE; r++){
        for(int c = 0; c < VECTOR_SIZE; c++){
            long long sum = 0;
            for(int i = 0; i < VECTOR_SIZE; i++){
                sum = add(sum, prod(a.m[r][i], b.m[i][c]));
            }
            m.m[r][c] = sum;
        }
    }
    return m;
}

Vector mat_vec_prod(Matrix a, Vector b){
    Vector v;
    for(int r = 0; r < VECTOR_SIZE; r++){
        long long sum = 0;
        for(int i = 0; i < VECTOR_SIZE; i++){
            sum = add(sum, prod(a.m[r][i], b.v[i]));
        }
        v.v[r] = sum;
    }
    return v;
}

long long compute(long long x){
    Matrix base = TRANSITION;
    Matrix pow = IDENTITY;
    const Vector init = INIT;
    
    if(x == 1){
        return init.v[2];
    }else if(x == 2){
        return init.v[1];
    }else if(x == 3){
        return init.v[0];
    }else if(x > 3){
        const long long times = x - 3;
        for(long long i = 0; i < BITS_OF_LONG_LONG; i++){
            if((times >> i) & 1){
                pow = mat_prod(base, pow);
            }
            base = mat_prod(base, base);
        }
        return mat_vec_prod(pow, init).v[0];
    }
    return init.v[2];
}

int main(){
    int t = 0;
    scanf("%d\n", &t);
    for(int i = 0; i < t; i++){
        long long x = 0;
        scanf("%lld\n", &x);
        printf("%lld\n", compute(x));
    }
    return 0;
}