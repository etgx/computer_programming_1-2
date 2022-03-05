// NTHUOJ 10786 Progression   

// Description
// The input contains three numbers, which are the 2nd, the 3rd and the 4th number of  an arithmetic progression (等差數列) or a geometric progression (等比數列). Your task is to distinguish which progression it is from this numbers and print out the first number and the 5th number.
// For example, if the input is  3 5 7, then you know this is an arithmetic progression and the common difference is 2. So the 1st and 5th number is 1 and 9 respectively.
// There are NO progression like 1 1 1 or 2 2 2 which are both an arithmetic progression and a geometric progression.

// Input
// Three integers

// Output
// The 1st and the 5th number of the progression. The two numbers should be separated by a blank.
// You DO NOT need to print ‘\n’ at the end of the output.

// Sample Input  
// 2 -4 8
// Sample Output  
// -1 -16

// 2020/05/01 SYC

#include<stdio.h>
#include<stdlib.h>

int main(){
    long int n2 = 0, n3 = 0, n4 = 0;
    scanf("%ld %ld %ld\n", &n2, &n3, &n4);

    if(n4 - n3 == n3 - n2){
        printf("%ld %ld", n2 - (n3 - n2), n4 + (n3 - n2));
    }else if(n2 != 0 && n3 != 0){
        if(n4 / n3 == n3 / n2){
            printf("%ld %ld", n2 / (n3 / n2), n4 * (n3 / n2));
        }
    }

    return 0;
}