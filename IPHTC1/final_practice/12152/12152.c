// NTHUOJ 12152 - youbike racer   
// Description
// "Wow! Look at that youbike! It's so fasion...."
// "Hey! Look! Is he.... is he the famous "The king on Akina Mount"(秋名山車神)...? The one who dominates all youbikers on Akina Mount? No way!"
// -----------------------------------------------------------
// The world's largest youbike racing contest is holding in NTHU. All the best youbike racers come to this place, including "The king on Akina Mount" !!! But now, he has several problems to solve......
// Due to youbikes cannot afford really high speed for too long since the components might break and racers would be in danger, so the race commitee sets up several checkpoints along the contest track. Every racer can choose to change a totally new youbike and go, or just pass the checkpoint without changing a new one.
// For The king on Akina Mount (we'll just call him "the king" in convenience), his speed is the fastest without any doubt. However, his youbike might break, too. But changing another youbike also takes time, we call it "penalty". The king wants to minimize the penalty, so that he could win this race. He ask you, the legendary mechanic, for help!
// The youbike race begins at position 0, ends at the endpoint. 
// While arriving each checkpoint, you can choose either to change a new youbike or continue with the original one. 
// Each youbike has the same damage degree k, and the damage degree will decrease 1 every 1 distance. Changing a new one means reset the damage degree to k. When the damage degree is lower than 0, the youobike breaks and the king loses. 
// Initially, the king is at position 0, and he's riding a totally new youbike, which means the damage degree is initially k.
// Given the position of every checkpoint and the location of endpoint, your task is to find out the minimum number of changing a new youbike. If he cannot reach the end, just output "The Legend Falls."

// Sweet caution:
// Do not break the speed when riding youbike.

// Input
// The first line contains two positive integers, n, k.
// The second line contains n positive integers indicate the position of every checkpoint. The position has been sorted in ascending order. The last station indicates the endpoint.
// The track is a straight line, and every checkpoint is on the right side of the initial position "0".
// 1<= n, k <= 100000, the position of every checkpoint will not exceed 100000.

// Output
// Output the minimum penalty, or "The Legend Falls." if the king cannot reach the end.
// Take the sample IO as an example, a new youbike can ride at most 5 unit long. The king will change another youbike at stations locate at 4 and 9, and finally reach the end point(14). 

// Sample Input  
// 6 5
// 2 4 7 8 9 14

// Sample Output  
// 2

#include<stdio.h>
#include<stdlib.h>

int main(){
    int n = 0, k = 0;
    int checkpoints[100005] = {0};
    scanf("%d %d\n", &n, &k);

    for(int i = 1; i <= n; i++){
        scanf("%d", &(checkpoints[i]));
    }

    int pos = k;
    int count = 0;
    int is_fall = 0;
    for(int i = 1; i <= n; i++){
        if(checkpoints[i] - checkpoints[i - 1] > k){
            is_fall = 1;
            break;
        }else if(pos < checkpoints[i]){
            count++;
            pos = checkpoints[i - 1] + k;
        }
    }

    if(is_fall){
        printf("The Legend Falls.\n");
    }else{
        printf("%d\n", count);
    }
    return 0;
}