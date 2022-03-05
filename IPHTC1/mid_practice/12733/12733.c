// NTHUOJ 12733 - Salary thief   
// Description
// I'm a salary thief who don't answer students' question

// ~by anonymous TA

// "I sucked!" TA think he's the worst, therefore he only asks you to do some cut and paste.

// You got a string and your cursor is at the leftmost position of the string.

// Let's call the leftmost position of the string position 0.

// The string only contains character '1'~'3'.

// You need to move the cursor to the right x times.

// Each time only cross one character.

// After the move, you divide the string into two part.

// You cut the right part, and paste it for n times.

// For n = the last character of left part of the string.

// You need to answer how long the string is after x moves.

// Because the string may be very long, you only need to answer the length of the final string mod 10^9+7(output positive number)

// We guarantee that each move will not on empty character​. 

// Example:

// Given x = 5, string = "231"

// Move 1(position 0->1):

// cut the string "231" -> "2" and "31"

// the last character of left part of the string = "2"

// past "31" for 2 times, we got "23131"

// Move 2(position 1->2):

// cut the string "23131" -> "23" and "131"

// the last character of left part of the string = "3"

// past "131" for 3 times, we got "23131131131"

// Move 3(position 2->3):

// cut the string "23131131131" -> "231" and "31131131"

// the last character of left part of the string = "1"

// past "31131131" for 1 times, we got "23131131131"

// Move 4(position 3->4):

// cut the string "23131131131" -> "2313" and "1131131"

// the last character of left part of the string = "3"

// past "1131131" for 3 times, we got "2313113113111311311131131"

// Move 5(position 4->5):

// cut the string "2313113113111311311131131" -> "23131" and "13113111311311131131"

// the last character of left part of the string = "1"

// past "13113111311311131131" for 1 times, we got "2313113113111311311131131"

 

// The final string "2313113113111311311131131" has length 25.

// The answer will be 25%(10^9+7) = 25

 

// Input
// First line contains one integer t(1 <= t <= 10) which means the number of testcases.

// Each testcase contains two lines.

// First line contains one integer x(1 <= x <= 10^6)

// Second line contains a string. ( 1 <= length of the string <= 500)

// Output
// For each testcase, print only one positive number which means the length of the final string mod 10^9+7

// Remember to print \n at the end of output.

// Sample Input  
// 4
// 5
// 231
// 7
// 2323
// 6
// 333
// 24
// 133321333

// Sample Output  
// 25
// 1438
// 1101
// 686531475


#include<stdio.h>
#include<stdlib.h>

int main(){
    long int t = 0;
    long long int mod = 1000000007;

    scanf("%ld\n", &t);
    // printf("%ld\n", t);
    for(long int i = 0; i < t; i++){
        long int x = 0;
        long int strLen = 0;
        long long int storedStrLen = 0;
        char tempC;
        char str[1000005] = {0};

        scanf("%ld\n", &x);
        while((tempC = getchar()) != EOF){
            if(tempC == '\n') break;

            str[strLen] = tempC;
            // printf("%c", str[strLen]);
            strLen++;
            storedStrLen++;
        }
        // printf("\nStrLen: %ld\n", strLen);

        long long int lenCount = strLen;
        for(long int j = 0; j < x; j++){
            char copyTimesChar = str[j];
            int copyTimes = atoi(&copyTimesChar);
            long long int copiedStrLen = (lenCount - j - 1) % mod;
            // printf("%ldth Copy\n", j + 1);
            // printf("CopyTimes: %d\n", copyTimes);

            // Update Stored String
            int escFlag = 0;
            long long int copyStrStart = j + 1;
            for(int h = 0; h < copyTimes - 1; h++){
                // printf("Copy Recursive%d\n", h + 1);
                for(long long int k = 0; k < copiedStrLen; k++){
                    if(storedStrLen < x){
                        // printf("storedStrLen: %lld < x: %ld\n", storedStrLen, x);
                        str[storedStrLen] = str[copyStrStart + k];
                        storedStrLen++;
                        // printf("UPDATED storedStrLen: %lld < x: %ld\n", storedStrLen, x);
                    }else{
                        escFlag = 1;
                        break;
                    }
                }
                if(escFlag){break;}
            }

            // Update the counter
            lenCount += (copiedStrLen * (copyTimes - 1)) % mod;
            // printf("Add Len: %lld * (%d - 1) =  %lld -> %lld\n", copiedStrLen, copyTimes, copiedStrLen * (copyTimes - 1), lenCount);
            // lenCount = lenCount % (1000000007);
            // printf("Moded LenCount: %lld\n", lenCount);
            // printf("----------------------------------------------------------------------------------\n");
        }

        printf("%lld\n", lenCount % mod);
        // printf("======================================================================================\n");
    }

    return 0;
}