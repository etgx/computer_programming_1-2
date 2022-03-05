// NTHUOJ 10716 Arithmetic Sequence   

// Description
// An arithmetic sequence is a sequence of numbers such that the difference between the consecutive terms is a constant. For instance, the sequence 5, 7, 9, 11, 13, 15 … is an arithmetic sequence with common difference of 2.
// Here, you are given an arithmetic sequence, where the initial term is ‘a’, the total number of terms in this sequence is ‘n’, and the common difference of successive terms is ‘d’. Then, in this sequence: what is the value of the nth term, and what is the sum of all the terms?

// Input
// Three integers separated by blanks. The first integer (a) is the initial term, where -1000<a<1000. The second integer (n) is the total number of terms in the sequence, where n>0 and n<1000. The third integer (d) is the common difference, where -1000<d<1000.

// Output
// Two values separated by a blank. The first value is the nth term of the sequence, and the second value is the sum of the sequence.  Note that you do not need to print '\n' at the end of the output.

// Sample Input  
// 2 5 1

// Sample Output  
// 6 20

// 2020/05/01 SYC

#include<stdio.h>
#include<stdlib.h>

int main(){
    long int a = 0, n = 0, d = 0;
    scanf("%ld %ld %ld\n", &a, &n, &d);

    long int last = a + ((n - 1) * d);
    long int sum = (a + last) * n / 2;
    printf("%ld %ld", last, sum);

    return 0;
}