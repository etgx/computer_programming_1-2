#include <stdio.h>
#include <stdlib.h>
#define MaxI 60 // 10^3 ~ 2^10 -> 10^18 ~ 2^60
#define MaxK 1000000000000000000 // 10^18
#define MaxKI 499999
            //   576460752303423488
#define Error -1

int main(){
    const long long int unit = 1;
    long long int t = (unit << 60) * 256; 
    printf("%lld\n", t);

    return 0;
}