// NTHUOJ 11567 Hexadecimal to Binary   
// Description
// Please try to add 2 hexadecimal numbers,  and give the answer as binary number.
// EX: Given A and B, we know that A represents 10 and B represents 11 in decimal, 10 + 11 = 21.
// 21 is 10101 in binary form , so the answer is 10101.
// Hint: You can use %x to read hexadecimal numers ：)
// (Reference) Below is Acsii Table：

// Input
// Two hexadecimal numbers X and Y.

// Output
// The sum of X and Y in binary form.

// Sample Input  
// 55
// BB

// Sample Output  
// 100010000

// 2020/05/01 SYC

#include<stdio.h>
#include<stdlib.h>

void bin(int dec){
    if(dec > 0){
        bin(dec / 2);
        printf("%d", dec % 2);
    }
}

int main(){
    int X = 0, Y = 0;
    scanf("%x\n%x\n", &X, &Y); // Important: Notice that be care about long int must match %lx

    int remain = X + Y;
    // char buff[1000] = {0};
    // int binLen = 0;

    bin(remain);

    // if(remain == 0){
    //     buff[0] = '0';
    //     binLen = 1;
    // }else{
    //     while(remain > 0){
    //         buff[binLen] = (remain & 1) + '0';
    //         remain = remain >> 1;
    //         binLen++;
    //     }
    // }

    // for(int i = binLen - 1; i >= 0; i--){
    //     printf("%c", buff[i]);
    // }

    return 0;
}