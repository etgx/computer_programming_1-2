// NTHUOJ 12139 HA HA HA   
// Description
// There are n children in Johnny Johnny' s family.
// And number i child wants to have ai units of sugar.
// But their PaPa don't want them eat too much sugar. Therefore he will randomly choose some children and only give them the great common divisor of ai. 
// For example, if there're n=5 children and ai = { 1, 4, 6, 7, 18 }.
// Suppose PaPa choose the children numbered 2,3,5.
// Then all children will only get  gcd(a2, a3, a5) = gcd(4,6,18) = 2 unit of sugar.
// Now Johnny wants to know what's the maximum amount of sugar they can get.(PaPa will at least choose two child) 
// If you can help him, he will laugh at you for you don't have any sugar " Ha Ha Ha!!! "
// To calculate great common divisor, you can use the method 輾轉相除法(https://zh.wikipedia.org/wiki/%E8%BC%BE%E8%BD%89%E7%9B%B8%E9%99%A4%E6%B3%95)

// Input
// input contains two lines.
// First line only contains one integer n ( 2 <= n <=  1000)
// Second line contain n integers a1 ~ an ( 1<= ai <= 1000 )

// Output
// output contains only one integer the maximum amount of sugar they can get.
// remember to print \n at the end of output.

// Sample Input  
// 5
// 1 4 6 9 18

// Sample Output  
// 9

// 2020/05/01 SYC

#include<stdio.h>
#include<stdlib.h>

int gcd(int m, int n){
    int t = 1;
    while(t != 0){
        t = m % n;
        m = n;
        n = t;
    }

    return m;
}

int main(){
    int n = 0;
    int max = 0;
    int array[1005] = {0};
    scanf("%d\n", &n);

    for(int i = 0; i < n; i++){
        int t = 0;
        scanf("%d", &t);
        array[i] = t;
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i != j){
                int gcdRes = gcd(array[i], array[j]);
                if(max < gcdRes){
                    max = gcdRes;
                }
            }
        }
    }
    // printf("%d\n", gcd(12, 1024));
    printf("%d\n", max);

    return 0;
}