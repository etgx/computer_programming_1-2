// NTHUOJ 12241 - Restaurants in Hsinchu   
// Description
// After some hard work of finding his queen, Knuckles finally arrived NTHU!
// Knuckles is exhausted. He wants to grab some delicious food. However, as all of us know......
// THERE IS NO "DELICIOUS" FOOD IN HSINCHU.
// (Actually there are some restaurants that are not bad. But just "not bad"...)
// This truth, which is cruel, hits Knuckles pretty hard. Knuckles doesn't give up and start his journey of finding delicious food in Hsinchu. 
// However, the more he goes out and seeks, the truth is just getting more clear...
// The i-th time that those bad-taste restaurants Knuckles found is Fi . Knuckles found that F1 = 1, F2 = 1, and Fi = Fi-1 + Fi-2 .
// The more Knuckles goes out, the more bad-taste restaurants he found.
// He is tired of finding more and more bad restaurants. He just wants to know there are how many bad restaurants when he goes out for the i-th time.

// There's a sequence F.
// F1 = 1, F2 = 1, Fi = Fi-1 + Fi-2.
// Find out Fi .
// Hint：

// Input
// The input contains multiple lines, ended by EOF.
// Every line contains an integer i.
// 1 <= i <= 1018.
// There will be at most 20 lines.

// Output
// Output Fi.
// Because Fi might be too big, the answer should mod 109+7, which means you should output Fi % (109+7).
// Remember to print a '\n' at the end of the output.

// Sample Input  
// 2
// 3
// 5
// 8
// 13
// 21
// 34
// 55

// Sample Output  
// 1
// 2
// 5
// 21
// 233
// 10946
// 5702887
// 583861472

#include<stdio.h>
#include<stdlib.h>
#define TransMatSize 2
#define Mod 1000000007
#define F1 1
#define F2 1
// Formular:
// |  Fi  | = | 1 1 | * | Fi-1 |
// | Fi-1 |   | 1 0 |   | Fi-2 |

void showMat(long long int **mat, const int rows, const int cols){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            printf("%lld ", mat[i][j]);
        }
        printf("\n");
    }
}

void **malloc2d(const int unitSize, const int rows, const int cols){
    void **res = (void **)malloc((sizeof(void *) * rows));
    for(int i = 0; i < cols; i++){
        res[i] = (void *)malloc(unitSize * cols);
    }

    return res;
}

long long int **mulSq(long long int **a, long long int **b, const int n, const long long int mod){
    long long int **res = (long long int **)malloc2d(sizeof(long long int) , n , n);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){
                res[i][j] = ((res[i][j] % mod) + (((a[i][k] % mod) * (b[k][j] % mod)) % mod)) % mod;
            }
        }
    }

    return res;
}

long long int mulRes(long long int **a, long long int *vert, const int n, const long long int mod){
    long long int res = 0;
    
    for(int j = 0; j < n; j++){
        res = ((res % mod) + (((a[0][j] % mod) * (vert[j] % mod)) % mod)) % mod;
    }
    
    return res;
}

long long int **fastPower(long long int **a, const int n, const long long int x, const long long int mod){
    long long int term = x;
    long long int **base = (long long int **)malloc2d(sizeof(long long int), n, n); // Copy of Matrix a
    long long int **accum = (long long int **)malloc2d(sizeof(long long int), n ,n); // Identity Matrix

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

    if(x <= 0){
        return accum;
    }else if(x == 1){
        return base;
    }else{
        while(term > 1){
            if(term % 2 == 1){
                // If term is Odd
                // x ^ n = x * ((x ^ 2) ^ ((n - 1) / 2))
                accum = mulSq(accum, base, n, mod);
                base = mulSq(base, base, n, mod);
                term = (term - 1) >> 1;
            }else{
                // If term is Even
                // x ^ n = (x ^ 2) ^ (n / 2)
                base = mulSq(base, base, n, mod);
                term = term >> 1;
            }
        }
    }

    return mulSq(accum, base, n, mod);
}

int main(){
    long long int x = 0;
    long long int *initMat = (long long int *)malloc(sizeof(long long int) * TransMatSize);
    long long int **transMat = (long long int **)malloc2d(sizeof(long long int), TransMatSize, TransMatSize);

    initMat[0] = F2; initMat[1] = F1;
    transMat[0][0] = 1; transMat[0][1] = 1; transMat[1][0] = 1; transMat[1][1] = 0;

    while(scanf("%lld", &x) != EOF){
        // printf("%lld\n", x);
        long long int **transit = fastPower(transMat, TransMatSize, x - 2, Mod);
        long long int res = mulRes(transit, initMat, TransMatSize, Mod);
        // showMat(transit, TransMatSize, TransMatSize);
        printf("%lld\n", res);
    }


    return 0;
}