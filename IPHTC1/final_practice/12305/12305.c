// NTHUOJ12305 - Airplane Shooter   
// Description
// It's a beautiful day outside. birds are singing, flowers are blooming... on days like these, kids like you... Should be burning in hell. Uhhhh... I mean, nothing, literally. (original: undertale sans dialogue)
// Even such a beautiful day like this, we shall watch out for the chance that there might be bombing plane bombing our campus. That's why we need our fortification, that is, the well-known "Airplane Shooter".
// "The True Appearance of the Airplane Shooter" PC by TA
// However, living in this "peaceful" era, we don't actually need to worry about bombing planes or "Little Boy" or somethin else like that. The Airplane Shooter is no longer be needed, so the school committee decided to turn it to a "public art", everyone is able to get closer to our legendary Airplane Shooter.
// Nothing lasts forever. Some "fart child" use it to flash those unfortunate passers. The famous Airplane Shooter has also become the infamous "Moto-shooter".
// Now, Knuckles is going to shoot(flash) those goddamnpoor motorcycles down because those motorcycles block his way of finding his queen.
// Knuckles could recognize the owner of every motorcycle. He prefers to shoot those school administration staffs first, especially the president. If their administration level are the same, he would like to shoot those motorcycles with smaller license plate number(which is literally a "number").
// Given the sequence of those motorcycles and their infos, you are going to tell Knuckles the order of shooting down.
// Given a sequence a. The elements of a has the following infomations:

// index: The index is followed by the input order, starts from 1. The input won't contain index, you have to record it yourself. Smaller input index has higher priority.
// admin level: Level starts from 0 to 999. level 0 has the highest priority, while level 999 has the lowest.
// level 0: president Hong Hocheng
// level 1: stuff of different school affairs
// level 2: junior sister(學妹)
// level 3: senior sister(學姊)
// level 4: senior brother(學長)
// level 5: campus stray dogs/cats
// level 6: squirrel
// level 7: pigeon
// ......
// level 999: junior brother(學弟)
// license number: An integer. Smaller number has higher priority.

// You are going to sort a. Element with higher priority brings to the front. Compare admin level first, then license number, then index.
// Output index(the old one) of every element in the new a.

// Input
// The first line contains an integer n, indicates the number of elements in a.
// There are n lines below. Start from the first line of the n lines, the i-th line contains the i-th information. Each line contains 2 integers admin level and license number.
// 1 <= n <= 105, 0 <= admin level <= 999, 1 <= license number <= 109

// Output
// Output the old index of every element in the new a respectively, each separated with a space
// Note that there should be no space after the last number but a '\n'.

// Sample Input  
// 5
// 6 60
// 1 20
// 999 1000000000
// 1 40
// 0 20

// Sample Output  
// 5 2 4 1 3

#include<stdio.h>
#include<stdlib.h>

typedef struct item{
    int idx;
    int admin;
    int license;
}Item;

int cmp(const Item *a, const Item *b){
    const int aLarger = 1;
    const int bLarger = 0;
    // Compare Admin
    if(a->admin > b->admin){
        return aLarger;
    }else if(a->admin < b->admin){
        return bLarger;
    }else{
        // Compare License
        if(a->license > b->license){
            return aLarger;
        }else if(a->license < b->license){
            return bLarger;
        }else{
            // Compare Index
            if(a->idx > b->idx){
                return aLarger;
            }else if(a->idx < b->idx){
                return bLarger;
            }
        }
    }
}

int main(){
    int n = 0;
    scanf("%d", &n);

    Item *array = (Item *)malloc(sizeof(Item) * n);

    for(int i = 0; i < n; i++){
        scanf("%d %d\n", &(array[i].admin), &(array[i].license));
        array[i].idx = i + 1;
    }

    qsort(array, n, sizeof(Item), (int (*)(const void *, const void *))cmp);
    
    printf("%d", array[0].idx);
    for(int i = 1; i < n; i++){
        printf(" %d", array[i].idx);
    }
    printf("\n");

    return 0;
}
