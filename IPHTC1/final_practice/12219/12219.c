// NTHUOJ 12219 - Uncle Huang Points Tutor   
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
// (Inspired by the post  靠北清大7754)

// Although uncle Huang loses the distich competition, he is still seeking for a male tutor. He would choose one of those who left comments below his post as his tutor ( and one cannot refuse! ). Because too many people left comments below ( just like Shiao said, he's truly a topic master ), he would pick two numbers "x" and "y", and choose the (xy)-th person that left a comment as his tutor. 
// Because xy might be too big, so the answer would mod(取模) a number "m", which is the total number of comments of his post.
// Uncle Huang is too busy seeking for his true love tutor, he asks you for help, could you help him find out his true love tutor?
// You are given three numbers "x", "y", and "m", you have to calculate the answer of ((xy)%m) .
// Hint: Use "Fast Power" method to solve this problem!

// Input
// The input contains only one line. 
// The first line contains exactly three numbers "x", "y", and "m", which are described above. 
// 1 <= x <= 1018,, 0 <= y <= 1018, 1 <= m <= 109.

// Output
// Output one number: (xy)%m .
// Remember th print a '\n' at the end of the output.

// Sample Input  
// 775477547754 775477547754 10235876

// Sample Output  
// 9284380

// 2020/05/27 SYC

#include<stdio.h>
#include<stdlib.h>

long long int fastPowerMod(long long int x, long long int y, long long int m){
    if(m == 0){return 0;}
    if(y == 0 || x == 1){return 1 % m;}
    else if(y == 1){return x % m;}
    else if(y % 2){return ((x % m) * (fastPowerMod(((x % m) * (x % m)) % m, y >> 1, m) % m)) % m;}
    else if(!(y % 2)){return fastPowerMod(((x % m) * (x % m)) % m, y >> 1, m) % m;}
}

int main(){
    long long int x = 0, y = 0, m = 0;
    scanf("%lld %lld %lld", &x, &y, &m);

    printf("%lld\n", fastPowerMod(x, y, m));

    return 0;
}