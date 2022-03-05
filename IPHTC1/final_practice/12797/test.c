#include <stdio.h>
#include <stdlib.h>
 
int main(){
    int T = 0;
    scanf("%d\n", &T);

    for(int i = 0; i < T; i++){
        long int A = 0, B = 0, C = 0, D = 0;
        long int ans = 0;
        int seq[100009] = {0};
        scanf("%ld %ld %ld %ld\n", &A, &B, &C, &D);

        for(int j = A; j <= B; j++){
            seq[j + B]++;
            seq[j + C + 1]--;
        }

        for(int j = A + B; j <= B + C + 1; j++){
            seq[j] = seq[j - 1] + seq[j];
        }

        for(int j = A + B; j <= C + D; j++){
            seq[j] = seq[j - 1] + seq[j];
        }

        for(int j = C; j <= D; j++){
            ans += (seq[B + C] - seq[j]);
        }

        printf("%ld\n", ans);
    }

    return 0;
}