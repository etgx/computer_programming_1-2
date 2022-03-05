// IPHTC2 Week9 Problem 2 | NTHUOJ 12522 - Hulk's Trouble
// Description
// Years after Thanos eliminated half lives of the universe and destroyed all the stones, Avengers finally gather 6 infinity stone and equip them onto the glove. The one who snaps the finger must be the strongest avenger. Everybody knows, the avenger is ThorHulk!
// Hulk's duty is to revive all lives that was eliminated by Thanos. At the moment he snaps, his mind just enters into the deepest layer of the universe. Now, he can see the whole universe.
// However, the amount of information is too large to find those eliminated people. Hulk asks you for help. Please help him to find out the information he needs.

// Hulk Thinking About This Problem
// If you click on this picture, something might happen...
// There will be an integer sequence with length , which contains all the information that the universe has.
// Hulk will give you several integers. He wants to know how many times the number appears in sequence .
// For example, the sequence a=\{3,2,3,6,6,5\}, then there are two 33, two 66, one 22, and one 55.

// Input
// The first line contains an integer n.
// The next line contains nn integers, which is the sequence aa.
// The next line contains an integer q, indicates the amount of numbers Hulk will ask you.
// Then q lines below, each line contains an integer xx.

// 1\le n\le 10^5, 1\le a_i\le 10^9\ \forall i\in[1,n], 1\le x\le 10^9, 1\le q\le10^51≤n≤10 
// 5
//  ,1≤a 
// i
// ​
//  ≤10 
// 9
//   ∀i∈[1,n],1≤x≤10 
// 9
//  ,1≤q≤10 
// 5
//  .

// Output
// For each query, output the number of times that xx appears in sequence aa.

// Sample Input 1 
// 10
// 8 3 6 1 7 7 3 7 10 7
// 5
// 3
// 7
// 999
// 1
// 5

// Sample Output 1
// 2
// 4
// 0
// 1
// 0

// Hint

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void show_arr(long long *a, long long n){
    for(long long i = 0; i < n; i++){
        printf("%lld ", a[i]);
    }
    printf("\n");
}

void swap(long long *a, long long *b){
    long long temp = *a;
    *a = *b;
    *b = temp;
}

void quick_sort(long long *a, long long l, long long r){
    if(l > r) return;
    long long pivot = a[r], i = 0, j = 0;
    for(i = l, j = l; j < r; j++){
        if(a[j] < pivot){
            swap(&(a[i]), &(a[j]));
            i++;
        }
    }
    swap(&(a[i]), &(a[r]));

    quick_sort(a, l, i - 1);
    quick_sort(a, i + 1, r);
}

void sorting(long long *a, long long n){
    quick_sort(a, 0, n - 1);
}

long long lbs(long long *a, long long x, long long l, long long r){
    if(l > r) return -1;
    if(r - l <= 1){
        if(a[l] == x) return l;
        if(a[r] == x) return r;
        return -1;
    }

    long long m = (l + r) / 2;
    // printf("LBS X: %lld - [%lld]: %lld | [%lld]: %lld | [%lld]: %lld\n", x, l, a[l], m, a[m], r, a[r]);
    if(a[m] > x){
        return lbs(a, x, l, m-1);  
    }else if(a[m] < x){
        return lbs(a, x, m+1, r);
    }else{
        return lbs(a, x, l, m);  
    }
}

long long lb(long long *a, long long x, long long n){
    return lbs(a, x, 0, n - 1);
}

long long ubs(long long *a, long long x, long long l, long long r){
    if(l > r) return -1;
    if(r - l <= 1){
        if(a[r] == x) return r;
        if(a[l] == x) return l;
        return -1;
    }

    long long m = (l + r) / 2;
    // printf("UBS X: %lld - [%lld]: %lld | [%lld]: %lld | [%lld]: %lld\n", x, l, a[l], m, a[m], r, a[r]);
    if(a[m] < x){
        return ubs(a, x, m+1, r);
    }else if(a[m] > x){
        return ubs(a, x, l, m-1);
    }else{
        return ubs(a, x, m, r);
    }
}

long long ub(long long *a, long long x, long long n){
    return ubs(a, x, 0, n - 1);
}

int main(){
    long long n = 0, q = 0, *a = NULL;
    scanf("%lld\n", &n);

    a = (long long*)malloc(sizeof(long long) * n);
    memset(a, 0, sizeof(long long) * n);

    for(long long i = 0; i < n; i++){
        scanf("%lld\n", &(a[i]));
    }
    sorting(a, n);
    // show_arr(a, n);
    scanf("%lld\n", &q);

    for(long long i = 0; i < q; i++){
        long long x = 0;
        scanf("%lld\n", &x);
        long long l = lb(a, x, n), u = ub(a, x, n);
        if(l == -1 && u == -1) printf("0\n");
        else printf("%lld\n", u - l + 1);
        // printf("%lld - LB: %lld | UB: %lld\n", x, l, u);
        // printf("%lld - LB: %lld\n", x, lb(a, x, n));
    }

    return 0;
}