// Another AC Version
#include <stdio.h>
#include <stdlib.h>

long long int fastP(const long long int x, const long long int y, const long long int m){
    // For power y:
    // if y is even: x ^ y = (x ^ 2) ^ (y >> 1)
    // if y is odd: x ^ y = x * (x ^ 2) ^ ((y - 1) >> 1)
    // For mod:
    // (x ^ y) % mod = ((x % mod) ^ y) % mod

    long long int base = x;
    long long int accum = 1;
    long long int p = y;
    if(p == 0 || x == 1){return accum % m;} // Problem is here, since: any number % 1 = 0
    else if(p >= 1){
        while(p > 1){
            if(p & 1){// Odd
                accum = (accum % m) * (base % m) %m;
                base = (base % m) * (base % m) % m;
            }else{// Even
                base = (base % m) * (base % m) % m;
                
            }
            p = p >> 1;
        }
    }

    return ((base % m) * (accum % m)) % m;
}

int main(){
    long long int x = 0, y = 0, m = 0;
    scanf("%lld %lld %lld\n", &x, &y, &m);
    printf("%lld\n", fastP(x, y, m));

    return 0;
}