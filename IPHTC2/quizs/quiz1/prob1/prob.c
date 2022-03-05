#include <stdio.h>
#include <stdlib.h>

#define MAX_DIGITS 10
#define MAX_NUM 1000003

long long count_1_prefix_sum[MAX_NUM] = {0};

long long count1s(long long a, long long b){
    return count_1_prefix_sum[b] - count_1_prefix_sum[a - 1];
}

long long count1(long long num){
    long long counter_1 = 0;
    char strInt[MAX_DIGITS] = {0};
    sprintf(strInt, "%lld", num);
    for(long long i = 0; i < MAX_DIGITS; i++){
        if(strInt[i] == '1')
            counter_1++;
    }
    return counter_1;
}

int main(){
    for(long long i = 1; i < MAX_NUM; i++){
        long long count_1 = count1(i);
        count_1_prefix_sum[i] = count_1_prefix_sum[i - 1] + count_1;
    }

    long long t = 0;
    scanf("%lld", &t);
    // printf("T: %lld\n", t);
    for(long long i=0; i < t; i++){
        long long a = 0, b = 0;
        scanf("%lld %lld\n", &a, &b);
        printf("%lld\n", count1s(a, b));
    }
    return 0;
}