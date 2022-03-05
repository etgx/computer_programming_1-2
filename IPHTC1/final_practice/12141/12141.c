// NTHUOJ 12141 - Ugandan Knuckles's code   
// Description
// Ugandan Knuckles is trapped in a dungeon. He wants to find his queen. He finds a stele (碑) that there are n strings on it. You can move the strings in any order you want.
// The way to go out is that for each string, all strings placed before it are its substrings.
// For example:
// If the stele contains strings:
// "n"
// "ugandan"
// "ganda"
// "gan"
// You should arrange the strings into the order:
// "n"
// "gan"
// "ganda"
// "ugandan"
// Help Knuckles get out of the dungeon or he will spit on you.

// Input
// Input contains several lines.
// First line contains only one integer n (1<= n <= 1000)
// Following n lines, each line contains one string s ( 1<= length of s <= 1000 )
// The string s only contains lowercase English letters.

// Output
// If it's impossible to arrange the strings in the desired order, print "NO".
// If it's possible, print "YES" .
// And then print n lines each line contains one string in required order.
// Remember to print \n at the end of output.

// Sample Input  
// 5
// ugandan
// g
// uganda
// ganda
// gan

// Sample Output  
// YES
// g
// gan
// ganda
// uganda
// ugandan

// Reference: https://www.geeksforgeeks.org/substring-sort/

#include<stdio.h>
#include<stdlib.h>
#define StrSize 1005
#define StrNum 1005

int is_sub = 1;

int compare(const char *a, const char *b){
    int sizeA = 0, sizeB = 0;
    for(sizeA = 1; a[sizeA] != '\0'; sizeA++){}
    for(sizeB = 1; b[sizeB] != '\0'; sizeB++){}

    // res = 
    //     = 1 a include in b
    //     = 0 b include in a
    //     = -1 None Included
    // int res = 1;
    if(sizeA < sizeB){
        // Is a include in b?
        for(int i = 0; i <= sizeB - sizeA; i++){
            int flag = 1;

            for(int j = 0; j < sizeA; j++){
                if(a[j] != b[i + j]){
                    flag = 0;
                    break;
                }
            }
            if(flag){return 0;}
        }

        // printf("Is a include in b?\n");
        is_sub = 0;
        return -1;
    }else if(sizeA > sizeB){
        // printf("a: %s - %d\n", a, sizeA);
        // printf("B: %s - %d\n", b, sizeB);
        // Is b include in a?
        for(int i = 0; i <= sizeA - sizeB; i++){
            int flag = 1;

            for(int j = 0; j < sizeB; j++){
                // printf("i: %d, j: %d\n", i, j);
                if(b[j] != a[i + j]){
                    flag = 0;
                    break;
                }
                
            }
            if(flag){
                return 1;
            }
        }
        // printf("Is b include in a?\n");
        is_sub = 0;
        return -1;
    }else{
        // Is a equals to b?
        for(int i = 0; i < sizeA; i++){
            if(a[i] != b[i]){
                // printf("Is a equals to b?\n");
                is_sub = 0;
                return -1;
            }
        }
        return 1;
    }
}

int main(){
    int n = 0;
    char strings[StrNum][StrSize] = {0};

    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%s", strings[i]);
    }
    qsort(strings, n, StrSize * sizeof(char), (int (*)(const void *, const void *))compare);

    if(is_sub){
        printf("YES\n");
        for(int i = 0; i < n; i++){
            printf("%s\n", strings[i]);
        }
    }else{
        printf("NO\n");
    }
    return 0;
}