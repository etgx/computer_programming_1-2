// NTHUOJ 12135 Ghoul Dawn   
// Description
// A famous streamer once said: " How dare you come down!! Ice Bird!! ", This famous streamer is also known as " Ghoul Dawn ". After killed the Ice Bird, Ghoul Dawn strart to kill little soldiers.
// There're n soldiers in front of Ghoul Dawn, their HP are denote as a1 ~ an .
// Ghoul Dawn's attack can attack at least k soldier at once but must be continuous segment of soldiers.
// The damage Ghoul Dawn can make is the sum of soldiers' HP.
// Ghoul Dawn wants to know the maximum average damage(the sum of soldiers' HP divided by the number of soldiers ) he can make.
// For example:
// There are n=5 soldiers, and a1~an = { 5,9,6,10,3 }.
// Ghoul Dawn can attack k =2 soldiers at once. 
// He can kill either  { 5,9 } or { 9,6,10 } or { 5,9,6,10,3 }..... . He need to choose { 9,6,10 } because (9+6+10)/3  is the maximum average damage he can make.
// Help Ghoul Dawn find out what's the maximum average damage he can make at once. Output the number to three decimal places.
// If you help him, he will tell you how to "Slide up".

// ⠄⠄⠄⠄⠄⠄⠄
//  ⠄⠄⠄⠄⠄⠄⠄⠈⠉⠁⠈⠉⠉⠙⠿⣿⣿⣿⣿⣿
//  ⠄⠄⠄⠄⠄⠄⠄⠄⣀⣀⣀⠄⠄⠄⠄⠄⠹⣿⣿⣿
//  ⠄⠄⠄⠄⠄⢐⣲⣿⣿⣯⠭⠉⠙⠲⣄⡀⠄⠈⢿⣿
//  ⠐⠄⠄⠰⠒⠚⢩⣉⠼⡟⠙⠛⠿⡟⣤⡳⡀⠄⠄⢻
//  ⠄⠄⢀⣀⣀⣢⣶⣿⣦⣭⣤⣭⣵⣶⣿⣿⣏⠄⠄⣿
//  ⠄⣼⣿⣿⣿⡉⣿⣀⣽⣸⣿⣿⣿⣿⣿⣿⣿⡆⣀⣿
//  ⢠⣿⣿⣿⠿⠟⠛⠻⢿⠿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣼
//  ⠄⣿⣿⣿⡆⠄⠄⠄⠄⠳⡈⣿⣿⣿⣿⣿⣿⣿⣿⣿
//  ⠄⢹⣿⣿⡇⠄⠄⠄⠄⢀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿
//  ⠄⠄⢿⣿⣷⣨⣽⣭⢁⣡⣿⣿⠟⣩⣿⣿⣿⠿⠿⠟
//  ⠄⠄⠈⡍⠻⣿⣿⣿⣿⠟⠋⢁⣼⠿⠋⠉⠄⠄⠄⠄
//  ⠄⠄⠄⠈⠴⢬⣙⣛⡥⠴⠂⠄⠄⠄⠄⠄⠄⠄⠄⠄...
// (the photo of the famous streamer)
// HINT: You can use the method "prefix sum(https://en.wikipedia.org/wiki/Prefix_sum)" to solve this question.

// Input
// input contains two lines.
// First line contains two integer n, k( 1<= k <= n <= 5000 )
// Second contains n integer a1~an( 1<= ai <= 109 )

// Output
// output only contains one integer -- the maximum average damage Ghoul Dawn can make. Output the number to three decimal places.
// remember to print \n at the end of output.

// Sample Input  
// 5 2
// 5 9 6 10 3

// Sample Output  
// 8.333

#include<stdio.h>
#include<stdlib.h>

long long int getSum(long long int *prefixSum, int leftIdx, int rightIdx){
    if(leftIdx == 0){
        return prefixSum[rightIdx];
    }else{
        return prefixSum[rightIdx] - prefixSum[leftIdx - 1];
    }
}

int main(){
    int n = 0, k = 0;
    long long int buff[5100] = {0};
    long long int prefixSum[5100] = {0};
    long long int accumSum = 0;
    scanf("%d %d\n", &n, &k);

    for(int i = 0; i < n; i++){
        scanf("%lld", &(buff[i]));
        accumSum += buff[i];
        prefixSum[i] = accumSum;
    }

    long double maxAvgDamage = 0;
    for(int i = 0; i < n; i++){
        for(int j = i + k - 1; j < n; j++){
            long double tempAvgDamage = (long double)getSum(prefixSum, i, j) / (long double)(j - i + 1);
            if(maxAvgDamage < tempAvgDamage){
                maxAvgDamage = tempAvgDamage;
                // printf("%d %d %.3Lf\n", i, j, maxAvgDamage);
            }
        }
    }

    printf("%.3Lf\n", maxAvgDamage);

    return 0;
}