#include <stdio.h>
#include <stdlib.h>
#define MaxPower 60

// Calculate how many competitions for specific students 
long long int s2c(const long long int k, const int pow){
    return (k * (k - 1UL) >> 1) + k * ((1UL << pow) - 1UL);
}

long long int odd(const long long int idx){
    return (idx * 2UL) + 1;
}

long long int binSearch(const long long int target, const int pow){
    const long long int upper = 1UL << (60 - pow);
    // printf("%lld\n", upper);
    // printf("%lld\n", s2c(1UL, 60));
    // printf("%lld\n", s2c(1152921504606846976UL, 0));
    // printf("%lld\n", odd(1152921504606846976UL));
    // Search for correct Odd Number
    long long int start = 0UL, end = upper;
    long long int mid = (start + end) >> 1;
    while(start < end){
        if(s2c(odd(mid), pow) < target){
            // printf("Start: %lld , End: %lld, Mid: %lld, Pow: %d, s2c: %lld < Target: %lld\n", start, end, mid, pow, s2c(odd(mid), pow), target);
            start = mid + 1UL;
        }else{
            // printf("Start: %lld , End: %lld, Mid: %lld, Pow: %d, s2c: %lld >= Target: %lld\n", start, end, mid, pow, s2c(odd(mid), pow), target);
            end = mid;
        }
        mid = (start + end) >> 1;
    }

    if(s2c(odd(mid), pow) == target){
        // printf("Res: %lld\n", odd(mid) << pow);
        return odd(mid) << pow;
    }
    else{return -1;}
}

int main(){
    int t = 0;
    scanf("%d", &t);

    for(int i = 0; i < t; i++){
        long long int x = 0;
        scanf("%lld", &x);

        // Iterate Power 2^0 ~ 2^60
        long long int res = -1;
        for(int i = 0; i <= 60; i++){
            res = binSearch(x, i);
            if(res != -1){break;}
        }
        if(res == -1){printf("-1\n");}
        else{printf("%lld\n", res);}
    }

    return 0;
}