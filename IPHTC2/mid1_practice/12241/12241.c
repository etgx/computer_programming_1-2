// IPHTC2 Week2 Problem 3 | NTHUOJ 12241 - Restaurants in Hsinchu
// Description
// After some hard work of finding his queen, Knuckles finally arrived NTHU!
// Knuckles is exhausted. He wants to grab some delicious food. However, as all of us know......
// THERE IS NO "DELICIOUS" FOOD IN HSINCHU.
// (Actually there are some restaurants that are not bad.)
// This truth, which is cruel, hits Knuckles pretty hard. Knuckles doesn't give up and start his journey of finding delicious food in Hsinchu.
// However, the more he goes out and seeks, the truth is just getting more clear...
// The i-th time that those bad-taste restaurants Knuckles found is F_i. Knuckles found that F_1=1, F_2=1, and F_i=F_{i-1}+F_{i-2}F 
// The more Knuckles goes out, the more bad-taste restaurants he found.
// He is tired of finding more and more bad restaurants. He just wants to know there are how many bad restaurants when he goes out for the i-th time.
// There's a sequence F.
// F_1=1, F_2=1, F_i=F_{i-1}+F_{i-2}
// Find out F_i.

// Input
// The input contains multiple lines, ended by EOF.
// Every line contains an integer i.
// 1 \le i \le 10^{18}.
// There will be at most 20 lines.

// Output
// Output F_i.
// Because F_i might be too big, the answer should mod 10^9+7, which means you should output F_i\%(10^9+7).
// Remember to print a '\n' at the end of the output.

// Sample Input 1 
// 2
// 3
// 5
// 8
// 13
// 21
// 34
// 55

// Sample Output 1
// 1
// 2
// 5
// 21
// 233
// 10946
// 5702887
// 583861472

// Hint
// \left[\begin{matrix}F_{n}\\F_{n-1}\end{matrix}\right]= \left[\begin{matrix}1&1\\1&0\end{matrix}\right] \left[\begin{matrix}F_{n-1}\\F_{n-2}\end{matrix}\right] ,\qquad n=2,3,4,\dots

// 2021/10/10 SYC 

#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007
#define MAX_SHIFT_BITS 64

typedef struct mat{
    unsigned long long a_11;
    unsigned long long a_12;
    unsigned long long a_21;
    unsigned long long a_22;
}Matrix;
typedef struct vec{
    unsigned long long u_1;
    unsigned long long u_2;
}Vec;

const Matrix I = {1, 0, 0, 1};
const Vec INIT = {1, 1};
const Matrix TRANS = {1, 1, 1, 0};

void show_mat(Matrix m){
    printf("==================\n");
    printf("| %llu \t %llu \t|\n", m.a_11, m.a_12);
    printf("| %llu \t %llu \t|\n", m.a_21, m.a_22);
    printf("==================\n");
}

unsigned long long inner_prod(unsigned long long x_1, unsigned long long x_2, unsigned long long y_1, unsigned long long y_2){
    return ((((x_1 % MOD) * (y_1 % MOD)) % MOD) + (((x_2 % MOD) * (y_2 % MOD)) % MOD)) % MOD;
    // return x_1 * y_1 + x_2 * y_2;
}

Matrix mat_prod(Matrix m_1, Matrix m_2){
    Matrix m_res;
    m_res.a_11 = inner_prod(m_1.a_11, m_1.a_12, m_2.a_11, m_2.a_21);
    m_res.a_12 = inner_prod(m_1.a_11, m_1.a_12, m_2.a_12, m_2.a_22);
    m_res.a_21 = inner_prod(m_1.a_21, m_1.a_22, m_2.a_11, m_2.a_21);
    m_res.a_22 = inner_prod(m_1.a_21, m_1.a_22, m_2.a_12, m_2.a_22);
    return m_res;
}

Vec vec_prod(Matrix m, Vec v){
    Vec v_res;
    v_res.u_1 = inner_prod(m.a_11, m.a_12, v.u_1, v.u_2);
    v_res.u_2 = inner_prod(m.a_21, m.a_22, v.u_1, v.u_2);
    return v_res;
}

Matrix mat_fast_power(const Matrix m, const unsigned long long pow){
    Matrix m_power = m, m_res = I;
    for(unsigned long long i = 0; i < MAX_SHIFT_BITS; i++){
        if((pow >> i) & 1){
            m_res = mat_prod(m_power, m_res);
            // printf("Bit %llu, Res Matrix:\n", i);
            // show_mat(m_res);
            // printf("Power Matrix:\n");
            // show_mat(m_power);
        }
        m_power = mat_prod(m_power, m_power);
    }
    return m_res;
}

unsigned long long compute(unsigned long long i){
    if(i == 1){
        return INIT.u_1;
    }else if(i == 2){
        return INIT.u_2;
    }else{
        return vec_prod(mat_fast_power(TRANS, i - 2), INIT).u_1;
    }
}

int main(){
    unsigned long long i = 0;
    while(scanf("%llu", &i) != EOF){
        printf("%llu\n", compute(i));
    }
    return 0;
}