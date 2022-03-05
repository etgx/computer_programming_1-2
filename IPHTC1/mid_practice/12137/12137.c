// NTHUOJ 12137 - Johnny Johnny   
// Description
// PaPa suspected that Johnny ate the sugar, yet Johnny said he hadn't eaten it.

// Therefore, PaPa asked: " Telling lies? "

// Johnny replied: " No PaPa. "

// PaPa then demanded: " Open your mouth! "

// Johnny laughed embarrassedly: " Ha Ha Ha!!! "

// PaPa is so furious with Johnny telling lies, so he punished Johnny to do some math.

// PaPa gave Johnny n numbers a1 ~ an and a number k.

// PaPa asked Johnny to calculate how many ways he could pick some numbers from a1 to an in order to make their sum equal to k?

// For example:

// Given n = 5 and numbers are { 1,2,3,3,3 }, and k = 3, the answer is 4.

// (Note that although there are three identical "3", we still consider them as different indentities.) { (1, 2), (3), (3), (3) }

// Johnny is a bad boy, so he commands you to do this for him!

 

 

// Input
// Input contains two lines.

// First line contains two integer n ( 1 <= n <= 20 ), k ( 1<=  k <=109)

// Second line contains n integer a1 ~ an ( 1 <= ai <= 107 )

 

// Output
// Output only contains one integer that is sum of available ways to pick numbers, which summation is equal to k.

// Remember to print \n at the end of output.

// Sample Input  
// 5 3
// 1 2 3 3 3

// Sample Output  
// 4


#include<stdio.h>
#include<stdlib.h>

int accum(long int *seq, int layer, int limit, long int sum, long int target, int *count){
    long int newSumAdded = seq[layer] + sum;
    // printf("%ld", seq[layer]);
    if(newSumAdded == target){
        (*count)++;
    }else if(layer <= limit){
        accum(seq, layer + 1, limit, newSumAdded, target, count);
    }
    if(layer <= limit){
        accum(seq, layer + 1, limit, sum, target, count);
    }
}

int main(){
    int n = 0, k = 0;
    long int seq[23] = {0};
    scanf("%d %d", &n, &k);

    for(int i = 0; i < n; i++){
        scanf("%ld", &(seq[i]));
        // printf("%ld", (seq[i]));
    }

    int *count = (int *)malloc(sizeof(int));
    accum(seq, 0, n, 0, k, count);
    printf("%d\n", (*count));

    return 0;
}
