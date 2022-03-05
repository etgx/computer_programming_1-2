// NTHUOJ 12127 - too many words   
// Status  |  Limits 
// Description
// Ovuvuevuevue Enyetuenwuevue Ugbemugbem Osas just got some writing homework to do.

// His teacher gave him some texts, then asked him to write all of these texts once, and by hand.

// However, Osas wants to cheat, so he ask you to write a program to repeat these texts exactly once so that he can just print them onto an A4 paper and turn in the homework easily.

// (Although you know that finish the work by computer and printer, he will definitely get a ZERO, however, you still have to complete your task to get your AC.)

 

// Input
// The input contains a lot of texts. You don't know when will the text ends, but you know that there must be EOF at the end of the input.

// And you know that the total amount of characters won't exceed 107.

// Output
// Print exactly the same as the input, even spaces and wraps('\n').

 

// Sample Input  
// TA good yeahhhhhhhhh       awesome!
// NO      WA_____iS __ GIveN_ _ by_US,ALLBy   JuDGE.....?..


//     GoTcHA



// Sample Output  
// TA good yeahhhhhhhhh       awesome!
// NO      WA_____iS __ GIveN_ _ by_US,ALLBy   JuDGE.....?..


//     GoTcHA




#include<stdlib.h>
#include<stdio.h>

int main(){
    char t = '0';
    while((t = getchar()) != EOF){
        putchar(t);
    }

    return 0;
}