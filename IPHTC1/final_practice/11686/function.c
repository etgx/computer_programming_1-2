// NTHUOJ 11686 - more simple exercise of pointer on array   
// Description
// In this exercise, you should exchange the content of two given one dimensional integer arrays with same length.
// We have written the code about reading the size and the content of arrays, and we want to pass them to a function for getting the final answer. What you need is helping us to complete the function. 
// What input into the function is two pointers representing the two arrays and the length of array, and the function has to exchange the content of the two arrays.
// For more specific, you only need to implement the following function:

// #include <stdio.h>
// #include "function.h"
// void array_exchanger(int* array_a, int* array_b, int length) {
//      // your code
// }
// The .c and .h file below might be helpful if you want to know how the function and the whole program works.

// Input
// The input may have 3 lines of input.
// The very first line is a number, representing the length of 2 arrays.
// The second and the third lines are several integers, representing the content of 2 arrays.

// Output
// The content in two arrays after exchanged.

// Sample Input  
// 3
// 1 2 3
// 4 5 6

// Sample Output  
// 4 5 6
// 1 2 3

// Partial Judge Code
// 11686.c

// Partial Judge Header
// 11686.h

// 2020/06/18 SYC

#include<stdio.h>
#include<stdlib.h>

void array_exchanger(int* array_a, int* array_b, int length){
    for(int i = 0; i < length; i++){
        int temp = array_a[i];
        array_a[i] = array_b[i];
        array_b[i] = temp;
    }
}