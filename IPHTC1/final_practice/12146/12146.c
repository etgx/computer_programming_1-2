// NTHUOJ 12146 - Too Many Things to Buy   
// Description
// Ovuvuevuevue Enyetuenwuevue Ugbemugbem Osas is a shopaholic.
// There are n different kinds of items in a store and Osas wants to buy every kinds of them.
// The i-th item cost ai dollars, but the price fluctuates greatly recently.
// Tomorrow the i-th item's price will be bi dollars. Osas has an special ability that he can know the price tomorrow.
// Because he's a shopaholic, he wants to buy every kinds of items in at most two days. Osas must buy at least k item at first day, or he will be crazy.
// Help Osas find out the minimum money he should pay to buy every kinds of item in the shop.

// Input
// Input contains third lines.
// First line contains two integer n ( 1 <= n <= 105 ) and k ( 0 <= k <= n ).
// Second line contains n integer a1 ~ an ( 1 <= ai <= 105).
// Third line contains n integer b1 ~ bn ( 1 <= bi <= 105 ).

// Output
// Output only contains one integer -- the minimum price Osas needs to pay.
// remember to print \n at the end of output.

// Sample Input  
// 5 2
// 6 8 9 5 4
// 5 1 10 3 2

// Sample Output  
// 21

#include<stdio.h>
#include<stdlib.h>

typedef struct item{
    int idx;
    int priceToday;
    int priceTomorrow;
    int lose; // Price today - Price tomorrow
}Item;

int cmp(const Item *a, const Item *b){
    return (a->lose > b->lose);
}

int main(){
    int n = 0, k = 0, todayCheaperN = 0, buyToday = 0;
    long long int cost = 0;
    scanf("%d %d\n", &n, &k);
    Item *items = (Item *)malloc(sizeof(Item) * n);

    for(int i = 0; i < n; i++){
        scanf("%d", &(items[i].priceToday));
        items[i].idx = i;
    }

    for(int i = 0; i < n; i++){
        scanf("%d", &(items[i].priceTomorrow));
        items[i].lose = items[i].priceToday - items[i].priceTomorrow;
    }

    qsort(items, n, sizeof(Item), (int (*)(const void *, const void*))cmp);

    // for(int i = 0; i < n; i++){
    //     printf("%d ", items[i].lose);
    // }

    for(todayCheaperN = 0; todayCheaperN < n; todayCheaperN++){
        if(items[todayCheaperN].lose >= 0){break;}
    }

    if(todayCheaperN < k){
        buyToday = k;
    }else{
        buyToday = todayCheaperN;
    }

    for(int i = 0; i < n; i++){
        if(i < buyToday){cost += (long long int)items[i].priceToday;}
        else{cost += (long long int)items[i].priceTomorrow;}
    }

    printf("%lld\n", cost);

    return 0;
}