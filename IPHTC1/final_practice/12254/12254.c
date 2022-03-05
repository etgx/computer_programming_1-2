// NTHUOJ 12254 - Thanos' Dilemma   
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

// 2020/06/18 SYC

// Reference: https://en.wikipedia.org/wiki/Exponentiation_by_squaring

#include<stdio.h>
#include<stdlib.h>
#define Mod 1000000007
#define TransMatSize 3
#define P1 1
#define P2 12
#define P3 13

void showMat(long long int **a, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%lld ", a[i][j]);
        }
        printf("\n");
    }
}

void **malloc2d(const int unitSize, const int rows, const int cols){
    void **res = (void **)malloc(sizeof(void *) * rows);
    for(int i = 0; i < cols ; i++){
        res[i] = (void *)malloc(unitSize * cols);
    }
    return res;
}

long long int **mulSq(long long int **a, long long int **b, const int n, const long long int mod){
    // Matrix a, b multiply
    // n: Matrix a, b size
    // mod
    long long int **res = (long long int **)malloc2d(sizeof(long long int), n, n);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){
                // (X * Y) % Mod = ((X % Mod) * Y) % Mod = ((X % Mod) * (Y % Mod)) % Mod
                res[i][j] = (res[i][j] % mod + ((a[i][k] % mod) * (b[k][j] % mod)) % mod) % mod;
            }
        }
    }

    return res;
}

long long int mulRes(long long int **a, long long int *vertic, const int n, const long long int mod){
    long long int res = 0;
    for(int j = 0; j < n; j++){
        res = ((res % mod) + (((a[0][j] % mod) * (vertic[j] % mod)) % mod)) % mod;
    }
    return res;
}

long long int **fastPower(long long int **a, const int n, const long long int k, const long long int mod){
    // a: Matrix to multiply
    // n: Size of a
    // k: How many time does a multiply
    // mod: calculate a % mod
    // Exponentiation By Squaring (Fast Power Method)
    // X ^ n = For n is Odd: x * (X ^ 2) ^ ((n - 1) / 2)
    //         For n is Even: (X ^ 2) ^ (n / 2)
    long long int term = k;
    long long int **base = (long long int **)malloc2d(sizeof(long long int), n, n);
    long long int **accum = (long long int **)malloc2d(sizeof(long long int), n, n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            base[i][j] = a[i][j];
            if(i == j){
                accum[i][j] = 1;
            }else{
                accum[i][j] = 0;
            }
        }
    }

    if(term < 0){
        return base;
    }else if(term == 0){
        return accum;
    }else{
        while(term > 1){
            if(term & 1){
                // Term is ODD
                accum = mulSq(accum, base, n, mod);
                base = mulSq(base, base, n, mod);
                term = (term - 1) >> 1;
            }else{
                // Term is EVEN
                base = mulSq(base, base, n, mod);
                term = term >> 1;
            }
        }
    }

    return mulSq(accum, base, n, mod);
}

int main(){
    int t = 0;
    long long int p[3] = {P3, P2, P1};
    long long int res = 0;
    scanf("%d\n", &t);

    long long int **transit = (long long int **)malloc2d(sizeof(long long int), TransMatSize, TransMatSize);
    transit[0][0] = 1;
    transit[0][1] = 2;
    transit[0][2] = 1;
    transit[1][0] = 1;
    transit[1][1] = 0;
    transit[1][2] = 0;
    transit[2][0] = 0;
    transit[2][1] = 1;
    transit[2][2] = 0;

    for(int i = 0; i < t; i++){
        long long int x = 0;
        scanf("%lld\n", &x);

        if(x == 3){res = P3;}
        else if(x == 2){res = P2;}
        else if(x == 1){res = P1;}
        else if(x <= 0){res = P1;}
        else{
            long long int **transAll = (long long int **)malloc2d(sizeof(long long int), TransMatSize, TransMatSize);
            transAll = fastPower(transit, TransMatSize, x - 3, Mod);
            // showMat(transAll, TransMatSize);

            res = mulRes(transAll, p, TransMatSize, Mod);
        }
        
        printf("%lld\n", res);
    }

    

    return 0;
}