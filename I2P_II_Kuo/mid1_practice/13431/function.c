// I2P - Kuo Week1 Problem 2 | NTHUOJ 13431 - Palindrome Linked List   
// Description
// Do you notice that the ID of this problem is a palindrome number? This problem, though, requires you to determine whether a linked list is a palindrome - i.e., it reads the same backwards as forwards.
// Please implement such a function.

// Input
// Since this problem is judged partially, you needn't be concerned about the format of input.
// The length of the linked list is at least 1 and won't exceed 100000.
// In case your're interested in sample I/O, there are several test cases in a file, which starts with a interger n indicating the length of the list and the next line contains n intergers.

// Output
// Since this problem is judged partially, you needn't be concerned about the format of output.
// In case your're interested in sample I/O, for each test case, if the list is a palindrome, it should print a single T, otherwise print a F. There should be a new line at the end of file (EOF).

// Sample Input  

// 3
// 78 89 78
// 3
// 78 89 689
// 6
// 78 89 92 78 89 92
// 6
// 78 89 92 92 89 78

// Sample Output  

// TFFT

#include "function.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool is_palindrome(node *head){
    int n = 0, palindrome_len = 0;
    node *temp = NULL;
    for(n = 0, temp = head; temp != NULL; n++, temp = temp->next){}
    palindrome_len = n / 2;

    // printf("N: %d, Palindrome Len: %d\n", n, palindrome_len);

    int palindrome_bytes = sizeof(int) * palindrome_len;
    int *palindrome = (int*)malloc(palindrome_bytes);
    memset(palindrome, 0, palindrome_bytes);
    temp = head;
    for(int i = palindrome_len - 1; i >= 0; i--){
        palindrome[i] = temp->val;
        // printf("%d ", palindrome[i]);
        temp = temp->next;
    }
    // printf(" - ");

    if(n % 2){
        temp = temp->next;
    }

    for(int i = 0; i < palindrome_len; i++){
        if(palindrome[i] != temp->val){return false;}
        // printf("%d ", temp->val);
        temp = temp->next;
    }
    free(palindrome);
    return true;
}