#include <stdbool.h>

typedef struct _node
{
    int val;
    struct _node *next;
} node;

bool is_palindrome(node *head); // return true value if the linked list is a palindrome, otherwise false
