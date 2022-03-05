// NTHUOJ 10772 - The number of occurrences   
// Description
// Given a string A and n strings B1, B2, B3, …, Bn, count the number of occurrences of string A in each of B1, B2, B3, … , and print the maximum number of occurrences. All of the strings contain only digits.
// For example, if A is “50” , n = 3, and the n strings are
// “5005”
// “055050”
// “55000”
// then your answer should be 2 because A appears in “5005”  one time,  in “055050” two times, and in “55000” one  time. So the maximum number of occurrences is 2.
// Note that if A is “99” and B1 is “9999”, the number of occurrences of A in B1 is counted as 3.
// You may assume string B1 is always longer than string A.

// Input
// The first line of the input is the string A (0<length of A<=4). The second line is n (1<n<10) .
// For the next n lines, each line contains a string Bi (length of A < length of Bi <9) and a ‘\n’ at the end of the line.

// Output
// The maximum number of occurrences of A appears in B1, B2, …, Bn. Note that you DO NOT need to print ‘\n’ at the end of the output.

// Sample Input  
// 12
// 4
// 12112212
// 12121212
// 111222
// 12112

// Sample Output  
// 4

// 2020/05/01 SYC

#include<stdio.h>
#include<stdlib.h>

int countOccur(char *A, int sizeOfA, char *Bi, int sizeOfBi){
    int occurTimes = 0;

    for(int i = 0; i <= sizeOfBi - sizeOfA; i++){ // Inside Bi
        int isSame = 1;

        for(int j = 0; j < sizeOfA; j++){ // Inside A
            // printf("%c %c\n", A[j], Bi[i + j]);
            if(A[j] != Bi[i + j]){isSame = 0;}
        }

        if(isSame){occurTimes++;}
    }
    // printf("A: %d, B: %d, %d\n", sizeOfA, sizeOfBi, occurTimes);
    return occurTimes;
}

int main(){
    int n = 0;
    char A[6] = {0};
    int sizeOfA = 0;

    scanf("%s\n", A);
    scanf("%d\n", &n);
    while(A[sizeOfA] != '\0'){
        sizeOfA++;
    }

    int maxOccur = 0;
    for(int i = 0; i < n; i++){
        char Bi[15] = {0};
        int sizeOfBi = 0;
        scanf("%s\n", Bi);

        while(Bi[sizeOfBi] != '\0'){
            sizeOfBi++;
        }
        
        // printf("%s\n", Bi);

        int occurOfA = countOccur(A, sizeOfA, Bi, sizeOfBi);
        if(maxOccur < occurOfA){maxOccur = occurOfA;}
    }

    printf("%d", maxOccur);

    return 0;
}