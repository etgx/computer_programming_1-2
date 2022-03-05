// NTHUOJ 12690 - Skate Shoes Sliding   
// Status  |  Limits 
// Description
// In the year of 2014, a well-known song has born...... and the name is "My Skate Shoes"(我的滑板鞋). 

// The song is known for its brainwashing style. The singer, Joseeh Pummanlon(約瑟翰 ‧ 龐麥郎), just slides left, then slide right... then slide everywhere with his skate shoes, like the step of devil, like the step of devil.

// Now Pummanlon is at the position 0. He has a sequence of commands which tells him to slide left or to slide right. 'L' is to slide left, 'R' is to slide right.

// For example, "LRLR" means he will slide to position -1, then 0, then -1, and stop at position 0.

// However, Pummanlon wants to free his sliding style at today's show. He still receives the sliding commands, but he might not perform some of the commands.

// For example, if Pummanlon receives the commands "LRLR", then here are some possible outcomes:

// "LRLR": Pummanlon moves to the left, to the right, then to the left again and end up at position -1.
// "LRLR": Pummanlon moves to the left, to the right, then to the left and to the right again and end up at position 0.
// "LRLR": Pummanlon doesn't move, he stands at position 0 like a blockhead instead of devil.
// "LRLR": Pummanlon moves to the left, to the right, then to the right again and end up at position 1.
// Pummanlon doesn't know which command will be performed since he will not know the mood while he's performing.Thus, he wants to know how many different positions may Pummanlon stops at.

// Input
// The first line contains an integer N, indicates the number of commands.

// The second line cocntains a string, contains exactly N commands of 'L' and 'R'.

// 1 <= N <= 105

// Output
// Print one integer — the number of different positions Pummanlon may end up at.

// Remember to print a '\n' at the end of the integer.

// Take sample as example, Pummanlon may end up anywhere between -2 and 2:

// LL -> -2
// LLR -> -1
// LR -> 0
// R -> 1
// RR -> 2
// Sample Input  
// 4
// LRLR
// Sample Output  
// 5

#include<stdio.h>

int main(){
	int n = 0;
	char str[10000];
	scanf("%d", &n);
	for(int i=0; i<n; i++){
		scanf("%c", &(str[0]));
	}
	printf("%d\n", n + 1);
	
	return 0;
}