#include "function.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void show()
{
    if(head == NULL)
        {
        printf("\n");
        return;
    }
    Node *now = head->ptr_to_next_node;
    while(now != head)
    {
        printf("%c ", now->character);
        now = now->ptr_to_next_node;
    }
    printf("\n");
}
int main()
{
    int n = 0;
    scanf("%d",&n);
    head = (Node*)malloc(sizeof(Node));
    head->character = '0';
    head->ptr_to_next_node = head->ptr_to_prev_node = head;
    Node *cursor = tail = head;
    while(n--)
    {
        int num = 0;
        char buf[20] = {0};

        scanf("%s",buf);
        if(!strcmp(buf,"insert"))
        {
            char intype = 0;
            getchar();
            scanf("%c",&intype);
            // printf("->%s %c\n", buf, intype);
            insert(&cursor, intype); 
        }
        else if(!strcmp(buf,"deletion"))
        {
            // printf("->%s\n", buf);
            deletion(&cursor);
        }
        else if(!strcmp(buf,"backspace"))
        {
            // printf("->%s\n", buf);
            backspace(&cursor); 
        }
        else if(!strcmp(buf,"go_left"))
        {
            scanf("%d", &num);
            // printf("->%s %d\n", buf, num);
            go_left(&cursor, num); 
        }
        else if(!strcmp(buf,"go_right"))
        {
            scanf("%d", &num);
            // printf("->%s %d\n", buf, num);
            go_right(&cursor, num); 
        }
        else if(!strcmp(buf,"go_home"))
        {
            // printf("->%s\n", buf);
            go_home(&cursor);
        }
        else if(!strcmp(buf,"go_end"))
        {
            // printf("->%s\n", buf);
            go_end(&cursor); 
        }
        else if(!strcmp(buf,"show"))
        {
            // printf("->%s\n", buf);
            show();
        }
        // printf("-->Cursor is at %c\n", cursor->character);
    }
    return 0;
}