// NTHUOJ 10728 A simple set problem  

// Description
// Out of the N NTHU 2015 Computer Science (CS) majors, X of them take the course CS13550* Introduction to Programming (I), Y of them take the course CL10100* College Chinese, and Z of them take none of the two courses (i.e., CS13550* and CL10100*). How many NTHU 2015 CS majors take both of the two courses? And how many take CS13550* but not CL10100*?

// Input
// Four integers N, X, Y, Z which are separated by blanks. Note that 0<N<1000, 0<X<1000, 0<Y<1000 and 0<Z<1000.

// Output
// Two integers separated by a blank. The first integer is the number of NTHU 2015 CS majors who take both CS13550* and CL10100*, and the second one is the number of NTHU 2015 CS majors who take CS13550* but not CL10100*. Note that you do not need to print '\n' at the end of the output.

// Sample Input  
// 60 28 35 5

// Sample Output  
// 8 20

// 2020/05/01 SYC

#include<stdio.h>
#include<stdlib.h>

int main(){
    int N = 0, X = 0, Y = 0, Z = 0;
    scanf("%d %d %d %d\n", &N, &X, &Y, &Z);

    int both = (X + Y) - (N - Z);
    int onlyCS13 = X - both;
    printf("%d %d", both, onlyCS13);

    return 0;
}