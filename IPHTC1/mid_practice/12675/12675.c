// NTHUOJ 12675 - Get the number   
// Description
// You are fired!
// ~by anonymous sniper
// My boss fired me and I fired him in the head.
// Now I wander how can I get integer n by two composite number a,b.
// You have to help me!
// You will have a integer n.
// Your goal is to print two composite number a, b that a-b = n.
// Note that a,b needs to be none-zero positive number and 1 <= a, b <= 10^18.
// (This problem is special judge. You can answer any pair of numbers as long as this answer is qualified the rules above. )

// Input
// The input only contains one integer n( 1 <= n <= 10^8)
 
// Output
// Print only two integer a,b which separated by a blank.
// Remember to print \n at the end of output.

// Sample Input  
// 512

// Sample Output  
// 4608 4096

#include<stdio.h>

int is_composite(int in){
	int i = 2;
	int flag = 0;
	while(i * i <= in){
        // printf("A");
		if(in % i == 0){
			flag = 1;
			break;
		}
        i++;
	}
	return flag;
}

int main(){
	int n = 0;
	int a = 1;
	int b = 1;
    int is_answer = 0;

	scanf("%d", &n);
	for(a=4; a<2147483647; a++){
		if(is_composite(a) == 1){
            // printf("B");
			if(is_composite(a + n) == 1){
                // printf("C");
				b = a + n;
                printf("%d %d\n", b, a);
                is_answer = 1;
				break;
			}
		}
	}
    if(is_answer == 0){
        printf("%d %d\n", n * 3, n * 2);
    }
	return 0;
}