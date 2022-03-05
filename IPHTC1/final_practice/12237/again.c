// Another AC version
#include <stdio.h>
#include <stdlib.h>

typedef union float2{
    float f;
    int raw;
}Float2;

void printBin(Float2 f){
    for(int i = 31; i >= 0; i--){
        printf("%d", (f.raw >> i) & 1);
    }
    printf("\n");
}

int main(){
    Float2 f;
    while(scanf("%f", &(f.f)) != EOF){
        printBin(f);
    }

    return 0;
}