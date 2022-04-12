#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DEBUG 0

// for lex
#define MAXLEN 256

// Token types
typedef enum {
    UNKNOWN, END, ENDFILE,
    INT, ID,
    ADDSUB, MULDIV,
    AND, OR, XOR,
    INCDEC,
    ASSIGN,
    LPAREN, RPAREN
} TokenSet;

TokenSet getToken(void);
TokenSet curToken = UNKNOWN, prevToken = UNKNOWN;;
char lexeme[MAXLEN] = {0}, prevLexeme[MAXLEN] = {0};

// Test if a token matches the current token
int match(TokenSet token);
// Get the next token
void advance(void);
// Get the lexeme of the current token
char *getLexeme(void);


// for parser
#define TBLSIZE 64
// Set PRINTERR to 1 to print error message while calling error()
// Make sure you set PRINTERR to 0 before you submit your code
#define PRINTERR 1

// Call this macro to print error message and exit the program
// This will also print where you called it in your program
#define error(errorNum) { \
    if (PRINTERR) \
        fprintf(stderr, "error() called at %s:%d: ", __FILE__, __LINE__); \
    err(errorNum); \
}

// Error types
typedef enum {
    UNDEFINED, MISPAREN, NOTID, NOTNUMID, NOTFOUND, RUNOUT, NOTLVAL, DIVZERO, SYNTAXERR
} ErrorType;

// Structure of the symbol table
typedef struct {
    int val;
    char name[MAXLEN];
} Symbol;

// Structure of a tree node
typedef struct _Node {
    TokenSet data;
    int val;
    char lexeme[MAXLEN];
    struct _Node *left;
    struct _Node *right;
} BTNode;

int sbcount = 0;
Symbol table[TBLSIZE];

// Initialize the symbol table with builtin variables
void initTable(void);
// Get the value of a variable
int getval(char *str);
// Set the value of a variable
int setval(char *str, int val);
// Make a new node according to token type and lexeme
BTNode *makeNode(TokenSet tok, const char *lexe);
// Free the syntax tree
void freeTree(BTNode *root);
BTNode *factor(void);
BTNode *term(void);
BTNode *term_tail(BTNode *left);
BTNode *expr(void);
BTNode *expr_tail(BTNode *left);
void statement(void);
// Print error message and exit the program
void err(ErrorType errorNum);


// for codeGen
// Evaluate the syntax tree
int evaluateTree(BTNode *root);
// Print the syntax tree in prefix
void printPrefix(BTNode *root);


/*============================================================================================
lex implementation
============================================================================================*/

TokenSet getToken(void)
{
    int i = 0;
    char c = '\0';

    while ((c = fgetc(stdin)) == ' ' || c == '\t');

    if (isdigit(c)) {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while (isdigit(c) && i < MAXLEN) {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return INT;
    } else if (c == '+') {
        // @MODIFIED:
        lexeme[0] = c;
        c = fgetc(stdin);
        if(c == '+'){
            lexeme[1] = c;
            lexeme[2] = '\0';
            return INCDEC;
        }else{
            ungetc(c, stdin);
        }
        lexeme[1] = '\0';
        return ADDSUB;
    }else if(c == '-'){
        // @MODIFIED:
        lexeme[0] = c;
        c = fgetc(stdin);
        if(c == '-'){
            lexeme[1] = c;
            lexeme[2] = '\0';
            return INCDEC;
        }else{
            ungetc(c, stdin);
        }
        lexeme[1] = '\0';
        return ADDSUB;
    }else if (c == '&') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return AND;
    }else if (c == '^') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return XOR;
    }else if (c == '|') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return OR;
    }else if (c == '*' || c == '/') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return MULDIV;
    } else if (c == '\n') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return END;
    } else if (c == '=') {
        strcpy(lexeme, "=");
        return ASSIGN;
    } else if (c == '(') {
        strcpy(lexeme, "(");
        return LPAREN;
    } else if (c == ')') {
        strcpy(lexeme, ")");
        return RPAREN;
    } else if (isalpha(c) || c == '_') {
        // @MODIFIED:
        // lexeme[0] = c;
        // lexeme[1] = '\0';

        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while ((isalpha(c) || isdigit(c) || c == '_') && i < MAXLEN) {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return ID;
    } else if (c == EOF) {
        return ENDFILE;
    } else {
        return UNKNOWN;
    }
}

