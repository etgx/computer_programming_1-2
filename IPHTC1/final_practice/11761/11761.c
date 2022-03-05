// NTHUOJ 11761 - D - Determinant   
// Description
// Writer: jjjjj19980806       Description: pclightyear        Difficulty: ★★★☆☆
// In linear algebra, the determinant (行列式) is a useful value that can be computed from the elements of a square matrix. The determinant also has many useful properties. For example: Assume we have a square matrix A. Then the determinant of A equals to zero if and only if A is not invertible.
// Given a n × n square matrix A, you have to calculate the determinant of A. (Denoted by det(A))
// Note: 
// (1) We can define the determinant of a 2 × 2 matrix as below:
// (2) We can calculate the determinant of a 3 × 3 matrix as below:

// Input
// The first line contains one integer n, representing the size of A.
// The next n lines contains n integers aij, representing each entry in A.
// It is guaranteed that :
// 1 ≤ n ≤ 8
// -16 ≤ aij ≤ 15
// Note that det(A) may exceed INT.

// Output
// Please output a line contains the value of det(A).

// Sample Input  
// 2
// 1 0
// 0 1

// Sample Output  
// 1

// 2020/06/17 SYC

#include<stdio.h>
#include<stdlib.h>

void showMat(int **mat, const int rows, const int cols){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

void **malloc2D(const int unitSize, const int rows, const int cols){
    void **a = malloc(sizeof(void *) * rows);
    for(int i = 0; i < cols; i++){
        a[i] = malloc(unitSize * cols);
    }
    return a;
}

void free2D(void **mat, const int rows, const int cols){
    for(int i = 0; i < rows; i++){
        free(mat[i]);
    }
}

long long int det(int **mat, const int n){
    if(n == 2){
        return (long long int)(mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0]);
    }

    long long int sum = 0;
    for(int i = 0; i < n; i++){
        // pivot * sub-matrix
        int **matS = (int **)malloc2D(sizeof(int), n - 1, n - 1);
        int pivot = i % 2? -mat[0][i] : mat[0][i];
        // Copy sub-matrix
        for(int p = 0; p < n - 1; p++){
            int across = 0;
            for(int q = 0; q < n; q++){
                if(q == i){across = 1;continue;}
                matS[p][q - across] = mat[p + 1][q];
            }
        }
        // printf("%dth Sub-matrix with pivot %d\n", i, pivot);
        // showMat(matS, n - 1, n - 1);

        sum += (long long int)pivot * det(matS, n - 1);
        free2D((void **)matS, n - 1, n - 1);
    }

    return sum;
}

int main(){
    int n = 0;
    long long int resDet = 0;
    scanf("%d\n", &n);
    int **mat = (int **)malloc2D(sizeof(int), n, n);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            scanf("%d", &(mat[i][j]));
        }
    }

    // showMat(mat, n, n);
    resDet = det(mat, n);
    printf("%lld\n", resDet);

    return 0;
}