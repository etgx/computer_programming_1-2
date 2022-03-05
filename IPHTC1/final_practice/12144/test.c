#include <stdio.h>
int atk, a[6][6], b[6][6], c[6][6], ans = 0;
void explore(int x, int y, int blood)
{
    if(x == 5 && y == 5)
    {
        if(b[x][y] == 0)
        {
            ans++;
        }
        else
        {
            blood = battle(blood, b[x][y], c[x][y]);
            if(blood > 0)
            {
                ans++;
            }
        }
    }else if(b[x][y] > 0)
    {
        blood = battle(blood, b[x][y], c[x][y]);
    }

    if(x + 1 < 6 && y + 1 < 6 && x + 1 > 0 && y + 1 > 0 && a[x+1][y+1] == 0)
    {
        a[x+1][y+1] = 1;
        explore(x+1, y+1, blood);
        a[x+1][y+1] = 0;
    }else if(x + 1 < 6 && y - 1 < 6 && x + 1 > 0 && y - 1 > 0 && a[x+1][y-1] == 0)
    {
        a[x+1][y-1] = 1;
        explore(x+1, y-1, blood);
        a[x+1][y-1] = 0;
    }else if(x - 1 < 6 && y + 1 < 6 && x - 1 > 0 && y + 1 > 0 && a[x-1][y+1] == 0)
    {
        a[x-1][y+1] = 1;
        explore(x-1, y+1, blood);
        a[x-1][y+1] = 0;
    }else if(x - 1 < 6 && y - 1 < 6 && x - 1 > 0 && y - 1 > 0 && a[x-1][y-1] == 0)
    {
        a[x-1][y-1] = 1;
        explore(x-1, y-1, blood);
        a[x-1][y-1] = 0;
    }
}
int battle(int blood, int monblood, int monattack)
{
    int bld = monblood;
    while(bld > 0)
    {
        bld -= atk;
        if(bld > 0) blood -= monattack;
    }
    return blood;
}
int main(void)
{
    int blood, num, j, k, x, y;
    scanf("%d%d%d", &blood, &atk, &num);
    for(int i = 0; i < num; i++)
    {
       scanf("%d%d%d%d", &j, &k, &x, &y);
       b[x][y] = j;
       c[x][y] = k;
    }
    explore(1, 1, blood);
    if(ans) printf("HEIR OF FIRE DESTROYED\n");
    else printf("YOU DIED\n");

    return 0;
}