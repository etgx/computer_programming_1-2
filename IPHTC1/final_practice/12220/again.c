// Another AC Version
#include<stdlib.h>
#include<stdio.h>

#define MaxLen 1000005
#define Inf 9223372036854775807

long long int binSearch(long long int *seq, long long int target, long long int start, long long int end){
    long long int mid = (start + end) / 2;
    if(end - start > 0){
        if(target <= seq[mid]){
            return binSearch(seq, target, start, mid);
        }else if(target > seq[mid]){
            return binSearch(seq, target, mid + 1, end);
        }
    }else{
        return mid;
    }
    
}

int main(){
    long long int n = 0, k = 0, q = 0;
    long long int seq[MaxLen] = {0};

    scanf("%lld %lld %lld\n", &n, &k, &q);
    for(long long int i = 0; i < n; i++){
        scanf("%lld", &(seq[i]));
    }

    for(long long int i = 0; i < q; i++){
        long long int f = 0;
        
        scanf("%lld", &f);

        if(f > seq[n - 1]){
            printf("gan ni nya sai bau\n");
        }else{
            long long int outputLeft = 0, outputRight = 0;
            long long int rightDis = 0, leftDis = 0;
            
            outputRight = binSearch(seq, f, k, n - 1);
            outputLeft = binSearch(seq, f, 0, k - 1);
            // printf("OutputRight: %lld OutputLeft: %lld\n", outputRight, outputLeft);
            rightDis = seq[outputRight] - f >= 0? seq[outputRight] - f : f - seq[outputRight];
            leftDis = seq[outputLeft] - f >= 0? seq[outputLeft] - f : f - seq[outputLeft];

            if((seq[k - 1] == seq[k] && rightDis <= leftDis) || (seq[k - 1] != seq[k] && f > seq[k - 1])){
                printf("%lld\n", outputRight + 1 - k);
            }else{
                printf("%lld\n", outputLeft + 1 - k + n);
            }
            // printf("Idx: %lld\n", output - 1);
        }   
    }

    return 0;
}