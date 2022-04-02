/**
I2P - Kuo HW2 Problem 2 | NTHUOJ 13161 - Kuo Sends Names To Mars
Kuo-chan can help send names to Mars.
However, he hates palindromes of length greater than 1. He gets upset whenever receiving a name containing palindrome substrings of length greater than 1.
We call a name's substring a palindrome if and only if it reads the same backwards and forwards. A string a is a substring of a string b if a can be obtained from b by deleting several (possibly zero or all) characters from the beginning and several (possibly zero or all) characters from the end.

For example, 
"bcd" and "e" are substrings of "abcde" but "ace" and "bz" are not.
"abccba", "aba", and "ee" are palindromes but "abcd" and "abcabc" are not.
Yang-chan also wants to send his name to Mars. However, as Kuo-chan's best friend, he doesn't want to upset Kuo-chan.
Therefore, Yang-chan will modify his name by replacing a letter at any position with any English letter. He can use this operation arbitrarily many times (possibly zero).
Yang-chan wants to know how many letters have to be modified at least?
(Please use C++  to solve this problem.)

Input
The first and only line of the input contains a non-empty string S of lowercase English letters — Yang-chan's name.
The length of S will not exceed 105.

Output
You should output a single integer, meaning the number of letters Yang-chan has to modify at least to avoid upsetting Kuo-chan.
Remember to add new line in the end

Sample Input  
abacaba

Sample Output  
2

Reference

1. [Code Studio - Remove All The Palindromes](https://www.codingninjas.com/codestudio/problem-details/remove-all-the-palindromes_1559746)

*/

#include <string>
#include <iostream>

#define ALPHABET_RANGE 26

int main(){
    char alt_count = 'A';
    std::string str = std::string();
    std::cin >> str;
    int str_size = str.size(), count = 0;

    // std::cout << str << std::endl;

    for(int i = 0; i < str_size; i++){
        if(i + 1 < str_size && str.at(i) == str.at(i + 1)){
            str.at(i + 1) = alt_count;
            alt_count = (alt_count + 1) % ALPHABET_RANGE;
            count++;
        }

        if(i + 2 < str_size && str.at(i) == str.at(i + 2)){
            str.at(i + 2) = alt_count;
            alt_count = (alt_count + 1) % ALPHABET_RANGE;
            count++;
        }
    }

    std::cout << count << std::endl;
}