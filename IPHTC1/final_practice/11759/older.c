// 首先要先證明最佳解存在一個Seperater，選中製造A的工廠和選中製造B的工廠分別在Seperater之上和之下
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NameLen 25

typedef struct Fact{
    char name[NameLen];
    int a;
    int b;
    int aMinusB;
}Fact;

int aMinusBCmp(const Fact *a, const Fact *b){return b->aMinusB > a->aMinusB;}
// Sort net profit of Car A in decreasing order
int aCmp(const Fact *a, const Fact *b){return b->a > a->a;}
// Sort net profit of Car B in decreasing order
int bCmp(const Fact *a, const Fact *b){return b->b > a->b;}

int lexicalCmp(const Fact *a, const Fact *b){
    if(strcmp(a->name, b->name) >= 0){return 1;}
    return 0;
}

int seperate(const int separator, int *maxSum, int *maxASum, Fact *facts, const int n, Fact *xSeq, const int x, Fact *ySeq, const int y){
    // Seperator: the begining index of y section
    // Check Boundery, note: boundary has been checked in for loop
    //if(separator < x || separator > n - y){return 0;}

    (*maxSum) = (*maxASum) = 0; 
    for(int i = 0; i < separator; i++){xSeq[i] = facts[i];}
    for(int i = separator; i < n; i++){ySeq[i - separator] = facts[i];}
    // Sort with the net profit of Car A in decresing order
    qsort(xSeq, separator, sizeof(Fact), (int (*)(const void *, const void *))aCmp);
    // Sort with the net profit of Car B in decresing order
    qsort(ySeq, (n - separator), sizeof(Fact), (int (*)(const void *, const void *))bCmp);
    // Calculate Sum of highest x net profit of car A
    for(int i = 0; i < x; i++){(*maxSum) += xSeq[i].a; (*maxASum) += xSeq[i].a;}
    // Calculate Sum of highest y net profit of car B
    for(int i = 0; i < y; i++){(*maxSum) += ySeq[i].b;}

    return *maxSum;
}

int main(){
    int n = 0, x = 0, y = 0, maxSep = 0, maxSum = 0, maxASum = 0;
    scanf("%d %d %d\n", &n, &x, &y);
    // printf("N: %d X: %d Y: %d\n", n, x, y);
    Fact *facts = (Fact *)malloc(sizeof(Fact) * n);
    Fact *xSeq = (Fact *)malloc(sizeof(Fact) * n);
    Fact *ySeq = (Fact *)malloc(sizeof(Fact) * n);
    memset((void *)facts, sizeof(Fact) * n, 0);
    memset((void *)xSeq, sizeof(Fact) * n, 0);
    memset((void *)ySeq, sizeof(Fact) * n, 0);

    for(int i = 0; i < n; i++){
        scanf("%s %d %d\n", facts[i].name, &(facts[i].a), &(facts[i].b));
        facts[i].aMinusB = facts[i].a - facts[i].b;
    }

    // Sort with the value a - b in decreasing order
    qsort(facts, n, sizeof(Fact), (int (*)(const void *, const void *))aMinusBCmp);
    // Brutal search and compare every kind of seperate
    for(int i = x; i <= n - y; i++){
        int temp = 0, tempA = 0;
        seperate(i, &temp, &tempA, facts, n, xSeq, x, ySeq, y);
        if(temp > maxSum){
            maxSep = i;
            maxSum = temp;
            maxASum = tempA;
        }else if(temp == maxSum && tempA > maxASum){
            // if sum is the same and sum of Car A is larger than current one, swap
            maxSep = i;
            maxASum = tempA;
        }
        memset((void *)xSeq, sizeof(Fact) * n, 0);
        memset((void *)ySeq, sizeof(Fact) * n, 0);
    }
    seperate(maxSep, &maxSum, &maxASum, facts, n, xSeq, x, ySeq, y);
    
    // Sort in lexical order
    qsort(xSeq, x, sizeof(Fact), (int (*)(const void *, const void *))lexicalCmp);
    for(int i = 0; i < x; i++){
        printf("%s\n", xSeq[i].name);
    }


    return 0;
}