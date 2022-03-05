// IPHTC2 Week8 Problem 2 | NTHUOJ 12522 - Thanos' Return
// Description
// The Avengers finally gathered all the infinity stones together from different universe, and saved all lives that disappeared five years ago. However, Thanos from different universe comes again. And this time, he'll eliminate the whole universe and create a new one, a grateful universe.
// Thanos needs to compute how many energy he needs to consume to destruct and create a new universe. That is, he has to perform lots of matrix operations, including addition and multiplication. Now he threaten you to calculate these troublesome math, so that he can spend more time to deal with those ants ── those so called "Avengers".
// Thanos thinking on this problem
// If you click on this picture, something might happen...
// You're given R and C, indicate the row number and column number of matrix M.
// An operation OP: + or *, and times TT will be given.

// For operation +, you need to calculate \sum^T_{i=1}M∑_{i=1}^T M and print the result.

// Note that:
// \sum^T_{i=1}M = \underbrace{M+M+\cdots+M}_T
 
// For operation *, you need to calculate \prod^T_{i=1}M and print the result.

// Note that:
// \prod^T_{i=1}M = \underbrace{M\times M\times\cdots\times M}_T
 
// This problem is partial judge. Note that in this problem, you must use C++ to solve this problem.
// We have implemented the interfaces and some functions of the class Matrix for you. What you need to do is to implement the remaining functions.
// Functions we have implemented:

// Matrix()(constructor):
// ​Construct an empty Matrix object.

// const int &getrow():
// ​Get the row number of the corresponding matrix.

// const int &getcol():
// ​Get the column number of the corresponding matrix.

// const int *operator[] (const int &x) const:
// ​Implement operator[] for Matrix class. Make private member mat can be viewed using [] only. For example, we can view M.mat[x][y] by accessing M[x][y] for a Matrix object M.

// void print():
// ​The function to print the whole matrix.

// Functions you have to implement:

// Matrix(int r, int c)(constructor):
// ​Construct an Matrix with row = r and column = c, with all matrix elements equals to 0.

// int *operator[] (const int &x):
// ​Implement operator[] for Matrix class. Make private member mat can be accessed using [] only. For example, we can access M.mat[x][y] by accessing M[x][y] for a Matrix object M.

// Matrix operator+ (const Matrix &x) const:
// ​Perform "addition" operation, then return the result.

// friend Matrix operator* (const Matrix &x, const Matrix &y):
// ​Perform "multiplication" operation, then return the result. Note that this function is declared with friend.
// In case of the result might be too large, all numbers should mod 10007 into non-negative integers.

// Input
// The first line contains R, C, T, and OP, respectively.
// There are R lines below. Each line contains C numbers. These R \times C numbers indicate every element in matrix M.

// 1\le R,\,C\le 100, 0\le T\le 10^{18}
// -10^5\le M\le 10^5−10, where M here indicates all elements in matrix MM.

// Output
// Output the result of the corresponding operation.
// Note that in this problem, you don't have to deal with output format.

// Sample Input 1 
// 3 3 10 *
// 7 5 3
// 8 5 1
// 6 2 4

// Sample Output 1
// /    6849     668    3180 \
// |    7322     184    5769 |
// \    5945    2776     948 /

// Hint
// The structure of class Matrix is:

// const int MAX_N = 102;
// class Matrix {
//     public:
//         Matrix() {
//             row = col = 0;
//             memset(mat, 0, sizeof(mat));
//         }
//         // TODO
//         Matrix(int r, int c);
//         const int &getrow() {
//             return row;
//         }
//         const int &getcol() {
//             return col;
//         }
//         // TODO
//         int *operator[] (const int &x);
//         const int *operator[] (const int &x) const {
//             return mat[x];
//         }
//         // TODO
//         Matrix operator+ (const Matrix &x) const;
//         // TODO: note that this function is declared with the keyword "friend"
//         friend Matrix operator* (const Matrix &x, const Matrix &y);
//         void print() {
//             for(int i=0;i<row;i++) {
//                 if(i==0) std::cout << "/";
//                 else if(i==row-1) std::cout << "\\";
//                 else std::cout << "|";
//                 for(int j=0;j<col;j++) {
//                     std::cout << std::right << std::setw(8) << mat[i][j];
//                 }
//                 if(i==0) std::cout << " \\\n";
//                 else if(i==row-1) std::cout << " /\n";
//                 else std::cout << " |\n";
//             }
//         }
//     private:
//         int mat[MAX_N][MAX_N];
//         int row, col;
// };

// You have to implement all functions marked with "TODO".

#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

#define MOD 10007

int add(int a, int b){return ((a % MOD) + (b % MOD)) % MOD;}

int mul(int a, int b){return ((a % MOD) * (b % MOD)) % MOD;}

long long mul_long(int a, long long b){return (((long long)a % MOD) * (b % MOD)) % MOD;}

