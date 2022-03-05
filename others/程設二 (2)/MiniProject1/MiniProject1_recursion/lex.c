#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "lex.h"
#include "parser.h"
static TokenSet getToken(void);
static TokenSet lookahead = UNKNOWN;
static char lexeme[MAXLEN];

TokenSet getToken(void)
{
    int i;
    char c;

    while ( (c = fgetc(stdin)) == ' ' || c== '\t' );  // �����ťզr��

    if (isdigit(c)) {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while (isdigit(c) && i<MAXLEN) { //�p�G�����쪺�r�O�Ʀr�A�h���_���ݤU�@�Ӧr�O�Ʀr
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return INT; //lexeme�x�s���O�ƭ� �^�ǳo�O�@��INT
    } else if (c == '+' || c == '-') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return ADDSUB;//lexeme�x�s���O+����-�� �^�ǳo�O�[�δ�
    } else if (c == '*' || c == '/') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return MULDIV;//lexeme�x�s���O*����/�� �^�ǳo�O���ΰ�
    } else if (c == '\n') {
        lexeme[0] = '\0';
        return END;//Ū�촫�� �^�ǵ����⦡
    } else if (c == '=') {
        strcpy(lexeme, "=");
        return ASSIGN;//Ū�쵥�� �ε���\�����lexeme �^�ǫ����ƭ�
    } else if (c == '(') {
        strcpy(lexeme, "(");
        return LPAREN;//Ū�쥪�A�� �Υ��A���\�����lexeme �^�ǥ��A��
    } else if (c == ')') {
        strcpy(lexeme, ")");
        return RPAREN;//Ū��k�A�� �Υk�A���\�����lexeme �^�ǥk�A��
    } else if (isalpha(c) || c == '_') {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;//Ū��r�����ܡA���ݤU�@�Ӧr��
        while (isalpha(c) || isdigit(c) || c == '_') {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return ID;//lexeme�s���O��Ӧr���զ����N�� �^�ǥN��
    } else if (c == EOF) {
        return ENDFILE;//Ū���󵲧� �^�ǵ���
    } else {
        lexeme[0] = c;
        lexeme[1] = '\0';
        error(NOTFOUND);
        return UNKNOWN;//Ū��ҥ~���p �^�ǥ���
    }
}

void advance(void)//�ΨөI�sgetToken()�A�Y��U�@��exprrsion���N��
{
    lookahead = getToken();
}

int match(TokenSet token)//�ΨӤ��ǨӪ��򤧫e���쪺Token�@���@�ˡA�p�G�S��LToken�ΤW�ӧ쪺Token�O�ҥ~�A�A��@��Token�A�ھڱ��p�^��1��0
{
    if (lookahead == UNKNOWN) advance();
    return token == lookahead;
}

char* getLexeme(void)//�^�Ƿ�e�s�۪�lexeme�A�i��O�Ÿ� �ƭ� �ΥN��
{
    return lexeme;
}

