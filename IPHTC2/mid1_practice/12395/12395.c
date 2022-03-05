// IPHTC2 Week6 Problem 1 | NTHUOJ 12395 - Storm Area 51
// Description
// If we naruto run, we can move faster than their bullets.
// ── Unknown naruto runner
// "Storm Area 51, They Can't Stop All of Us" is an event that invites everyone to intrude into the famous America military base "Area 51" on Sep. 20, 2019. In this event, participants are asked to use naruto run to intrude Area 51 so that they can move faster than their bullets.
// However, performing naruto run challenges the control of Chakra(查克拉) of the runner. They have to control the flow of Chakra and distribute it appropriately so that they could be able to run steadily.
// A runner run over the camera. Shot in 1/1000 sec. The original report is here.
// On every step, a pre-order binary expression and some values would cross runners' mind. Runners needs to rearrange the binary expression into in-order and calculate the answer of this expression, so that they can naruto run steadily and dodge those bullets.
// You are an adviser of this event. Somehow you can read the runners' mind and tell them the answers of these expressions. You're going to write a program to help them, otherwise they will be hit by bullets.
// Because naruto run is a simple ninjutsu(忍術), the expression won't be too complicated, so the variables in an expression won't exceed 3(x,y,zx,y,z). And we don't care about the parentheses.

// Input
// The first line contains the whole expression in pre-order. The length of the input string wouldn't exceed 100.
// The input expression would contain:
// variable (x,y,z)
// operator (+,-,*,/)
// integers in range [1,100]
// The second line contains three integers represent x, y, z, respectively.
// 1 <= x,y,z <= 100. You don't have to worry about overflow or underflow.
// Note that there will be a space after every operator, number, and variable. Please refer to the sample.

// Output
// On the first line, output the expression in in-order. There should be no space between every operator, number, and variable.
// On the second line, output the result of this expression.

// Sample Input 1 
// / + x * 3 y 4
// 3 1 9

// Sample Output 1
// x+3*y/4
// 1

// Hint
// Take the sample as example:
// We use the pre-order binary expression the build a syntax tree, the tree should look like the following graph:

// /
// +
// 4
// x
// *
// 3
// y
// Now, we can write down the in-order: x+3*y/4. Note that we don't add spaces or parentheses.
// And we know that x=3, y=1, z=9, then calculate the answer: (3+3*1)/4=6/4=1.
// Note that we only pick the integer part to calculate.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPRESSION_SIZE 101
#define BUF_SIZE 5

char expression[MAX_EXPRESSION_SIZE] = {0};

void get_char(char *buf, int size, int reset){
    // Indicator
    static int i;
    if(reset){
        i = 0;
        return;
    }

    // read string
    char c = expression[i++];
    if(c == ' '){
        get_char(buf, size, 0);
    }else if(c >= '0' && c <= '9'){
        buf[0] = c;
        // printf("Get: %c\n", c);
        for(int buf_i = 1; expression[i] >= '0' && expression[i] <= '9' && buf_i < size; i++, buf_i++){
            // printf("Get: %c\n", c);
            buf[buf_i] = expression[i];
        }
    }else{
        // printf("Get: %c\n", c);
        buf[0] = c;
    }
}

int evaluate(int x, int y, int z){
    char buf[BUF_SIZE] = {0};
    get_char(buf, BUF_SIZE, 0);

    if(buf[0] == '+'){
        int expr_l = evaluate(x, y, z);
        printf("+");
        int expr_2 = evaluate(x, y, z);
        // printf("%d = %d + %d\n", expr_l + expr_2, expr_l, expr_2);
        return expr_l + expr_2;
    }else if(buf[0] == '-'){
        int expr_l = evaluate(x, y, z);
        printf("-");
        int expr_2 = evaluate(x, y, z);
        // printf("%d = %d - %d\n", expr_l - expr_2, expr_l, expr_2);
        return expr_l - expr_2;
    }else if(buf[0] == '*'){
        int expr_l = evaluate(x, y, z);
        printf("*");
        int expr_2 = evaluate(x, y, z);
        // printf("%d = %d * %d\n", expr_l * expr_2, expr_l, expr_2);
        return expr_l * expr_2;
    }else if(buf[0] == '/'){
        int expr_l = evaluate(x, y, z);
        printf("/");
        int expr_2 = evaluate(x, y, z);
        // printf("%d = %d / %d\n", expr_l / expr_2, expr_l, expr_2);
        return expr_l / expr_2;
    }else if(buf[0] == 'x'){
        // printf("X = %d\n", x);
        printf("x");
        return x;
    }else if(buf[0] == 'y'){
        // printf("Y = %d\n", y);
        printf("y");
        return y;
    }else if(buf[0] == 'z'){
        // printf("Z = %d\n", z);
        printf("z");
        return z;
    }else if(buf[0] >= '0' && buf[0] <= '9'){
        int constant = atoi(buf);
        printf("%d", constant);
        // printf("Const: %d\n", constant);
        return constant;
    }
}

int main(){
    int x = 0, y = 0, z = 0;
    char temp[BUF_SIZE] = {0};

    scanf("%[^\n]s", expression);
    scanf("%d %d %d", &x, &y, &z);
    get_char(temp, BUF_SIZE, 1);

    // printf("Expression: %s\n", expression);
    // printf("X: %d Y: %d Z: %d\n", x, y, z);
    printf("\n%d\n", evaluate(x, y, z));
    return 0;
}