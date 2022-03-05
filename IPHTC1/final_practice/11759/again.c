#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FactNameSize 30

typedef struct fact{
    char name[FactNameSize];
    int a;
    int b;
    int aMinusB;
}Fact;

typedef struct profit{
    int total;
    int a;
    int b;
}Profit;

void showFacts(Fact *facts, const int n){
    for(int i = 0; i < n; i++){
        printf("Name: %s a: %d b: %d, | %d\n", facts[i].name, facts[i].a, facts[i].b, facts[i].aMinusB);
    }
}

int cmp(const Fact *a, const Fact *b){return b->aMinusB > a->aMinusB;}
int aCmp(const Fact *a, const Fact *b){return b->a > a->a;}
int bCmp(const Fact *a, const Fact *b){return b->b > a->b;}
int lexicalCmp(const Fact *a, const Fact *b){return strcmp(a->name, b->name) >= 0;}

// the factories that has index order < sep make profit with Car A, otherwise with Car B
Profit seperate(Fact *facts, const int n, Fact *xSeq, const int x, Fact *ySeq, const int y, const int sep){
    // int profitSum = 0, profitASum = 0, profitBSum = 0;
    Profit p = {0, 0, 0};
    // printf("P total: %d, a: %d, b: %d\n", p.total, p.a, p.b);
    for(int i = 0; i < sep; i++){xSeq[i] = facts[i];}
    for(int i = sep; i < n; i++){ySeq[i - sep] = facts[i];}

    qsort(xSeq, sep, sizeof(Fact), (int (*)(const void *, const void *))aCmp);
    qsort(ySeq, n - sep, sizeof(Fact), (int (*)(const void *, const void *))bCmp);

    for(int i = 0; i < x; i++){p.total += xSeq[i].a; p.a += xSeq[i].a;}
    for(int i = 0; i < y; i++){p.total += ySeq[i].b; p.b += ySeq[i].b;}
    // printf("WithSep: %d\n", sep);
    // printf("Seperated xSeq:\n");
    // showFacts(xSeq, x);
    // printf("Seperated ySeq:\n");
    // showFacts(ySeq, y);
    // printf("P total: %d, a: %d, b: %d\n", p.total, p.a, p.b);

    return p;
}

int main(){
    int n = 0, x = 0, y = 0, maxProfitSep = 0;
    Profit maxProfit = {0, 0, 0};
    // printf("maxProfit total: %d, a: %d, b: %d\n", maxProfit.total, maxProfit.a, maxProfit.b);
    scanf("%d %d %d\n", &n, &x, &y);
    Fact *facts = (Fact *)malloc(sizeof(Fact) * n);
    Fact *xSeq = (Fact *)malloc(sizeof(Fact) * n);
    Fact *ySeq = (Fact *)malloc(sizeof(Fact) * n);
    memset(facts, sizeof(Fact) * n, 0);
    memset(xSeq, sizeof(Fact) * n, 0);
    memset(ySeq, sizeof(Fact) * n, 0);

    for(int i = 0; i < n; i++){
        scanf("%s %d %d", facts[i].name, &(facts[i].a), &(facts[i].b));
        facts[i].aMinusB = facts[i].a - facts[i].b;
    }

    // Sort with aMinusB in decreasing order
    qsort(facts, n, sizeof(Fact), (int (*)(const void *, const void *))cmp);
    // showFacts(facts, n);
    // Problem: the boudary should be i <= n - y
    for(int i = x; i <= n - y; i++){
        Profit p = seperate(facts, n, xSeq, x, ySeq, y, i);
        if(p.total > maxProfit.total){
            maxProfit = p;
            maxProfitSep = i;
        }else if(p.a > maxProfit.a && p.total == maxProfit.total){
            maxProfit = p;
            maxProfitSep = i;
        }
        memset(xSeq, sizeof(Fact) * n, 0);
        memset(ySeq, sizeof(Fact) * n, 0);
    }

    seperate(facts, n, xSeq, x, ySeq, y, maxProfitSep);
    // Sort in lexical order
    qsort(xSeq, x, sizeof(Fact), (int (*)(const void *, const void *))lexicalCmp);

    for(int i = 0; i < x; i++){
        printf("%s\n", xSeq[i].name);
    }

    return 0;
}