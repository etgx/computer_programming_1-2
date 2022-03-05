// NTHUOJ 11728 - Distance on 2D plane   
// Description
// TA knows that in Monday lecture, HT taught everyone the concept of structure.
// Moreover, the hackthon will be held on Saturday, and you students will use lots of APIs, containing many usages of structure.
// Therefore, TA wants to ensure that you have enough basic knowledge of structure through this problem. 
// In this problem, TA forces you to use structure to record imformation and use afterward.
// You will be given several points' locations on 2D plane(x, y), and you should compute the Euclidean distance of specific two points.
// (Hint: you can use sqrt() to calculate the square root)
// You should implement funcion.c below and submit it. (Due to Partial judge)

// #include <stdio.h>
// #include <math.h>
// #include "function.h"

// Point * ones_vec_1(int length)
// {
//    /// Please implement
//    /// 1. Malloc memory for point array
//    /// 2. Read values into point array
//    /// 3. Return the address of the first element in the array

// }

// float compute_distance(Point* a, int first_id, int second_id)
// {
//     float ans;
//     Point first_p, second_p;

//     /// Please implement
//     /// 1. Get two point from function argument
//     /// 2. Compute 2D distance and return ans

//     return ans;
// }

// You should see .c and .h file below to know how the function and the whole program works.

// Input
// Input may have several lines.
// The first line contains an integer M, indicating how many points' locations you should read.
// (Notice that the first point is indexed 0, and the second point is indexed 1, and so on...)
// And the next M lines , each line has two integers, indicating point's location x and y.
// The next line contains an integer N, indicating the number of the pairs of chosen two points.
// And the next N lines, each line contains two integers, which are two indices representing two specific points needed to be calculated for Euclidean distance.

// Output
// Ouput has N lines.
// Each line contains a floating number, indicating the Euclidan distance of two specific points.

// Sample Input  
// 3
// 0 0
// 3 4
// 6 8
// 2
// 0 1
// 0 2

// Sample Output  
// 5.000
// 10.000

// Partial Judge Code
// 11728.c

// Partial Judge Header
// 11728.h

// 2020/06/19 SYC

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "function.h"

// HINT: To compile the "math.h" library, add flag "-lm" that the command is: 
// gcc 11728.c function.c function.h -o 11728 -lm

// typedef struct {
//     int x;
//     int y;
// } Point;

Point * ones_vec_1(int length){
    Point *arr = (Point *)malloc(sizeof(Point) * length);
    for(int i = 0; i < length; i++){
        scanf("%d %d\n", &(arr[i].x), &(arr[i].y));
    }

    return arr;
}

float compute_distance(Point* a, int first_id, int second_id){
    return sqrt((double)((a[first_id].x - a[second_id].x) * (a[first_id].x - a[second_id].x) + (a[first_id].y - a[second_id].y) * (a[first_id].y - a[second_id].y)));
}