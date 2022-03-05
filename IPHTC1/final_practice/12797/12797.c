// NTHUOJ 12797 - Unlimited Triangle Work   
// Description
// Recently, Gilgamesh found that he's almost lack of swords in his vault, so he wants to forge a lot of swords with different shapes. He command you to forge for him!
// Gilgamesh's sword can only be forged by triangle. Different triangle can be forged into a unique sword. He will give you the intervals of the edges of triangles, you have to calculate how many swords with different shape can he get?
// king
// Gilgamesh threats you with his "Gate of Babylon".
// You are given four positive integer , you're going to count how many triangle that can be build by edges with length , where .
// For example: 
// You can build triangles with edges : .
// So the answer is 4.

// Input
// The first line contains one integer , there are  testcases below.
// For each testcase, the four integer  is given respectively.
// .
// .

// Output
// For each testcase, output its answer, followed by a newline character.

// Sample Input  
// 5
// 1 2 3 4
// 1 5 9 16
// 1 50 100 2000
// 10 1364 9841 50000
// 50000 50000 50000 50000

// Sample Output  
// 4
// 35
// 22100
// 423883295
// 1

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

        for(long int j = A; j <= B; j++){
            seq[j + B]++;
            seq[j + C + 1]--;
        }

        for(long int j = A + B; j <= B + C + 1; j++){
            seq[j] = seq[j - 1] + seq[j];
        }

        // for(int q = 0; q < 15; q++){
        //     printf("%d ", seq[q]);
        // }
        // printf("\n");

        for(long int j = A + B; j <= D + C + 1; j++){
            seq[j] = seq[j - 1] + seq[j];
        }

        // for(int q = 0; q < 15; q++){
        //     printf("%d ", seq[q]);
        // }
        // printf("\n");

        for(long int k = C; k <= D; k++){
            ans += (seq[B + C] - seq[k]);
        }

        printf("%ld\n", ans);
    }
    return 0;
}