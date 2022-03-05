// NTHUOJ 11619 pC - Collinear   
// Description
// You are given sets of N points in two-dimensional space. It is guaranteed that no two points coincide in each set.
// For each set, please calculate the number of lines which pass through at least three points in the set.

// Input
// The first line contains an integer T, representing the number of testcases (sets).
// For each testcase (set) :
// The first line contains an integer N, representing the number of points in this set.
// The next N line contain two integer xi, yi, representing the coordinates of the i-th point. All points in the set are distinct.
// 1 ≤ T ≤ 20
// 1 ≤ N ≤ 100
// -200000 ≤ xi, yi ≤ 200000

// Output
// For each testcase (set), please output a line contains an integer representing your answer.
// (i.e. Please print '\n' after each answer.)

// Sample Input  
// 4
// 3
// 0 0
// 1 1
// 1 2
// 3
// 1 2
// 2 4
// 4 8
// 4
// 1 1
// 2 2
// 3 3
// 4 4
// 5
// 0 0
// 2 0
// 0 2
// 2 2
// 1 1

// Sample Output  
// 0
// 1
// 1
// 2

#include<stdio.h>
#include<stdlib.h>

#define CoordBuffSize 200
#define CoordLabelsArraySize 10005

typedef struct linear{
    long int ah;
    long int ar;
    long int bh;
    long int br;
    long int x1;
    long int y1;
} Linear;

typedef struct coord{
    long int x;
    long int y;
    int linearBelongCount;
    int linearLabelsMap[CoordLabelsArraySize]; // Index represent the label of the line. If [index] = 1, it mean that the coord is belongs to line "index".
    int linearLabels[CoordLabelsArraySize]; // Record the labels of lines.
} Coord;

Linear getLinear(Coord c1, Coord c2){
    Linear lin;
    lin.ah = c2.y - c1.y;
    lin.ar = c2.x - c1.x;
    lin.bh = (c1.y * c2.x) - (c2.y * c1.x);
    lin.br = c2.x - c1.x;
    lin.x1 = c1.x;
    lin.y1 = c1.y;

    return lin;
}

int checkColinear(Linear lin, Coord c){
    if(lin.ah == 0){
        if(lin.y1 == c.y){
            return 1;
        }else{
            return 0;
        }
    }else if(lin.ar == 0){
        if(lin.x1 == c.x){
            return 1;
        }else{
            return 0;
        }
    }else if((lin.ah * lin.br * c.x) + (lin.ar * lin.bh)  == (c.y * lin.ar * lin.br)){
        return 1;
    }else{
        return 0;
    }
}

void setColinear(Coord *c, int label){
    c->linearLabels[c->linearBelongCount] = label;
    c->linearLabelsMap[label] = 1;
    c->linearBelongCount++;
}

int isColinear(Coord c1, Coord c2){
    if(c1.linearBelongCount == 0 || c2.linearBelongCount == 0){
        return 0;
    }else{
        if(c1.linearBelongCount < c2.linearBelongCount){
            for(int i = 0; i < c1.linearBelongCount && i < CoordLabelsArraySize; i++){
                if(c2.linearLabelsMap[c1.linearLabels[i]] == 1){
                    return 1;
                }
            }
        }else{
            for(int i = 0; i < c2.linearBelongCount && i < CoordLabelsArraySize; i++){
                if(c1.linearLabelsMap[c2.linearLabels[i]] == 1){
                    return 1;
                }
            }
        }
    }

    return 0;
}

int main(){
    int T = 0;
    scanf("%d\n", &T);
    

    for(int i = 0; i < T; i++){
        int N = 0;
        Coord *coordBuff = (Coord *)malloc(sizeof(Coord) * CoordBuffSize);
        int totalLinearCount = 0;
        scanf("%d\n", &N);
        // printf("TestCase%d %dVertice\n", i, N);
        // printf("LinearCount: %d\n", totalLinearCount);

        for(int k = 0; k < N; k++){
            scanf("%ld %ld", &(coordBuff[k].x), &(coordBuff[k].y));
            // coordBuff[k].linearLabels = {-1};
            // coordBuff[k].linearLabelsMap = {0};
            coordBuff[k].linearBelongCount = 0;
            // printf("%ld %ld\n", coordBuff[k].x, coordBuff[k].y);
        }

        for(int k = 0; k < N; k++){
            for(int p = k + 1; p < N; p++){
                if(!isColinear(coordBuff[k], coordBuff[p])){
                    Linear lin = getLinear(coordBuff[k], coordBuff[p]);
                    // printf("C%d(%ld, %ld) C%d(%ld, %ld)\n", k, coordBuff[k].x, coordBuff[k].y, p, coordBuff[p].x, coordBuff[p].y);
                    int isNewLinear = 1;

                    for(int q = p + 1; q < N; q++){
                        // printf("CheckColinear a = ah:%ld / ar:%ld b = bh:%ld / br:%ld; Q:C%d(%ld, %ld): %c\n", lin.ah, lin.ar, lin.bh, lin.br, q, coordBuff[q].x, coordBuff[q].y, checkColinear(lin, coordBuff[q]) == 1? 'T':'F');
                        if(checkColinear(lin, coordBuff[q])){
                            if(isNewLinear){
                                // printf("NewLinear C%d(%ld, %ld): %d Belongs to C%d(%ld, %ld) C%d(%ld, %ld)\n", q, coordBuff[q].x, coordBuff[q].y, totalLinearCount, k, coordBuff[k].x, coordBuff[k].y, p, coordBuff[p].x, coordBuff[p].y);
                                setColinear(&(coordBuff[k]), totalLinearCount);
                                setColinear(&(coordBuff[p]), totalLinearCount);
                                setColinear(&(coordBuff[q]), totalLinearCount);
                                isNewLinear = 0;
                                
                            }else{
                                // printf("ExtendLinear C%d(%ld, %ld): %d\n", q, coordBuff[q].x, coordBuff[q].y, totalLinearCount);
                                setColinear(&(coordBuff[q]), totalLinearCount);
                            }
                        }
                    }
                    if(!isNewLinear){totalLinearCount++;}
                }
            }
        }

        printf("%d\n", totalLinearCount);
        // printf("LinearCount: %d\n", totalLinearCount);
        // printf("---------------------------------------------\n");
    }

    return 0;
}