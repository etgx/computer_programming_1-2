// NTHUOJ 11576 Time conversion   
// Description
// Please convert 24-h time format to 12-h time format .
// Hint1:
// You can define an integer called 'flag' to indicate a.m. or p.m.
// And then you can use 'flag' to compute the key information : 'a' , 'p'
// int key_info = 'a' * ((flag+1)%2) + 'p' * flag ; 
// key_info will be 'p' when flag is 1 , and be 'a' when flag is 0.
// Hint2:
// Note that 1200 belongs to p.m. 
// Namely, the output should be 00:00 p.m.
// and 0000 belongs to a.m.
// Namely, the output should be 00:00 a.m.

// Input
// always a 4-digit integer

// Output
// hour    +   ":"   +  minute  +  "whitespace"  +  "a.m." / "p.m."
// (2-digit)                (2-digit)

// hour and minute numbers need to have 0 prepended if needded.

// Note that there is no need to add "\n" at the end of output.

// Sample Input  
// 0000

// Sample Output  
// 00:00 a.m.

// 2020/05/01 SYC

#include<stdio.h>
#include<stdlib.h>

int main(){
    char hrStr[3] = {0}, minStr[3] = {0};
    scanf("%c%c%c%c", &(hrStr[0]), &(hrStr[1]), &(minStr[0]), &(minStr[1]));

    int hr = (hrStr[0] - '0') * 10 + (hrStr[1] - '0');
    int amOrPm = hr < 12 || hr == 24? 1 : 0;

    if(hr == 24){
        hr = 0;
    }else if(hr >= 12){
        hr = hr - 12;
    }

    printf("%02d:%s %s", hr, minStr, amOrPm? "a.m." : "p.m.");

    return 0;
}