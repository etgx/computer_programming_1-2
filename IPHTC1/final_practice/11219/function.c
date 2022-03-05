// NTHUOJ 11219 - Get your array and then sort it!   
// Description
// [Partial Judge]
// Given a sequence of integers, sort it in increasing order by implementing the function my_sort().
// The main code and the header code are provided as below.
// There are two functions defined in the header file:
// int* readInput();
// void my_sort(int* B);
// Function int* readInput() is given. It will read the input numbers, save it into an array, say Seq, and finally return the address of the array.
// The first element of array Seq is the number of integers to be sorted. The following elements are the integers.
// Function void my_sort(int* B) is the one leaved for you to implement. It take in a single argument B of type int*, whose value is the address of the address of the array Seq.
// * Note that the address of the array Seq is returned by the function int* readInput().
// * Also, you should be care of the actual type of the variable you want to access to. Do not be confused with the function definition.
// * When submitting your code, remember to set Language option to "C: -O2 -lm -std=c99"

// Input
// A line of N integers seperated by a space in between.
// 100 <= N <= 1000.
// The value of integer falls in the range of [-1000, 1000].
// Input is handled by the provided function int* readInput(). You don't need to worry about it.

// Output
// A line of sorted integers seperated by a space in between. No extra space after the last integer. An newline character ('\n') is appended at the end.
// You don't need to worry about it. It is handled in the provided main function.

// Sample Input  
// 141 -542 -669 -513 160 717 473 344 -51 -548 703 -869 270 -181 957 -509 -6 937 -175 434 -625 -403 901 -847 -708 -624 413 -293 709 886 445 716 -236 533 869 903 655 -714 27 890 -311 800 307 -682 665 -338 134 708 -761 -135 535 631 -354 -259 -973 -147 -281 737 516 -222 -690 34 -821 842 -712 -909 36 -62 255 -363 433 794 883 -274 -642 343 -1 86 -619 547 620 -383 -928 945 -253 835 -36 373 925 -705 -64 -577 -386 318 535 528 -890 -919 -82 -467 -169 100 -363 644 -307 926 971 -695 658 -625 19 -269 -89 63 -733 827 -236 566 95 -496 975 284 157 -373 -656 -245 644 567 -971 -954 337 150 -67 714 960 429 92 -824 999 332 450 -719
// Sample Output  

// -973 -971 -954 -928 -919 -909 -890 -869 -847 -824 -821 -761 -733 -719 -714 -712 -708 -705 -695 -690 -682 -669 -656 -642 -625 -625 -624 -619 -577 -548 -542 -513 -509 -496 -467 -403 -386 -383 -373 -363 -363 -354 -338 -311 -307 -293 -281 -274 -269 -259 -253 -245 -236 -236 -222 -181 -175 -169 -147 -135 -89 -82 -67 -64 -62 -51 -36 -6 -1 19 27 34 36 63 86 92 95 100 134 150 157 160 255 270 284 307 318 332 337 343 344 373 413 429 433 434 445 450 473 516 528 533 535 535 547 566 567 620 631 644 644 655 658 665 703 708 709 714 716 717 737 794 800 827 835 842 869 883 886 890 901 903 925 926 937 945 957 960 971 975 999

// Partial Judge Code
// 11219.c

// Partial Judge Header
// 11219.h

#include<stdio.h>
#include<stdlib.h>
#include"function.h"

void mergeSort(int *seq, int start, int end){

}

int cmp(const int *a, const int *b){
    return (*b) < (*a);
}

void sort(int *seq){
    int n = seq[0];
    qsort(&(seq[1]), n, sizeof(int), (int (*)(const void *, const void *))cmp);
}

void my_sort(int* B){
    // mergeSort(B)
    
    int **k = (int **)B;
    sort(*k);
}