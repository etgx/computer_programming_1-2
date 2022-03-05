// NTHUOJ 12661 - The night's watch   
// Status  |  Limits 
// Description
// And now my watch begins.

// ~by a binge watching man

// Your a lord commander of the night's watch. You wants to choose some men to be your soldiers while other lords also needs to choose some men. There're n lords and n soldiers and there're k lords who are your friends therefore they will follow your order. And each soldier's ability is represented by a number ai. Since the lords stand in a line and wait for their turn to choose, you are standing in the m-th position.

// Given a sequence of numbers a1 ~ an. n people standing in a line to choose one number from the sequence.

// Each person can only choose a number from the head or the tail of the sequence.

// Once a number is chosen, it will be remove from the sequence.

// You are at m-th position of the line.

// You want to get the number as big as possible.

// You can order at most k people to choose what you want them to choose(head or tail).

// But you can not change your order during the choosing process.

// And those who you don't give an order will choose arbitrarily.

// Your task is to find out what is the greatest integer x such that, no matter what are the choices of the others you didn't choose to control, the element you will take from the array will be at least x?

 

// Example:

// If there are n=6 numbers 2, 9, 2, 3, 8, 5.

// You are at m=4 position.

// And you can control k=2 people.

// If the first person ordered by you choose tail 5.

// The second person ordered by you choose head 2.

// Then the third person can choose either 9 or 8.

// No matter what the third person choose, you can get at least 8.

// Therefore the answer is 8.


// Input
// The first line of input will be t(1 <= t <= 10) means number of testcases.

// Each testcases contains two lines.

// First line contains three integers n( 1 <= n <= 5000), m(1 <= m <= n), k(0 <= k <= n-1).

// Second line contains n integers ai(1 <= ai <= 10^9).

 
// Output
// For each testcases, print a single integer x.

// Each output is ended by \n.

// Sample Input  
// 4
// 6 4 2
// 2 9 2 3 8 5
// 4 4 1
// 2 13 60 4
// 4 1 3
// 1 2 2 1
// 2 2 0
// 1 2

// Sample Output  
// 8
// 4
// 1
// 1


#include<stdlib.h>
#include<stdio.h>

int main(){
    int t = 0;
    scanf("%d", &t);
    
    for(int i = 0; i < t; i++){
        int n = 0, m = 0, k = 0;
        long int seq[5003] = {0};
        scanf("%d %d %d", &n, &m, &k);
        // printf("%d %d %d\n", n, m, k);

        for(int j = 0; j < n; j++){
            scanf("%ld", &(seq[j]));
        }

        int ordered = k <= m - 1? k : m - 1;
        int unordered = m - k - 1 <= 0? 0 : m - k - 1;
        // printf("Ordered: %d, Unordered: %d\n", ordered, unordered);

        long max_ordered = 0;
        for(int i = 0; i <= ordered; i++){
            int start_o = ordered - i;
            int end_o = n - 1 - i;

            // printf("start_o: %d end: %d\n", start_o, end_o);
            
            long int min_unordered = 1000000003;
            for(int j = 0; j <= unordered; j++){
                int start_u = start_o + unordered - j;
                int end_u = end_o - j;
                // printf("Unordered start: [%d]-%ld end: [%d]-%ld\n", start_u, seq[start_u], end_u, seq[end_u]);

                long int local_max = seq[start_u] > seq[end_u]? seq[start_u] : seq[end_u];
                if(min_unordered > local_max){min_unordered = local_max;}
            }

            if(min_unordered > max_ordered){max_ordered = min_unordered;}
        }

        printf("%ld\n", max_ordered);
    }

    return 0;
}