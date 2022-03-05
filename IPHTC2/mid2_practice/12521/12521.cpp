// IPHTC2 Week9 Problem 1 | NTHUOJ 12521 - Break my heart
// Description
// I have broken many girls' hearts into pieces. But none of them mad at me. None.
// ​ ~ by anonymous surgeon
// You're a surgeon, you need to mend those girls' heart. Therefore you need a data structure to support some functions.
// This question is about maintain a set that contain only integers.
// There will be nn instruction.
// Each instruction will be either:

// insert:
// Insert a new element a_i into the set. Note that if the element has already in the set, do nothing.

// print:
// print all the element in the set in increasing order.

// min:
// print the number in the set that is the smallest. If there's no number, do nothing.

// range_erase:
// You will have two integer l, r
// You need to erase all the elements a_i  in the set that l \leq a_i \leq r

// sum: (Different from practice!!)
// print the sum of the elements in the set.

// Hint: You can solve this question very fast by using std::set .
// These are some functions you may use in your code:
// set.begin(), set.size(), set.erase(), set.lower_bound(), set.upper_bound(), set.insert(). To traverse through your set, you may also need iterator or type auto(only in c++11!) meme

// Input
// the input will contain several lines.
// The first line only contains an integer n
// The following are n lines.
// Each lines contains a instruction list above.
// Note that a_i (0 \leq a_i \leq 10^9) testcase 1~4: 1 \leq n \leq 5000

// testcase 5: n = 200000
// For testcase 5 there's no "print" instruction.

// Output
// For each print instruction, print all the number in the set in increasing order.
// Each number is separated by a single blank.(No blank at the the end!)
// Remember to print \n at the end of output
// For each min instruction, print the smallest number in the set.
// Remember to print \n at the end of output

// Sample Input 1 

// 11
// print
// range_erase 3 53
// min
// insert 90
// insert 36
// min
// insert 1
// print
// insert 26
// range_erase 7 57
// print

// Sample Output 1

// 36
// 1 36 90
// 1 90

// Hint
// The reference of C++ and C.
// ![reference.zip](http://140.114.85.195/public/upload/reference.zip)

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <set>

using namespace std;

#define PRINT_INSTR "print"
#define RANGE_ERASE_INSTR "range_erase"
#define MIN_INSTR "min"
#define INSERT_INSTR "insert"
#define SUM_INSTR "sum"
#define MAX_INSTR_LEN 15
#define MAX_VAL_IN_SET 1000000001
#define EMPTY_FLAG -1

void print(set<long long> *s){
    if(s->size() < 1) return;

    set<long long>::iterator iter = s->begin();
    cout << *iter;
    iter++;
    for(; iter != s->end(); iter++){
        cout << " " << *iter;
    }
    cout << "\n";
}

void insert(set<long long> *s, long long x){
    s->insert(x);
}

long long min(set<long long> *s){
    if(s->size() < 1) return EMPTY_FLAG;
    long long min_val = MAX_VAL_IN_SET;
    for(set<long long>::iterator iter = s->begin(); iter != s->end(); iter++){
        if(*iter < min_val){
            min_val = *iter;
        }
    }
    return min_val;
}

void range_erase(set<long long> *s, long long l, long long r){
    set<long long>::iterator l_iter = s->lower_bound(l), r_iter = s->upper_bound(r);
    s->erase(l_iter, r_iter);
}

long long sum(set<long long> *s){
    if(s->size() < 1) return EMPTY_FLAG;
    long long sum = 0;
    for(set<long long>::iterator iter = s->begin(); iter != s->end(); iter++){
        sum += *iter;
    }
    return sum;
}

int main(){
    long long n = 0;
    set<long long> s;
    scanf("%lld", &n);

    for(long long i = 0; i < n; i++){
        char instr[MAX_INSTR_LEN] = {0};
        scanf("%s", instr);

        if(!strcmp(instr, PRINT_INSTR)){
            print(&s);
        }else if(!strcmp(instr, INSERT_INSTR)){
            long long x = 0;
            scanf("%lld", &x);
            insert(&s, x);
        }else if(!strcmp(instr, MIN_INSTR)){
            long long min_val = min(&s);
            if(min_val != EMPTY_FLAG){
                printf("%lld\n", min_val);
            }
        }else if(!strcmp(instr, RANGE_ERASE_INSTR)){
            long long l = 0, r = 0;
            scanf("%lld %lld", &l, &r);
            range_erase(&s, l, r);
        }else if(!strcmp(instr, SUM_INSTR)){
            long long sum_val = sum(&s);
            if(sum_val != EMPTY_FLAG){
                printf("%lld\n", sum_val);
            }
        }
    }

    return 0;
}