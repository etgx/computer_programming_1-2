// NTHUOJ 12801 - Poorgrammer   
// Description
// A program a day keep girls away.
// ~by anonymous programmer
// You are a programmer, you need to write code day and night.
// In order to keep you in a sharp mind, you drink a lot of coffee.
// Given n cups of coffee, the ith cup of coffee has the effect that make
// you write ai lines of code and ai will be decreasing order.
// Each cup of coffee can only be drunk for once.
// You need to write m lines of code.
// In a day when you drink a cup of coffee,
// the second cup of coffee will loss it's effect by 1
// and the third cup of coffee will loss it's effect by 2
// ..... and so on
// You need to find out what's the minimum number of days
// that you can finish m lines of code.

// Example:
// Given n = 5 cups of coffee, you need to finish m=16 lines of code.
// The effect of coffee = a1 = 5, a2 = 5, a3 = 5, a4 = 5, a5 = 5
// If you drink a1~a4 at the first day, you finish 5 + (5-1) + (5-2) + (5-3) = 14 lines of code.
// If you drink a5 at the second day, you finish 5 lines of code.
// 14+5 >= 16 therefore you can finish your code by 2 days,
// and it's the minimum number of days that you can achieve.

// Input
// First line contains one integer t(1 <= t <= 10) which means the number of testcases.
// Each testcases contains two lines.
// First line contains two integer n(1 <= n <= 2*10^5), m(1 <= m <= 10^9)
// Second line contains n numbers ai(1 <= ai <= 10^9)

// Output
// For each testcase print only one number which means the minimum number of days
// that you can finish m lines of code.
// If you can't finish your code in any way, print -1.
// Remember to print \n at the end of output.

// Sample Input  
// 5
// 5 8
// 3 2 2 1 1
// 7 10
// 4 4 3 2 2 1 1
// 5 15
// 5 5 5 5 5
// 5 16
// 5 5 5 5 5
// 5 26
// 5 5 5 5 5

// Sample Output  
// 4
// 2
// 1
// 2
// -1

#include<stdio.h>
#include<stdlib.h>

void oldWay(int n, long int m, long int *coffees){// Seems correct, but too slow
    int d = 1;
    int is_done = 0;

    // Iteate Days
    for(int d = 1; d < n; d++){
        int isCoffeeNotWork = 0;
        int maxRound = n / d;
        long int accumCode = 0;

        // Iterate Rounds & offsets For specific day
        for(int r = 0; r < maxRound; r++){
            for(int offset = 0; offset < d; offset++){
                long int workOfCoffee = coffees[r * d + offset] - r;

                if(workOfCoffee <= 0){
                    isCoffeeNotWork = 1;
                    break;
                }

                accumCode += workOfCoffee;

                if(accumCode >= m){
                    printf("%d\n", d);
                    is_done = 1;
                    break;
                }
            }

            if(is_done || isCoffeeNotWork){break;}
        }

        if(is_done){break;}
    }
}

int binSearch(long int *seq, long int target, int start, int end){
    // To find the largest number that smaller than target
    int mid = (start + end) / 2;
    int startI = start, endI = end;
    // printf("Binary Search Target: %ld within %d ~ %d\n", target, start, end);

    while(startI != endI){
        // printf("Binary Search: startI:[%d]%ld mid:[%d]%ld endI:[%d]%ld", startI, seq[startI], mid, seq[mid], endI, seq[endI]);
        if(target > seq[mid]){
            endI = mid;
            // printf(" T > M\n");
        }else{
            startI = mid + 1;
            // printf(" T <= M\n");
        }

        mid = (startI + endI) / 2;
    }

    return mid;
}

void newWay(int n, long int m, long int *coffees, long int *prefixSum, long int maxWorks){
    // Iterate Days
    for(int d = 1; d <= n; d++){
        int maxRound = n / d;
        long int cost = 0;
        long int accumCode = prefixSum[d];

        // printf("For %d Days\n", d);
        // printf("->Round 0: %ld\n", accumCode);

        for(int r = 1; r <= maxRound; r++){
            if(d * (r + 1) - 1 < n && coffees[d * (r + 1) - 1] == r){
                // the last round that can add
                cost += d * r;
                accumCode = prefixSum[d * (r + 1)] - cost;
                // printf("->Round %d: %ld\n", r, accumCode);
                break;
            }else if(d * (r + 1) - 1 < n && coffees[d * (r + 1) - 1] > r){
                // add next round
                cost += d * r;
                accumCode = prefixSum[d * (r + 1)] - cost;
                // printf("->Round %d: %ld\n", r, accumCode);
            }else if(d * r < n){
                
                int binSearchEnd = n - 1 < d * (r + 1) - 1? n - 1 : d * (r + 1) - 1;
                // printf("Search for %d ~ %d < %d\n", d * r, binSearchEnd, n - 1);
                int searchRes = binSearch(coffees, r, d * r, binSearchEnd);
                int range = searchRes - (d * r);
                cost += range * r;
                accumCode = prefixSum[searchRes] - cost;

                // printf("->Tail: [%d]%ld ~ [%d]%ld(%d) = %ld In Total\n", searchRes, coffees[searchRes], (d * r), coffees[(d * r)], range, accumCode);
                break;
            }
            

            if(accumCode >= m){break;}
        }

        if(accumCode >= m){
            printf("%d\n", d);
            break;
        }
    }
}

int main(){
    int t = 0;
    long int coffees[200005] = {0};
    long int prefixSum[200005] = {0};
    scanf("%d\n", &t);

    for(int i = 0; i < t; i++){
        int n = 0;
        long int m = 0;
        long int maxWorks = 0;
        scanf("%d %ld\n", &n, &m);

        for(int j = 0; j < n; j++){
            scanf("%ld", &(coffees[j]));
            maxWorks += coffees[j];
            // Note: coffee[k] = prefixSum[k + 1] - prefixSum[k]
            prefixSum[j + 1] = maxWorks;

        }

        if(maxWorks < m){
            printf("-1\n");

        }else if(maxWorks == m){
            printf("%d\n", n);
        }else{
            // printf("n:%d m:%ld\n", n, m);
            newWay(n, m, coffees, prefixSum, maxWorks);
            // printf("OldWay: ");
            // oldWay(n, m, coffees);
            // printf("===========================\n");
        }
            
    }

        

    return 0;
}