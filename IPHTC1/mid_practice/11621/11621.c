// NTHUOJ 11621 pE - Exquisite Substrings   
// Description
// HT Chen is an aspiring (also a little bit naughty) professor in NTHU. One day he felt extremely bored in his laboratory, so he decided to write down some strings on a paper. After writing down some strings, HT discovered that for some special string s, he could find two distinct indices l and r such that if he reverses the substring s[l, r], the whole string would still remain unchanged. HT found this property very exquisite, so he decided to name this kind of substring after "exquisite substring".
// HT is wondering how many "exquisite substrings" are there in each string he wrote on the paper. Counting them by hand will be a dreadful work, so he decides to give extra homework so you guys can help him solve this problem.
// If you can't solve this problem, HT maybe be disappointed and the upcoming midterm will become harder than usual.
// wink** For someone who doesn't know the definition of substring : https://en.wikipedia.org/wiki/Substring 

// Input
// There are multiple lines in each testcase. Each line contains a string si that HT wrote on the paper.
// The input file is ended by 'EOF'.
// It is guaranteed that :
// At most 10 lines in each testcase.
// testcase #1 ~ #4 : 1 ≤ | s | ≤ 200
// testcase #5 Bonus: 1 ≤ | s | ≤ 2000

// Output
// For each string si, please output a line contains one integer representing the number of "exquisite substrings" in si.
// (i.e. Please print '\n' after each answer.)

// Sample Input  
// abcd
// abab
// aaaaa
// cdabaafbaabaa
// cdabaafcddcdcddc

// Sample Output  
// 0
// 2
// 10
// 7
// 12

// 2020/05/01 SYC

#include <stdio.h>
#include <stdlib.h>
#define BuffSize 2005

int solve(char *buff){
    int strSize = 0;
    int panlidromeCount = 0;
    for(strSize = 0; strSize < BuffSize; strSize++){
        if(!buff[strSize]) break;
    }
    // printf("%d\n", strSize);

    for(int i = 1; i < strSize; i++){
        // Even
        for(int l = i - 1, r = i; l >= 0 && r < strSize; l--, r++){
            if(buff[l] == buff[r]){panlidromeCount++;}
            else{break;}
        }
        // Odd
        for(int l = i - 2, r = i; l >= 0 && r < strSize; l--, r++){
            if(buff[l] == buff[r]){panlidromeCount++;}
            else{break;}
        }
    }

    printf("%d\n", panlidromeCount);
}

int main(){
    char buff[BuffSize] = {0};

    while(scanf("%s", buff) != EOF){
        // printf("%s\n", buff);
        solve(buff);
    }

    return 0;
}