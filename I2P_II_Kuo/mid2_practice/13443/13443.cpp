/**
I2P - Kuo HW2 Problem 4 | NTHUOJ 13443 - Recursive Acronym
A recursive acronym is an acronym (an abbreviation word formed from the first letter of words) that refer to itselft recursively. For instance, GNU stands for GNU not Unix. In fact, Allegro is an atypical recursive acronym standing for Allegro Low LEvel Game ROutines.
In the community of computer science, there exists somewhat a tradition that quite a few people tend to choose such recursive acronym to express their humorousness, e.g. ATI stands for ATI Technology Incoperated (a graphic card manufacturer which was acquired by AMD and became Radeon later), TikZ stands for TikZ ist kein Zeichenprogramm (German; TikZ is not a drawing program, TikZ is a LaTeX package to draw vector graphics), and so forth.
In this problem, your task is to determine whether some words can form a typical recursive acronym refering to the first word.

Note
This problem is case-insensitive, i.e., it does not matter that a letter is lower case or upper case.
You could call getline() to get entire content including spaces of a line until the newline character, and use stringstream to split the line by spaces.  For more detail, you may refer to online resources.

Input
Each test case may contain several lines. For each line, please determine whether it can form a typical recursive acronym refering to its first word or not.
The number of lines won't exceed 10. Each line won't contain more than 1000 words. The length of words won't exceed 1000.

Output
For each line, if it can form a typical recursive acronym refering to its first word, then print o'_'o, otherwise QQ. Remember to put a newline character.

Sample Input  
PIP install packages
National Tsing Hua University
curl url request library
Computer Science
PHP hypertext preprocessor

Sample Output  
o'_'o
QQ
o'_'o
QQ
o'_'o

**/
#include <string>
#include <sstream>
#include <cctype>
#include <iostream>

#define ACRONYM "o'_'o"
#define NOT_ACRONYM "QQ"

int main(){
    std::string str = std::string();
    // std::getline(std::cin, str);
    // std::cout << "INIT: " << str << std::endl;

    // while(!std::cin.eof()){
    while(std::getline(std::cin, str)){
        // std::cout << "OK" << std::endl;
        std::stringstream stream;
        std::string abbr = std::string(), shorten = std::string();
        bool is_acronym = true;

        stream << str;

        stream >> abbr;
        shorten = shorten + abbr.at(0);

        for(int idx = 1; ; idx++){
            std::string buf = std::string();
            stream >> buf;
            if(stream.fail()) break;
            // std::cout << shorten << " : " <<  buf << std::endl;
            // if(buf.size() <= 0) break;
            shorten = shorten + buf.at(0);
        }

        if(shorten.size() != abbr.size() || shorten.size() <= 0 || abbr.size() <= 0){
            is_acronym = false;
        }else{
            for(int i = 0; i < shorten.size(); i++){
                if(tolower(shorten.at(i)) != tolower(abbr.at(i))){
                    is_acronym = false;
                    break;
                }
            }
        }

        if(is_acronym){
            std::cout << ACRONYM << std::endl;
        }else{
            std::cout << NOT_ACRONYM << std::endl;
        }

        // std::getline(std::cin, str);
    }
}