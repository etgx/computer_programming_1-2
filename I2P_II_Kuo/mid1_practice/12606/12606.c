// I2P - Kuo Week0 Problem 5 | NTHUOJ 12606 - Happy New Year
// Description
// Chinese New Year is coming.
// Bob decides to say “Happy New Year” to his friends.
// Bob and his friends reside on the same street.
// We can view the street as a straight line, and the position of their houses as points on the straight line.
// Bob is at his home at begining.
// He wants to visit each of his friend at least once, and then go back to his home.
// Because he is too lazy to move, can you help him to find out the minimun distance he should move?

// Input

// One integer N on the first line, denoting the number of Bob’s friends.
// The second line contains N+1 distinct number x_0,x_1,x_2,...,x_n
// x_0 represents the position of Bob’s house.
// x_1, x_2,...,x_n represents the position of Bob’s friends.
// It’s guaranteed that:
// 1 ≤ N ≤ 2∗105
// 0 ≤ xi ≤ 109

// Output

// Print the minimun distance he should move in one line.
// Remember ‘\n’ on the end of line.

// Sample Input  

// 5
// 2 0 1 3 5 6

// Sample Output  

// 12

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int N = 0;
    // The initial min should be the maximum of the variable.
    long long min = 1e9, max = 0;
    scanf("%d\n", &N);

    for(int i = 0; i < N + 1; i++){
        long long dest = 0;
        scanf("%lld", &dest);
        // N may = 1, so need to update both min and max.
        if(dest > max){
            max = dest;
        }
        if(dest < min){
            min = dest;
        }
    }
    printf("%lld\n", 2 * (max - min));
    return 0;
}