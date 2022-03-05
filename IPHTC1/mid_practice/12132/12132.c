// // NTHUOJ 12132 - too many watermelons   
// Description
// Ovuvuevuevue Enyetuenwuevue Ugbemugbem Osas wants to eat watermelon. But the watermelons are stored in a cylindrical(圓柱狀) box.
// He has n watermelons and each one has a specific index denote as ai.
// Osas wants to eat a watermelon indexed ai.
// But if the watermelon indexed ai is not on the top,
// he needs to eat all watermelon above the watermelon indexed ai.
// Osas also has a list which is the order of watermelons he wants to eat which denoted as bi.
// The length of the list is also n and all bi are distinct.
// Please help him calculate that each time he wants to eat a watermelon, how many watermelons he needs to eat at same time?
// For example ：
// if the index of watermelon from top to bottom is: 5, 3, 2, 1, 4. And the list Osas has is: 2, 3, 4, 5, 1.
// First time Osas will eat 3 watermelons(5,3,2).
// Second time because the watermelons that indexed 3 is already been eaten, Osas eat 0 watermelon . So on and so forth.
// In this example, you need to output: 3 0 2 0 0.

// Input
// input contains three lines.
// First line contains n the number of watermelons.( 1 <= n <= 2*105 )
// Second line contains n integer a1 ~ an which denote as the index of watermelons from top to bottom .( 1 <= ai <= n )
// Third line contains n integer b1 ~ bn which denote as the order of watermelons  that Osas' wants to eat.( 1 <= bi <= n )

// Output
// output contains one line.
// output n integer means the number of watermelons that each time Osas eat. Separate each number by a blank but don't print the blank after the last number.
// remember to print \n at the end of output.

// Sample Input  
// 5
// 5 3 2 1 4
// 2 3 4 5 1

// Sample Output  
// 3 0 2 0 0


#include<stdio.h>

int main(){
	int n = 0;
	int w[200000] = {0};
	// int eaten_value = 0;

	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		int k = 0;
		scanf("%d", &k);
		w[k] = i;
		// if(i == 0){
		// 	eaten_value = k;
		// }
	}


	// int b[200000] = {0};
	int b = 0;
	int eaten_idx = -1;
	
	for(int i = 0; i < n; i++){
		scanf("%d", &b);

		int current_value = b;
		int eating_target  = w[current_value];
		int eating = eating_target - eaten_idx;

		// printf("[%d]: %d from [%d]: %d | %d\n", eating_target, current_value, eaten_idx, eaten_value, eating);

		if(eating > 0 ){	
			eaten_idx = eating_target;
			// eaten_value = current_value;
			printf("%d", eating);
		}else{
			printf("0");
		}

		if(i < n - 1){
			printf(" ");
		}
	}

	printf("\n");


	return 0;
}