// @MODIFIED:
void unadvance(void) {
    int symbolLen = strlen(lexeme);
    for(int i = symbolLen - 1; i >= 0; i--){
        ungetc(lexeme[i], stdin);
    }
    memcpy(lexeme, prevLexeme, MAXLEN * sizeof(char));
    curToken = prevToken;
    prevToken = UNKNOWN;
}

void advance(void) {
    // @MODIFIED:
    memcpy(prevLexeme, lexeme, MAXLEN * sizeof(char));
    prevToken = curToken;
    curToken = getToken();
}

int match(TokenSet token) {
    if (curToken == UNKNOWN)
        advance();
    return token == curToken;
}

char *getLexeme(void) {
    return lexeme;
}


/*============================================================================================
parser implementation
============================================================================================*/

void initTable(void) {
    strcpy(table[0].name, "x");
    table[0].val = 0;
    strcpy(table[1].name, "y");
    table[1].val = 0;
    strcpy(table[2].name, "z");
    table[2].val = 0;
    sbcount = 3;
}

int getval(char *str) {
    int i = 0;

    for (i = 0; i < sbcount; i++)
        if (strcmp(str, table[i].name) == 0)
            return table[i].val;

    // @MODIFIED:
    // if (sbcount >= TBLSIZE)
    //     error(RUNOUT);

    // strcpy(table[sbcount].name, str);
    // table[sbcount].val = 0;
    // sbcount++;

    error(NOTFOUND);
    return 0;
}

int setval(char *str, int val) {
    int i = 0;

    for (i = 0; i < sbcount; i++) {
        if (strcmp(str, table[i].name) == 0) {
            table[i].val = val;
            return val;
        }
    }

    if (sbcount >= TBLSIZE)
        error(RUNOUT);

    strcpy(table[sbcount].name, str);
    table[sbcount].val = val;
    sbcount++;
    return val;
}

