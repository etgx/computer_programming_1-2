// 助教您好，這個bug我確定有修@@，因為用gcc compile的時候有跳出這個warning，有特別把他修好@@
#include<stdio.h>
#include<stdlib.h>

// void bin(long int dec){
//     if(dec > 0){
//         bin(dec / 2);
//         printf("%ld", dec % 2);
//     }
// }

int main(){
    long int X = 0, Y = 0;
    scanf("%lx\n%lx\n", &X, &Y);

    int remain = X + Y;
    char buff[1000] = {0};
    int binLen = 0;

    // bin(remain);

    if(remain == 0){
        buff[0] = '0';
        binLen = 1;
    }else{
        while(remain > 0){
            buff[binLen] = (remain & 1) + '0';
            remain = remain >> 1;
            binLen++;
        }
    }

    for(int i = binLen - 1; i >= 0; i--){
        printf("%c", buff[i]);
    }

    return 0;
}