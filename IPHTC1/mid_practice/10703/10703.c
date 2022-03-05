// NTHUOJ 10703 A-Dualily
// Description
// Leafa drew a convex polygon. She thought the polygon is so cute so that she wanted to give it to her brother, Kirito, as a gift. But before she ever had the chance to do so Kirito spotted the cute polygon in the Leafa's computer. Kirito thought one is not enough because he loves to use dual blades in many online games he plays. So he used a simple polyline to split the convex poly-
// gon into two non-empty simple polygons and saved them into two different files.
// When Leafa realized her convex polygon has been splitted she is so sad because those two simple ploygons are not as cute as the original one. So she asks you to put them back into one convex polygon. Can you help her?
// A polygon is a plane gure bounded by a nite chain of line segments closing in a loop. A convex polygon is a polygon that any line drawn through the polygon which are not tangent to a point or an edge of the polygon intersects with the boundary of the polygon exactly twice. A simple polygon is a polygon whose bondaries do not cross itself. A polyline, or a polygonal chain is a connected series of line segments. A simple polyline is a polyline that only consecutive line segments intercest and only intersecting on their ends.

// Input
// The first line of the input data contains an integer T (1 ≤ T ≤101) specifying the number of test cases.
// The first line of each test case contains an integers N (3 ≤ N ≤ 100,000) indicating the number of points of the first simple polygon. The N lines following contains two integers x, y each line (0 ≤ x, y ≤ 109) indicating the coordinates of the points.
// The (N + 2)th line of each test case contains an integers M (3 ≤ M ≤ 100,000) indicating the number of points of the second simple polygon. The M lines following contains two integers x, y each line (0 ≤ x, y ≤ 109) indicating the coordinates of the points.
// The points in a polygon are given in counterclockwise order. No two points in a polygon are at the same spot and no three consecutive points in a polygon are co-line. Note that two polygons in a test case may overlap since the coordinates may be shifted while saving the le. For at least 95 test cases, N, M ≤ 1000.

// Output
// For each test case, if two simple polygons cannot put back to a convex polygon due to le corruption, please output "No" on a single line. Otherwise first output "Yes" and two integers dx dy in a single line where the vector (dx, dy) indicating the movement of the second polygon so that it can join the first. If there is multiple possible solutions output the one with least dx, if still more than one possible solutions then output the least dy among the ones with the least dx. Note " " is only for clarity.

// Sample Input  
// 1
// 3
// 0 0
// 1 1
// 0 2
// 4
// 2 0
// 4 1
// 2 2
// 3 1

// Sample Output  
// Yes -2 0

// 2020/05/01 SYC

#include<stdio.h>
#include<stdlib.h>

typedef struct coord(){
    long int x;
    long int y;
} Coord;

void moveCoord(Coord *coord, long int dx, long int dy){
    coord->x += dx;
    coord->y += dy;
}

void movePolygon(Coord *polygon, long int polygonVerticeCount, long int dx, long int dy){
    for(int i = 0; i < polygonVerticeCount; i++){
        moveCoord(&(polygon[i]), dx, dy);
    }
}



int main(){
    int T = 0;
    scanf("%d\n", &T);

    for(int i = 0; i < T; i++){
        int N = 0;
        scanf("%d\n", &N);

        for(int j = 0; j < N; j++){
            long int x = 0, y = 0;
            scanf("%d %d\n", &x, &y);
        }

        int M = 0;
        scanf("%d\n", &M);
        for(int j = 0; j < M; j++){
            long int x = 0, y = 0;
            scanf("%d %d\n", &x, &y);
        }
    }

    return 0;
}