// NTHUOJ 11592 - Change the Cap   
// Description
// Johnson, a pro table tennis player, is a member of school team in NTHU. The coach trains the whole team three times a week. After training, Johnson needs to drink a lot of sports drinks named "Fin & Bubblegum" (also known as "F&B").
// One day, the company decides to hold a long-term promotion. After you collect three caps from the bottle, you can return them back to the company and get a new bottle of "F&B".
// Johnson notices that he needs to drink N bottle of "F&B" every week. He would like to know the minimum number of "F&B" he needs to buy every week.
// If you can solve this problem, maybe Johnson will teach you how to play table tennis.
// For this problem, you don't need to calculate the remaining caps from last week.
// Attention : Johnson found out that some programs may give him wrong answer in some other cases, so he decided to add more testcases to ensure the correctness of your program. (rejudge in 10/5 18:20)

// Input
// There is only one integer for each testcase.
// 1 <= N <= 104

// Output
// Please output the minimum number of "F&B" Johnson needs to buy every week.
// Remember to print '\n' after your answer.

// Sample Input  
// 13

// Sample Output  
// 9

// 2020/05/01 SYC

#include<stdio.h>
#include<stdlib.h>

int countFBs(int input){
    int remain = input;
    int getFBs = input;
    while(remain > 2){
        getFBs += remain / 3;
        remain = (remain / 3) + (remain % 3);
    }

    return getFBs;
}

int main(){
    int target = 0;
    scanf("%d", &target);

    for(int i = target; i >= 0; i--){
        // printf("%d: %d\n", i, countFBs(i));
        if(countFBs(i) < target){
            printf("%d\n", i + 1);
            break;
        }
    }

    return 0;
}