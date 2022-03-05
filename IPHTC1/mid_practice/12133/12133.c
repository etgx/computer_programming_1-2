// NTHUOJ 12133 - Yes papa   
// Description
// Johnny is a three years old kid. He likes to eat sugar. One day, he sneaked into the kitchen in order to grab some sugar to eat. Unfortunately, his papa catched him.

// His papa called him: " Johnny, Johnny! "

// Johnny replied: " Yes, papa. "

// papa then asked: " Eating sugar? "

// Johnny lied: " No, papa. "

// At that moment, Johnny began to think that what's defintion of string equivalent?

// Johnny thinks that string a and string b is equivalent if a and b are the same or string a and string b can be devided into two same size part: a1, a2, b1, b2 and the following rules fulfill：

// (  ( a1 == b1 ) && ( a2 == b2 ) )  or  ( ( a1 == b2 ) && ( a2 == b1 ) )

// In above sentence, "==" means whether a and b are the same or string a and string b can be devided into two same size part: a1, a2, b1, b2 and the following rules fulfill: (  ( a1 == b1 ) && ( a2 == b2 ) )  or  ( ( a1 == b2 ) && ( a2 == b1 ) ). You can consider this equal definition as a recursion.

// For example: 

// a = " papa ", b = " apap ", we need to check if " pa " equals " ap " in Johnny ' s rule.

// Therefore, we divide " pa " into "p" and "a", and divide "ap" into "a" and "p". 

// Then, because "p" == "p" && " a " == "a", we know that "pa" == "ap".

// Hence, we can conclude that " papa " equals " apap ".

 

// Note that we can't divide a string if the length of the string is an odd number.

// Help Johnny find out whether the two string are the same. If you help him, he will give you some sugar.

 

 

 

 

// Input
// input contains two lines.

// First line is the string a. 

// Second line is the string b. 

// the length of the two string are the same and the length is from 1~105 ( 1 <= length <= 105 )

 

// Output
// output contains one line.

// print "YES" if two string is equal in Johnny's rule,

// print "NO" otherwise.

// remember to print \n at the end of output.

// Sample Input  
// apapapap
// papapapa
// Sample Output  
// YES


#include <stdio.h>
#include <stdlib.h>

int compare(char *a, int startA, int endA, char *b, int startB, int endB){
    int lenA = endA - startA + 1;
    int lenB = endB - startB + 1;

    int re_is_same = 1;

    if(lenA % 2 == 1){
        for(int iA = startA, iB = startB; iA <= endA, iB <= endB; iA++, iB++){
            if(a[iA] != b[iB]){re_is_same = 0; break;}
        }
    }else{
        int midA = (startA + endA) / 2;
        int midB = (startB + endB) / 2;
        if(compare(a, startA, midA, b, startB, midB) && compare(a, midA + 1, endA, b, midB + 1, endB)){
            re_is_same = 1;
        }else if(compare(a, startA, midA, b, midB + 1, endB) && compare(a, midA + 1, endA, b, startB, midB)){
            re_is_same = 1;
        }else{
            re_is_same = 0;
        }
    }

    return re_is_same;
}

int main(){
    char t;
    int i = 0;
    int j = 0;
    int is_newline = 0;
    char a[100005] = {0};
    char b[100005] = {0};

    while((t = getchar()) != EOF){
        if(t == '\n'){
            is_newline = 1;
        }else if(!is_newline){
            a[i] = t;
            i++;
            // printf("%c", t);
        }else{
            b[j] = t;
            j++;
            // printf("%c", t);
        }
    }

    if(compare(a, 0, i - 1, b, 0, j - 1)){
        printf("YES\n");
    }else{
        printf("NO\n");
    }

    return 0;
}