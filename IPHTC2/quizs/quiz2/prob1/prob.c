#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_M_SIZE 400005

void build_prefix_sum(long long *prefix_sum, long long num_real_size, char *m, long long l){
    long long buf_size = l + 1, cmp_l_str_size = l + 1;
    char *buf = (char*)malloc(sizeof(char) * buf_size);
    char *cmp_l_str = (char*)malloc(sizeof(char) * cmp_l_str_size);

    for(long long i = 0; i < l; i++){
        cmp_l_str[i] = '0';
    }
    cmp_l_str[l] = 0;
    
    for(int i = 0; i <= num_real_size; i++){
        if(i < l){
            prefix_sum[i] = 0;
        }else{
            memset(buf, 0, buf_size);
            memcpy(buf, &(m[i - l]), l);
            if(strncmp(buf, cmp_l_str, l) == 0){
                prefix_sum[i] = prefix_sum[i - 1] + 1;
            }else{
                prefix_sum[i] = prefix_sum[i - 1];
            }
        }
    }
    free(buf);
    free(cmp_l_str);
}

long long count_occur(long long l, long long *prefix_sum, long long L, long long R){
    long long a_reindex = L + l - 1;
    if(a_reindex <= R)
        return prefix_sum[R] - prefix_sum[a_reindex - 1];
    else
        return 0;
}

int main(){
    long long a = 0, b = 0, n = 0, q = 0, l = 0, net_shift = 0, num_real_size = 0;
    scanf("%lld %lld %lld\n", &a, &b, &n);
    char *m = (char*)malloc(sizeof(char) * MAX_M_SIZE);
    memset(m, 0, MAX_M_SIZE);

    net_shift = a - b;
    if(net_shift > 0){
        for(long long i = 0; i < net_shift; i++){
            m[i] = '0';
        }
        num_real_size = 0;
    }else{
        long long shift_ignore = n + net_shift, zero_padding_num = 0;
        num_real_size = 0;

        for(long long i = 0; i < shift_ignore; i++){getchar();}
        for(long long i = shift_ignore; i < n; i++){
            long long idx = i - shift_ignore;
            m[idx] = getchar();
            printf("M[%lld]: %c\n", idx, m[idx]);
        }
        num_real_size += (n - shift_ignore);

        // Zero-padding at the tail
        for(long long i = 0; i < a; i++){
            long long idx = i + n - shift_ignore;
            m[idx] = '0';
            printf("M[%lld]: %c\n", idx, m[idx]);
        }
        num_real_size += a;
        printf("With Padding M: %s, num_real_size: %lld\n", m, num_real_size);

        // Count zero paddings at the head(useless zeros)
        for(zero_padding_num = 0; m[zero_padding_num] == '0'; zero_padding_num++){
            if(m[zero_padding_num] == 0){
                break;
            }
        }
        printf("zero_padding_num: %lld, num_real_size: %lld\n", zero_padding_num, num_real_size);

        // Remove zero paddings at the head
        for(long long i = 0; i < num_real_size; i++){
            m[i] = m[i + zero_padding_num];
        }
        num_real_size -= zero_padding_num;
    }
    printf("M: %s, num_real_size: %lld\n", m, num_real_size);

    // scanf("%s", m);
    scanf("%lld %lld\n", &q, &l);
    long long *prefix_sum = (long long*)malloc(sizeof(long long) * num_real_size);
    memset(prefix_sum, 0, sizeof(long long) * num_real_size);
    build_prefix_sum(prefix_sum, num_real_size, m, l);

    for(long long i = 0; i < q; i++){
        long long L = 0, R = 0;
        scanf("%lld %lld\n", &L, &R);
        printf("%lld\n", count_occur(l, prefix_sum, L, R));
    }

    // 需要處理0的問題，因為 mod 完後最小還會是0

    return 0;
}