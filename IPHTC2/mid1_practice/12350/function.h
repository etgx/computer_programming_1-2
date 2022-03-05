typedef struct _NODE
{
    char character;
    struct _NODE *ptr_to_next_node;
    struct _NODE *ptr_to_prev_node;
}Node;

struct _NODE *head, *tail;

void insert(struct _NODE **cur, char c);

void deletion(struct _NODE **cur);

void backspace(struct _NODE **cur);

void go_left(struct _NODE **cur, int t);

void go_right(struct _NODE **cur, int t);

void go_home(struct _NODE **cur);

void go_end(struct _NODE **cur);

void show();