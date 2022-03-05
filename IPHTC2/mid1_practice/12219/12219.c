// IPHTC2 Week4 Problem 2 | NTHUOJ 12219 - Uncle Huang Points Tutor
// Description
// Disclaimer: If something described below happened or happens in real world, which is just a coincidence. We will not take any responsibility of any coincidence.
// Uncle: I'm an employee of the library and dating master, nickname "Uncle Huang", who are you?
// Shiao: Two years tutor experience, straying book boy of second-hand section, "Shiao Tsing".
// Uncle: Well, well. Let me test you!
// Uncle: In the painting, dragons won't roar, tigers won't howl, little book boy, funny funny!
// Shiao: In the article, man is allowed, woman is forbidden, seeking tutor, urgent urgent!
// Uncle: Warbler, swallow, emerald, red, prosperous, harmonious, everywhere.
// Shiao: Tutor, Shu-shu, urgent, critial, anxious, serious, swimming pool.
// Wang Ye: Another distich!
// Uncle: See a jerk standing over there.
// Shiao: Seek a tutor swimming over the pool.
// Uncle: I am hero in the battle field.
// Shiao: You are topic master booming the post.
// Uncle: Ahhhhh........!
// (Inspired by the post 靠北清大7754 - should've been deleted)

// Although uncle Huang loses the distich competition, he is still seeking for a male tutor. He would choose one of those who left comments below his post as his tutor ( and one cannot refuse! ). 
// Because too many people left comments below ( just like Shiao said, he's truly a topic master ), he would pick two numbers xx and yy, and choose the (x^y)(x^y)-th person that left a comment as his tutor.
// Because x^y might be too big, so the answer would mod(取模) a number mm, which is the total number of comments of his post.
// Uncle Huang is too busy seeking for his true love tutor, he asks you for help, could you help him find out his true love tutor?
// You are given three integers x, y, and m, you have to calculate the answer of (x^y)\%m.

// Input
// The input contains only one line.
// The first line contains exactly three numbers xx, yy, and mm, which are described above.
// 1 <= x <= 10^18, 0 <= y <= 10^18, 1 <= m <= 10^9.

// Output
// Output one number: (x^y)\%m.
// Remember th print a '\n' at the end of the output.

// Sample Input 1 
// 775477547754 775477547754 10235876

// Sample Output 1
// 9284380

// Hint
// Use "Fast Power" method to solve this problem!

// 2021/10/10 SYC 

#include <stdio.h>
#include <stdlib.h>

#define MAX_SHIFT_BITS 64

unsigned long long fast_power(unsigned long long x, unsigned long long y, unsigned long long m){
    unsigned long long res = 1 % m, power = x % m;
    // printf("X: %llu, Y: %llu, M: %llu\n", x, y, m);
    // printf("Res: %llu Pow: %llu\n", res, power);

    for(int i = 0; i < MAX_SHIFT_BITS; i++){
        if((y >> i) & 1){
            res = (res * power) % m;
        }
        // printf("Res: %llu Pow: %llu, Bit: %llu\n", res, power, (y >> i) & 1);
        power = (power * power) % m;
    }
    return res;
}

int main(){
    unsigned long long x=0, y=0, m=0;
    scanf("%llu %llu %llu", &x, &y, &m);
    printf("%llu\n", fast_power(x, y, m));
    return 0;
}