// NTHUOJ 11760 - C - Stable Sort   
// Description
// Writer: jjjjj19980806       Description: pclightyear        Difficulty: ★★☆☆☆
// Given a list of students and their score, you have to sort their score in decreasing order.
// If there are many students with the same score, you need to maintain their relative order in the original list.
// That is, if whenever there are two students A and B with the same score and with A appearing before B in the original list, A will appear before B in the sorted list.
// Reference: https://en.wikipedia.org/wiki/Category:Stable_sorts​

// Input
// The first line contains one integer n, representing the number of students.
// The next n lines contain a string and an integer si and ai, representing the name of each student and his/her score.
// It is guaranteed that :
// n ≤ 105
// 1 ≤ | si | ≤ 20
// 0 ≤ aij ≤ 100
 

// Output
// After sorting, please output the list of students' names, each name with a line.

// Sample Input  
// 4
// Roy 99
// Feng 99
// hsuan 100
// Johnson 87

// Sample Output  
// hsuan
// Roy
// Feng
// Johnson

#include<stdio.h>
#include<stdlib.h>

typedef struct grade{
    int idx;
    char name[25];
    int score;
}Grade;

int cmp(const Grade *a, const Grade *b){
    if(a->score < b->score){
        return 1;
    }else if(a->score > b->score){
        return 0;
    }else{
        if(a->idx >= b->idx){
            return 1;
        }else{
            return 0;
        }
    }
}

int cmpMerge(const Grade *a, const Grade *b){
    if(a->score < b->score){
        return 1;
    }else{
        return 0;
    }
}

void swap(Grade *a, Grade *b){
    Grade temp = (*a);
    (*a) = (*b);
    (*b) = temp;
}

void mergeSort(Grade *array, int start, int end){
    const int Inf = 2147483647;
    int mid = (start + end) / 2;
    int tempArrASize = (mid - start + 1), tempArrBSize = (end - mid);
    mergeSort(array, start, mid);
    mergeSort(array, mid + 1, end);

    int *tempArrA = (int *)malloc(sizeof(int) * (tempArrASize + 1));
    int *tempArrB = (int *)malloc(sizeof(int) * (tempArrBSize + 1));

    for(int i = 0; i < tempArrBSize; i++){
        tempArrA[i] = array[start + i];
        tempArrB[i] = array[mid + i + 1];
    }
    tempArrA[tempArrASize - 1] = array[start + tempArrASize - 1];
    tempArrA[tempArrASize] = Inf;
    tempArrB[tempArrBSize] = Inf;
}

int main(){
    int n = 0;
    Grade list[100005];
    scanf("%d\n", &n);

    for(int i = 0; i < n; i++){
        scanf("%s %d\n", (list[i].name), &(list[i].score));
        list[i].idx = i;
    }

    qsort(list, n, sizeof(Grade), (int (*)(const void *, const void *))cmp);

    for(int i = 0; i < n; i++){
        printf("%s\n", list[i].name);
    }

    return 0;
}