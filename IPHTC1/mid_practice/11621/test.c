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

// Sample Output  
// 0
// 2
// 10

// 2020/05/01 SYC

#include<stdio.h>
#include<stdlib.h>

#define BuffSize 3000

void countPalindrome(char *buff, int buffCount){
    long long int panlidromeCount = 0;
    
    for(int i = 1; i < buffCount; i++){
        int panlidromeSize = 0;
        int currentIdct = i;

        // Even Panlidrome
        int evenIdct = i - 1;
        while(evenIdct >= 0 && currentIdct < buffCount){
            if(buff[currentIdct] == buff[evenIdct]){
                panlidromeSize += 2;
                // printf("EVEN[%d]%c = [%d]%c: %d\n", currentIdct, buff[currentIdct], evenIdct, buff[evenIdct], panlidromeSize);
                evenIdct--;
                currentIdct++;
                panlidromeCount++;
            }else{break;}
        }

        // Odd Panlidrome
        int oddIdct = i - 2;
        currentIdct = i;
        panlidromeSize = 1;
        while(oddIdct >= 0 && currentIdct < buffCount){
            if(buff[currentIdct] == buff[oddIdct]){
                panlidromeSize += 2;
                // printf("ODD [%d]%c = [%d]%c: %d\n", currentIdct, buff[currentIdct], oddIdct, buff[oddIdct], panlidromeSize);
                oddIdct--;
                currentIdct++;
                panlidromeCount++;
            }else{break;}
        }
        panlidromeSize = 0;
    }
    // printf("Count: %d\n", panlidromeCount);
    printf("%lld\n", panlidromeCount);
}

int main(){
    char temp = '0';
    char buff[BuffSize] = {0};
    int buffCount = 0;

    while((temp = getchar()) != EOF){
        if(temp != '\n'){
            // printf("%c", temp);
            buff[buffCount] = temp;
            buffCount++;
        }else{
            // printf("\n");
            countPalindrome(buff, buffCount);
            for(int i = 0; i < buffCount; i++){
                // printf("%c",buff[i]);
                buff[i] = 0;
            }
            buffCount = 0;
        }
    }
    // printf("\n");
    countPalindrome(buff, buffCount);

    return 0;
}