// const int MAX_N = 102;
// class Matrix {
//     public:
//         Matrix() {
//             row = col = 0;
//             memset(mat, 0, sizeof(mat));
//         }
//         // TODO
//         Matrix(int r, int c){
//             row = r;
//             col = c;
//         }
//         const int &getrow() {
//             return row;
//         }
//         const int &getcol() {
//             return col;
//         }
//         // TODO
//         int *operator[] (const int &x){
//             return mat[x];
//         }
//         const int *operator[] (const int &x) const {
//             return mat[x];
//         }
//         // TODO
//         Matrix operator+ (const Matrix &x) const{
//             Matrix add_res(x.row, x.col);
//             for(int i = 0; i < x.row; i++){
//                 for(int j = 0; j < x.col; j++){
//                     add_res[i][j] = mat[i][j] + x[i][j];
//                 }
//             }
//             return add_res;
//         }
//         friend Matrix operator* (const Matrix &x, const long long &y){
//             Matrix mul_res(x.row, x.col);
//             for(int i = 0; i < x.row; i++){
//                 for(int j = 0; j < x.col; j++){
//                     mul_res[i][j] = (int)mul_long(x[i][j], y);
//                 }
//             }
//             return mul_res;
//         }
//         // TODO: note that this function is declared with the keyword "friend"
//         friend Matrix operator* (const Matrix &x, const Matrix &y){
//             Matrix mul_res(x.row, x.col);
//             for(int i = 0; i < x.row; i++){
//                 for(int j = 0; j < x.col; j++){
//                     mul_res[i][j] = 0;
//                     for(int k = 0; k < x.col; k++){
//                         mul_res[i][j] = add(mul_res[i][j], mul(x[i][k], y[k][j]));
//                     }
//                 }
//             }
//             return mul_res;
//         }
//         void print() {
//             for(int i=0;i<row;i++) {
//                 if(i==0) std::cout << "/";
//                 else if(i==row-1) std::cout << "\\";
//                 else std::cout << "|";
//                 for(int j=0;j<col;j++) {
//                     std::cout << std::right << std::setw(8) << mat[i][j];
//                 }
//                 if(i==0) std::cout << " \\\n";
//                 else if(i==row-1) std::cout << " /\n";
//                 else std::cout << " |\n";
//             }
//         }
//     private:
//         int mat[MAX_N][MAX_N];
//         int row, col;
// };

Matrix::Matrix(int r, int c){
    row = r;
    col = c;
}

int *Matrix::operator[] (const int &x){
    return mat[x];
}

Matrix Matrix::operator+ (const Matrix &x) const{
    Matrix add_res(x.row, x.col);
    for(int i = 0; i < x.row; i++){
        for(int j = 0; j < x.col; j++){
            add_res[i][j] = mat[i][j] + x[i][j];
        }
    }
    return add_res;
}
// Matrix operator* (const Matrix &x, const long long &y){
//     Matrix mul_res(x.row, x.col);
//     for(int i = 0; i < x.row; i++){
//         for(int j = 0; j < x.col; j++){
//             mul_res[i][j] = (int)mul_long(x[i][j], y);
//         }
//     }
//     return mul_res;
// }
// TODO: note that this function is declared with the keyword "friend"
Matrix operator* (const Matrix &x, const Matrix &y){
    Matrix mul_res(x.row, x.col);
    for(int i = 0; i < x.row; i++){
        for(int j = 0; j < x.col; j++){
            mul_res[i][j] = 0;
            for(int k = 0; k < x.col; k++){
                mul_res[i][j] = add(mul_res[i][j], mul(x[i][k], y[k][j]));
            }
        }
    }
    return mul_res;
}

Matrix zero_matrix(int r, int c){
    Matrix m(r, c);
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            m[i][j] = 0;
        }
    }
    return m;
}

Matrix identity_matrix(int r, int c){
    Matrix m(r, c);
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            m[i][j] = 0;
        }
    }
    int n = r < c? r : c;
    for(int k = 0; k < n; k++){
        m[k][k] = 1;
    }
    return m;
}

Matrix identity2_matrix(int r, int c){
    Matrix m(r, c);
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            m[i][j] = 0;
        }
    }
    int n = r < c? r : c;
    for(int k = 0; k < n; k++){
        m[k][k] = 2;
    }
    return m;
}

Matrix fast_add(Matrix m, long long T){
    Matrix base = m, accum = zero_matrix(m.getrow(), m.getcol()), iden2 = identity2_matrix(m.getrow(), m.getcol());
    for(int i = 0; i < 64; i++){
        if((T >> i) & 1){
            accum = accum + base;
        }
        base = base * iden2;
    }
    return accum;
}

Matrix fast_power(Matrix m, long long T){
    Matrix base = m, accum = identity_matrix(m.getrow(), m.getcol());
    for(int i = 0; i < 64; i++){
        if((T >> i) & 1){
            accum = accum * base;
        }
        base = base * base;
    }
    return accum;
}

// Matrix mul_const(Matrix m, long long T){
//     return m * T;
// }

int main(){
    long long R = 0, C = 0, T = 0;
    char OP = 0;
    scanf("%lld %lld %lld %c\n", &R, &C, &T, &OP);

    Matrix m(R, C);
    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; j++){
            scanf("%d", &(m[i][j]));
        }
    }

    if(OP == '*'){
        // printf("OP: *\n");
        fast_power(m, T).print();
    }else if(OP == '+'){
        // printf("OP: +\n");
        fast_add(m, T).print();
    }else{
        printf("ERR\n");
    }
}