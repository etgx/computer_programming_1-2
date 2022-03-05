// NTHUOJ 12155 - Cat-Toast crisis   
// Description
// Recently, scientists finally find a way to produce unlimited energy. The scientists call it "Cat-Toast".
// In case that someone might not know:
// While buttered toast falls onto the ground, it will always land with its buttered side - Falling Toast Theorem(FTT)
// While cats fall onto the ground, they will always land with their four feets. - Falling Cat Theorem(FCT)
// By FTT, we can assume that if we put butter on both sides of the toast, we might create a perpetual motion machine, because by FTT, we know that the buttered side will land onto the ground. However, there are two buttered sides. If any side of the toast lands, there will be a contradiction, so the toast will never fall and continue spinning around. We can apply the same way on FCT.
// However, there is a big problem. if we just put two buttered toasts or two cats together, there will be no momentum, and obviously it won't spin except for any external force, which cannot be a perpetual motion machine. This problem had confused scientists for centuries.
// Recently, scientists finally got a breakthrough progress. They combined a cat and a buttered toast and it just spins by itself! Due to the difference mass of a cat and a buttered toast, the machine itself will provide the momentum to spin, and it will never fall onto the ground (due to the contradiction we proved before), the first perpetual motion machine was born!
// The original video is here.

// Scientists found that if two cat-toasts' distance are equal to or closer than r, there will be a collision which cause a small black hole and soon disappear, which is very dangerous. The cat-toast must be secured separately. Also, if there are multiple cat-toasts that will collide, those cat-toasts will all collide together and spawn exactly one black hole. If there's any problem, you may refer to Sample I/O.
// One day in NTHU, a servitor just carries a lot of cat-toasts, each with a secured box. He accidently falls down and all the cat-toasts just drop out of their own boxes.
// Now given r and all the coordinates of all cat-toasts, the servitor wants to know how many cat-toasts remains there after some destructive collisions and how many black holes spawned. 
// Note that the distance of two cat-toasts is sqrt( (x1-x2)^2 + (y1-y2)^2 ), where (x1,y1) and (x2,y2) are the coordinates of this two.

// Input
// The first line contains two integers n, r, indicate the number of cat-toast, the distance r decribed above.
// The next n lines, each line contains two integers xi, yi, indicates the location of the i-th cat-toast.
// 1 <= n <= 1000, 1 <= r <= 104
// 1 <= xi, yi <= 104

// Output
// The first line of the output is the total number of cat-toasts that still remains and the total number of black holes after collisions, separated by a space.
// Remember to output a '\n' at the end of the output.
// (In fact, expect for the problem DO ask you not to output a '\n' at the end of the output, mostly you shoul output a '\n' at the end.)
// Take Sample I/O as an example, obviously cat-toast located at (5,15) and (1,15) will collide. (1,7), (1,3), and (5,3) will collide together because (1,7), (1,3) collides, and (1,3), (5,3) collides, just like a chain, or a tree.
// There's only one remaining cat-toast located at (500,500) and spawned 2 black holes, so the answer is "1 2" without quotes.

// Sample Input  
// 6 4
// 1 7
// 1 3
// 5 3
// 5 15
// 1 15
// 500 500

// Sample Output  
// 1 2

// #include<stdio.h>
// #include<stdlib.h>

// typedef struct catToast{
//     int x;
//     int y;
//     struct catToast *collision_to;
//     int is_collision;
// }CatToast;

// int isCollision(CatToast a, CatToast b, int r){
//     if((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) <= r * r){
//         return 1;
//     }else{
//         return 0;
//     }
// }

// CatToast *findHead(CatToast *a){
//     CatToast *temp = a;
//     CatToast *compressNodes[1005];
//     int compressCount = 0;
    
//     while(temp->collision_to != NULL){
//         temp = temp->collision_to;
//         // compressNodes[compressCount]->collision_to = temp;
//         // compressCount++;
//     }

//     // for(int i = 0; i < compressCount; i++){
//     //     compressNodes[i]->collision_to = temp;
//     // }

//     return temp;
// }

// int main(){
//     int n = 0, r = 0;
//     CatToast cat_toasts[1005];
//     // CatToast buckets[1005];
//     scanf("%d %d\n", &n, &r);

//     for(int i = 0; i < n; i++){
//         scanf("%d %d\n", &(cat_toasts[i].x), &(cat_toasts[i].y));
//         cat_toasts[i].collision_to = NULL;
//         cat_toasts[i].is_collision = 0;
//     }

//     for(int i = 0; i < n; i++){
//         for(int j = i + 1; j < n; j++){
//             if(isCollision(cat_toasts[i], cat_toasts[j], r)){
//                 if(cat_toasts[j].collision_to != NULL && cat_toasts[j].collision_to != NULL){
//                     // Merge Set
//                     CatToast *head_i = findHead(&(cat_toasts[i]));
//                     CatToast *head_j = findHead(&(cat_toasts[j]));
                    
//                     head_j->collision_to = head_i;
//                     head_j->is_collision = 1;
//                     cat_toasts[i].is_collision = 1;
//                     cat_toasts[j].collision_to = head_i;
//                     cat_toasts[j].is_collision = 1;
//                 }else if(cat_toasts[j].collision_to != NULL){
//                     // Merge node i to Set j
//                     CatToast *head = findHead(&(cat_toasts[j]));
//                     cat_toasts[i].collision_to = head;
//                     cat_toasts[i].is_collision = 1;
//                     // cat_toasts[j].collision_to = head;
//                 }else{
//                     // Merge node j to Set i or node i
//                     cat_toasts[j].collision_to = findHead(&(cat_toasts[i]));
//                     cat_toasts[i].is_collision = 1;
//                     cat_toasts[j].is_collision = 1;
//                 }
//             }
//         }
//     }

//     int collision_count = 0;
//     int uncollision_count = 0;
//     for(int i = 0; i < n; i++){
//         if(cat_toasts[i].collision_to == NULL && cat_toasts[i].is_collision == 1){
//             collision_count++;
//         }
//         if(cat_toasts[i].is_collision == 0){
//             uncollision_count++;
//         }
//     }

//     printf("%d %d\n", uncollision_count, collision_count);

//     return 0;
// }

#include<stdio.h>
#include<stdlib.h>
typedef struct catToast{
    int x;
    int y;
    int visited;
}CatToast;

int getDisSqrt(CatToast a, CatToast b){
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

int dfs(CatToast *catToasts, int now, int n, int r){
    int isRemain = 1;
    catToasts[now].visited = 1;

    for(int i = 0; i < n; i++){
        if(!catToasts[i].visited && getDisSqrt(catToasts[now], catToasts[i]) <= r * r){
            isRemain = 0;
            dfs(catToasts, i, n, r);
        }
    }

    return isRemain;
}

int main(){
    int n = 0, r = 0, remain = 0, blackhole = 0;
    CatToast catToasts[1005];
    // CatToast buckets[1005];
    scanf("%d %d\n", &n, &r);

    for(int i = 0; i < n; i++){
        scanf("%d %d\n", &(catToasts[i].x), &(catToasts[i].y));
        catToasts[i].visited = 0;
    }

    for(int i = 0; i < n; i++){
        if(catToasts[i].visited == 0){
            int res = dfs(catToasts, i, n, r);

            if(res){remain++;}
            else{blackhole++;}
        }
    }

    printf("%d %d\n", remain, blackhole);
    
    return 0;
}