BTNode *makeNode(TokenSet tok, const char *lexe) {
    BTNode *node = (BTNode*)malloc(sizeof(BTNode));
    strcpy(node->lexeme, lexe);
    node->data = tok;
    node->val = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void freeTree(BTNode *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

void print_tri_node(const char *str, BTNode *root){
    if(!DEBUG) return;
    printf("%s", str);
    if(root != NULL){
        printf(" [%s] -", root->lexeme);
        if(root->left != NULL){
            printf(" L:[%s]", root->left->lexeme);
        }
        if(root->right != NULL){
            printf(" R:[%s]", root->right->lexeme);
        }
    }
    printf("\n");
}


// unary_expr := ADDSUB unary_expr | factor
BTNode *unary_expr(){
    BTNode *retp = NULL;
    if(match(ADDSUB)){
        retp = makeNode(ADDSUB, getLexeme());
        advance();
        retp->left = makeNode(INT, "0");
        print_tri_node("Unary:", retp);
        retp->right = unary_expr();
        print_tri_node("Unary_Expr: AddSub Unary_Expr", retp);
    }else{
        // printf("Unary - Factor Lexeme: %s %d\n", getLexeme(), curToken);
        retp = factor();
        print_tri_node("Unary_Expr: Factor", retp);
    }
    return retp;
}

// muldiv_expr_tail := MULDIV unary_expr muldiv_expr_tail | NiL
BTNode *muldiv_expr_tail(BTNode *left){
    BTNode *retp = NULL;
    if(match(MULDIV)){
        retp = makeNode(MULDIV, getLexeme());
        advance();
        retp->left = left;
        retp->right = unary_expr();
        print_tri_node("MulDiv_Expr_Tail: MULDIV Unary_Expr MulDiv_Expr_Tail", retp);
        BTNode *root = muldiv_expr_tail(retp);
        // if(root != NULL) return root;
        print_tri_node("Unary_Expr: Factor", retp);
        return root;
    }else{
        return left;
    }
    // return retp;
}

// muldiv_expr := unary_expr muldiv_expr_tail
BTNode *muldiv_expr(){
    BTNode *left = unary_expr();
    // BTNode *retp = muldiv_expr_tail(left);
    // if(retp == NULL){
    //     retp = left;
    // }
    // print_tri_node("MulDiv_Expr: AddSub_Expr MulDiv_Expr_Tail", retp);
    // return retp;
    return muldiv_expr_tail(left);
}

// addsub_expr_tail := ADDSUB muldiv_expr addsub_expr_tail | NiL
BTNode *addsub_expr_tail(BTNode *left){
    BTNode *retp = NULL;
    if(match(ADDSUB)){
        retp = makeNode(ADDSUB, getLexeme());
        advance();
        retp->left = left;
        retp->right = muldiv_expr();
        // BTNode *root = addsub_expr_tail(retp);
        // if(root != NULL) return root;
        return addsub_expr_tail(retp);
    }else{
        return left;
    }
    // return retp;
}

// addsub_expr := muldiv_expr addsub_expr_tail
BTNode *addsub_expr(){
    BTNode *left = muldiv_expr();
    // BTNode *retp = addsub_expr_tail(left);
    // if(retp == NULL){
    //     retp = left;
    // }
    // print_tri_node("AddSub_Expr: MulDiv_Expr AddSub_Expr_Tail", retp);
    // return retp;
    return addsub_expr_tail(left);
}

// assign_expr := ID ASSIGN assign_expr | or_expr
BTNode *assign_expr(){
    BTNode *retp = NULL;
    if(match(ID)){
        BTNode *left = makeNode(ID, getLexeme());
        advance();
        if(match(ASSIGN)){
            retp = makeNode(ASSIGN, getLexeme());
            advance();
            retp->left = left;
            retp->right = assign_expr();
            print_tri_node("Assign_Expr: ID = Assign_Expr", retp);
        }else{
            unadvance();
            retp = addsub_expr();
            print_tri_node("Assign_Expr: AddSub_Expr", retp);
            // printf("Enter Unary\n");
            // retp = unary_expr();
            // print_tri_node("Assign_Expr: Unary_Expr", retp);
        }
    }else{
        retp = addsub_expr();
        print_tri_node("Assign_Expr: AddSub_Expr", retp);
        // retp = unary_expr();
        // print_tri_node("Assign_Expr: Unary_Expr", retp);
    }
    return retp;
}

// factor := INT | ID | INCDEC ID | LPAREN assign_expr RPAREN
BTNode *factor(void) {
    BTNode *retp = NULL, *left = NULL;

    if (match(INT)) {
        retp = makeNode(INT, getLexeme());
        advance();
    } else if (match(ID)) {
        retp = makeNode(ID, getLexeme());
        advance();
    } else if (match(INCDEC)) {
        retp = makeNode(INCDEC, getLexeme());
        retp->left = NULL;
        advance();
        if(match(ID)){
            retp->right = makeNode(ID, getLexeme());
            advance();
        }else{
            error(NOTID);
        }
    } else if (match(LPAREN)) {
        advance();
        retp = assign_expr();
        if (match(RPAREN))
            advance();
        else
            error(MISPAREN);
    } else {
        printf("NOTNUMID: %s\n", getLexeme());
        error(NOTNUMID);
    }
    return retp;
}

// term := factor term_tail
BTNode *term(void) {
    BTNode *node = factor();
    return term_tail(node);
}

// term_tail := MULDIV factor term_tail | NiL
BTNode *term_tail(BTNode *left) {
    BTNode *node = NULL;

    if (match(MULDIV)) {
        node = makeNode(MULDIV, getLexeme());
        advance();
        node->left = left;
        node->right = factor();
        return term_tail(node);
    } else {
        return left;
    }
}

// expr := term expr_tail
BTNode *expr(void) {
    BTNode *node = term();
    return expr_tail(node);
}

// expr_tail := ADDSUB term expr_tail | NiL
BTNode *expr_tail(BTNode *left) {
    BTNode *node = NULL;

    if (match(ADDSUB)) {
        node = makeNode(ADDSUB, getLexeme());
        advance();
        node->left = left;
        node->right = term();
        return expr_tail(node);
    } else {
        return left;
    }
}

// statement := ENDFILE | END | assign_expr END
void statement(void) {
    BTNode *retp = NULL;

    if (match(ENDFILE)) {
        exit(0);
    } else if (match(END)) {
        printf(">> ");
        advance();
    } else {
        // retp = expr();
        retp = assign_expr();
        if (match(END)) {
            printf("%d\n", evaluateTree(retp));
            printf("Prefix traversal: ");
            printPrefix(retp);
            printf("\n");
            freeTree(retp);
            printf(">> ");
            advance();
        } else {
            error(SYNTAXERR);
        }
    }
}

void err(ErrorType errorNum) {
    if (PRINTERR) {
        fprintf(stderr, "error: ");
        switch (errorNum) {
            case MISPAREN:
                fprintf(stderr, "mismatched parenthesis\n");
                break;
            case NOTID:
                fprintf(stderr, "identifier expected\n");
                break;
            case NOTNUMID:
                fprintf(stderr, "number or identifier expected\n");
                break;
            case NOTFOUND:
                fprintf(stderr, "variable not defined\n");
                break;
            case RUNOUT:
                fprintf(stderr, "out of memory\n");
                break;
            case NOTLVAL:
                fprintf(stderr, "lvalue required as an operand\n");
                break;
            case DIVZERO:
                fprintf(stderr, "divide by constant zero\n");
                break;
            case SYNTAXERR:
                fprintf(stderr, "syntax error\n");
                break;
            default:
                fprintf(stderr, "undefined error\n");
                break;
        }
    }
    exit(0);
}


/*============================================================================================
codeGen implementation
============================================================================================*/

int evaluateTree(BTNode *root) {
    int retval = 0, lv = 0, rv = 0;

    if (root != NULL) {
        switch (root->data) {
            case ID:
                retval = getval(root->lexeme);
                break;
            case INT:
                retval = atoi(root->lexeme);
                break;
            case ASSIGN:
                rv = evaluateTree(root->right);
                retval = setval(root->left->lexeme, rv);
                break;
            // @MODIFIED:
            case INCDEC:
                if(strcmp(root->lexeme, "++") == 0) {
                    rv = getval(root->right->lexeme) + 1;
                }else if(strcmp(root->lexeme, "--") == 0) {
                    rv = getval(root->right->lexeme) - 1;
                }
                retval = setval(root->right->lexeme, rv);
                break;
            case ADDSUB:
            case MULDIV:
                lv = evaluateTree(root->left);
                rv = evaluateTree(root->right);
                if (strcmp(root->lexeme, "+") == 0) {
                    retval = lv + rv;
                } else if (strcmp(root->lexeme, "-") == 0) {
                    retval = lv - rv;
                } else if (strcmp(root->lexeme, "*") == 0) {
                    retval = lv * rv;
                } else if (strcmp(root->lexeme, "/") == 0) {
                    if (rv == 0)
                        error(DIVZERO);
                    retval = lv / rv;
                }
                break;
            default:
                retval = 0;
        }
    }
    return retval;
}

void printPrefix(BTNode *root) {
    if (root != NULL) {
        printf("%s ", root->lexeme);
        printPrefix(root->left);
        printPrefix(root->right);
    }
}


/*============================================================================================
main
============================================================================================*/

// This package is a calculator
// It works like a Python interpretor
// Example:
// >> y = 2
// >> z = 2
// >> x = 3 * y + 4 / (2 * z)
// It will print the answer of every line
// You should turn it into an expression compiler
// And print the assembly code according to the input

// This is the grammar used in this package
// You can modify it according to the spec and the slide
// statement  :=  ENDFILE | END | expr END
// expr    	  :=  term expr_tail
// expr_tail  :=  ADDSUB term expr_tail | NiL
// term 	  :=  factor term_tail
// term_tail  :=  MULDIV factor term_tail| NiL
// factor	  :=  INT | ADDSUB INT |
//		   	      ID  | ADDSUB ID  |
//		   	      ID ASSIGN expr |
//		   	      LPAREN expr RPAREN |
//		   	      ADDSUB LPAREN expr RPAREN

int main() {
    initTable();
    printf(">> ");
    while (1) {
        statement();
    }
    return 0;
}
