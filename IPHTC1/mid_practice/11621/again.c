// Another AC Version
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

    return 0;
}