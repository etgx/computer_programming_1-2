#include<stdio.h>

typedef struct {
    char s[24];
    int a, b;
}Fac;

Fac fac[1000], list_a[1000], list_b[1000];
int n, x, y, tmp;

int cmp0(Fac *a, Fac *b)
{
    if( a->a - a->b > b->a - b->b ) return -1;
    else if( a->a - a->b < b->a - b->b ) return 1;
    else return 0;
}

int cmp1(Fac *a, Fac *b)
{
    if( a->a > b->a) return -1;
    else if( a->a < b->a) return 1;
    else return 0;
}

int cmp2(Fac *a, Fac *b)
{
    if( a->b > b->b) return -1;
    else if( a->b < b->b) return 1;
    else return 0;
}

int cmp3(Fac *a, Fac *b)
{
    return strcmp( a->s, b->s);
}

int split(int mid)
{
    tmp = 0;
    if( mid < x ) return;
    if( n-mid < y ) return;
    int len_a=0, len_b=0, i;
    for(i=0; i<mid; i++){
        list_a[i] = fac[i];
        len_a++;
    }
    for(i=mid; i<n; i++){
        list_b[i-mid] = fac[i];
        len_b++;
    }

    qsort(list_a, len_a, sizeof(Fac), cmp1);
    qsort(list_b, len_b, sizeof(Fac), cmp2);

    for(i=0; i<x; i++) tmp += list_a[i].a;
    for(i=mid; i<mid+y; i++) tmp += list_b[i-mid].b;
    return tmp;
}

int main()
{
    int i;

    scanf("%d%d%d", &n, &x, &y);

    for(i=0; i<n; i++){
        scanf("%s%d%d", &fac[i].s, &fac[i].a, &fac[i].b);
    }
    qsort(fac, n, sizeof(Fac), cmp0);

    int ans = -1, mid = x;
    for(i=0; i<n; i++){
        tmp = split(i);
        if(tmp > ans){
            ans = tmp;
            mid = i;
        }
    }

    split(mid);
    qsort(list_a, x, sizeof(Fac), cmp3);
    for(i=0; i<x; i++){
        printf("%s\n", list_a[i].s);
    }
}
