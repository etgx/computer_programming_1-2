#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#define MAX_EXPR_LEN 33
#define SYMBOL_LEN 2

long long parse(){
    char expr[MAX_EXPR_LEN];
    scanf("%s", expr);

    const char plus[SYMBOL_LEN] = {'+', '\0'};
    const char minus[SYMBOL_LEN] = {'-', '\0'};
    const char prod[SYMBOL_LEN] = {'*', '\0'};
    const char div[SYMBOL_LEN] = {'/', '\0'};
    const char mod[SYMBOL_LEN] = {'%', '\0'};

    if(strcmp(expr, plus) == 0){
        long long lhs = parse();
        long long rhs = parse();
        return lhs + rhs;
    }else if(strcmp(expr, minus) == 0){
        long long lhs = parse();
        long long rhs = parse();
        return lhs - rhs;
    }else if(strcmp(expr, prod) == 0){
        long long lhs = parse();
        long long rhs = parse();
        return lhs * rhs;
    }else if(strcmp(expr, div) == 0){
        long long lhs = parse();
        long long rhs = parse();
        return lhs / rhs;
    }else if(strcmp(expr, mod) == 0){
        long long lhs = parse();
        long long rhs = parse();
        return lhs % rhs;
    }else{
        // Require to use 64-bits integer to prevent overflow.
        return atoll(expr);
    }
}

int main(){
    long long res = parse();
    printf("%lld\n", res);
    return 0;
}