#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <vector>
#include <string>
#include <iostream>

#define DEBUG 1
#define DEBUG_TRI_NODE 0

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
    UNDEFINED, MISPAREN, NOTID, INVALIDIDHEAD, INVALIDID, NOTNUMID, NOTFOUND, RUNOUT, NOTLVAL, DIVZERO, SYNTAXERR, MEMNOTSET
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
BTNode *statement(void);
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
    if(!DEBUG_TRI_NODE) return;
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

void semantic_check(BTNode *root){
    if(root == NULL) return;

    switch(root->data){
        case(MULDIV):
            if(strcmp(root->lexeme, "/") == 0 && root->right != NULL){
                if(root->right->data == INT && atoi(root->right->lexeme) == 0){
                    error(DIVZERO);
                }
            }
            semantic_check(root->left);
            semantic_check(root->right);
        break;
        case(ID):
            if(!((root->lexeme[0] >= 'a' && root->lexeme[0] <= 'z') || 
               (root->lexeme[0] >= 'A' && root->lexeme[0] <= 'Z') || 
               (root->lexeme[0] == '_'))){
                error(INVALIDIDHEAD);
            }
            for(int i = 0; i < MAXLEN; i++){
                if(!((root->lexeme[0] >= '0' && root->lexeme[0] <= '9') || 
                    (root->lexeme[0] >= 'a' && root->lexeme[0] <= 'z') || 
                    (root->lexeme[0] >= 'A' && root->lexeme[0] <= 'Z') || 
                    (root->lexeme[0] == '_'))){
                    error(INVALIDID);
                }
            }
            getval(root->lexeme);
            semantic_check(root->left);
            semantic_check(root->right);
        break;
        case(ASSIGN):
            if(root->left == NULL || (root->left != NULL && root->left->data != ID)){
                error(NOTID);
            }
            setval(root->left->lexeme, 0);
            semantic_check(root->right);
        break;
        default:
            semantic_check(root->left);
            semantic_check(root->right);
        break;
    }
}

BTNode* parse(){
    BTNode *retp = assign_expr();
    if(match(END)) {
        semantic_check(retp);
    }else {
        error(SYNTAXERR);
    } 
    return retp;
}

void AST_print(BTNode *head){
    const int MAX_LENGTH = 256;
    static char indent_str[MAX_LENGTH] = "";
	static int indent = 0;
	char *indent_now = indent_str + indent;
	const static char KindName[][20] = {
        "UNKNOWN", "END", "ENDFILE", "INT", "ID", "ADDSUB", "MULDIV", "AND", "OR", "XOR", "INCDEC", "ASSIGN", "LPAREN", "RPAREN"
	};
	const static char format[] = "%s, <%s>\n";
	const static char format_str[] = "%s, <%s = %s>\n";
	const static char format_val[] = "%s, <%s = %d>\n";
	if (head == NULL) return;
	indent_str[indent - 1] = '-';
	printf("%s", indent_str);
	indent_str[indent - 1] = ' ';
	if (indent_str[indent - 2] == '`')
		indent_str[indent - 2] = ' ';
	switch (head->data) {
        case UNKNOWN:
        case END:
		case ASSIGN:
		case ADDSUB:
		case MULDIV:
		case AND:
		case OR:
        case XOR:
		case INCDEC:
		case LPAREN:
		case RPAREN:
			printf(format, KindName[head->data], (char*)&(head->lexeme));
			break;
		case ID:
			printf(format_str, KindName[head->data], "name", (char*)&(head->lexeme));
			break;
		case INT:
			printf(format_val, KindName[head->data], "value", atoi(head->lexeme));
			break;
		default:
			puts("=== unknown AST type ===");
	}
	indent += 2;
	strcpy(indent_now, "| ");
	AST_print(head->left);
	strcpy(indent_now, "` ");
	AST_print(head->right);
	indent -= 2;
	(*indent_now) = '\0';
}

void visualize_AST(BTNode *root){
    printf("\n====================\nAST\n");
    AST_print(root);
    printf("\n====================\n");
}

// statement := ENDFILE | END | assign_expr END
BTNode* statement(void) {
    BTNode *retp = NULL;

    if (match(ENDFILE)) {
        exit(0);
    } else if (match(END)) {
        advance();
    } else {
        retp = parse();
        if (match(END)) {
            advance();
        } else {
            error(SYNTAXERR);
        }
    }
    return retp;
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
            case INVALIDIDHEAD:
                fprintf(stderr, "the head of the identifier should be a-z, A-Z, or _\n");
                break;
            case INVALIDID:
                fprintf(stderr, "invalid identifier\n");
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
            case MEMNOTSET:
                fprintf(stderr, "the memory slot hasn't been setted\n");
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

typedef enum{INVALID_MOVE, ISA_ERR, SPACE_ERR, STACK_ERR, MACHINE_CODE_ERR}CODEGEN_ERR;

#define code_gen_error(err_code, fmt, ...) \
printf("**********************************\n"); \
fprintf(stdout, "error() called at %s:%d: ", __FILE__, __LINE__); \
printf(fmt, __VA_ARGS__); \
printf("\n"); \
code_gen_err_code(err_code); \
printf("**********************************\n");

void code_gen_err_code(CODEGEN_ERR err_code){
    if (PRINTERR) {
        fprintf(stdout, "error: ");
        switch(err_code){
            case INVALID_MOVE:
                fprintf(stdout, "invalid move instruction\n");
                break;
            case ISA_ERR:
                fprintf(stdout, "invalid ISA operation\n");
                break;
            case SPACE_ERR:
                fprintf(stdout, "invalid space operation\n");
                break;
            case STACK_ERR:
                fprintf(stdout, "invalid stack operation\n");
                break;
            case MACHINE_CODE_ERR:
                fprintf(stdout, "invalid machine code\n");
                break;
            default:
                fprintf(stdout, "undefined error\n");
                break;
        }
    }
}

class Register{
    public:
    int id = -1;
    Register(){this->id = -1;}
    Register(int id){this->id = id;}
};

class Memory{
    public:
    int id = -1, addr = -1;
    Memory(){
        this->id = -1;
        this->addr = -1;
    }
    Memory(int id){
        this->id = id;
        this->addr = id * 4;
    }
};

class Constant{
    public:
    int id = -1;
    Constant(){this->id = -1;}
    Constant(int id){this->id = id;}
};

class Space{
    public:
    typedef enum{REG, MEM, CONST, UNDEFINED} TYPE;

    Space::TYPE type = Space::TYPE::UNDEFINED;
    int id = -1, addr = -1;
    Register reg;
    Memory mem;
    Constant constant;

    Space(Register x){
        this->type = Space::TYPE::REG;
        this->id = x.id;
        this->reg = x;
    }

    Space(Memory x){
        this->type = Space::TYPE::MEM;
        this->id = x.id;
        this->addr = x.addr;
        this->mem = x;
    }
    Space(Constant x){
        this->type = Space::TYPE::CONST;
        this->id = x.id;
        this->constant = x;
    }

    Space(Space::TYPE type, int id){
        this->type = type;
        this->id = id;
        switch(type){
            case Space::TYPE::REG:
                this->reg = Register(id);
            break;
            case Space::TYPE::MEM:
                this->mem = Memory(id);
            break;
            case Space::TYPE::CONST:
                this->constant = Constant(id);
            break;
            default:
                code_gen_error(SPACE_ERR, "invalid constructor argument type '%d' for space", type);
            break;
        }
    }
};

class ISA{
    private:
    std::vector<std::string> instructions;
    const std::string reg_prefix = std::string("r"), mem_prefix = std::string("["), mem_postfix = std::string("]"), mid = std::string(", ");

    std::string reg_code(const Register reg){
        return this->reg_prefix + std::to_string(reg.id);
    }

    std::string mem_code(const Memory mem){
        return this->mem_prefix + std::to_string(mem.addr) + this->mem_postfix;
    }

    std::string const_code(const Constant constant){
        return std::to_string(constant.id);
    }

    std::string unit_code(const Space space){
        switch(space.type){
            case Space::TYPE::REG:
                return this->reg_code(space.reg);
            break;
            case Space::TYPE::MEM:
                return this->mem_code(space.mem);
            break;
            case Space::TYPE::CONST:
                return this->const_code(space.constant);
            break;
            default:
                code_gen_error(ISA_ERR, "invalid space type: '%d'", space.type);
                return this->const_code(Constant(-1));
            break;
        }
    }

    std::string arithm_code(const char *op, const Register reg0, const Register reg1){
        return std::string(op) + std::string(" ") + std::to_string(reg0.id) + std::string(", ") + std::to_string(reg0.id);
    }

    std::string move_code(const Space space0, const Space space1){
        return std::string("MOV ") + this->unit_code(space0) + std::string(", ") + this->unit_code(space1);
    }

    void append_instruction(std::string instr){
        std::cout << instr << std::endl;
        this->instructions.push_back(instr);
    }

    public:
    typedef enum{ADD, SUB, MUL, DIV, AND, OR, XOR, EX_SUCC, EX_ERR} OP;

    ISA(){
        this->instructions = std::vector<std::string>();
    }

    void move(Register dest, Register src){
        this->append_instruction(this->move_code(Space(dest), Space(src)));
    }

    void move(Register dest, Constant src){
        this->append_instruction(this->move_code(Space(dest), Space(src)));
    }

    void move(Register dest, Memory src){
        this->append_instruction(this->move_code(Space(dest), Space(src)));
    }

    void move(Memory dest, Register src){
        this->append_instruction(this->move_code(Space(dest), Space(src)));
    }

    void arithmetic(ISA::OP op, Register reg0, Register reg1){
        std::string instr;
        switch(op){
            case ADD:
                instr = this->arithm_code("ADD", reg0, reg1);
                break;
            case SUB:
                instr = this->arithm_code("SUB", reg0, reg1);
                break;
            case MUL:
                instr = this->arithm_code("MUL", reg0, reg1);
                break;
            case DIV:
                instr = this->arithm_code("DIV", reg0, reg1);
                break;
            case AND:
                instr = this->arithm_code("AND", reg0, reg1);
                break;
            case OR:
                instr = this->arithm_code("OR", reg0, reg1);
                break;
            case XOR:
                instr = this->arithm_code("XOR", reg0, reg1);
                break;
            default:
                code_gen_error(ISA_ERR, "invalid arithmetic code: '%d'", op);
                break;
        }
        this->append_instruction(instr);
    }

    void exit(ISA::OP op){
        std::string instr;
        switch (op){
        case EX_SUCC:
            instr = std::string("EXIT 0");
            break;
        case EX_ERR:
            instr = std::string("EXIT 1");
            break;
        default:
            code_gen_error(ISA_ERR, "invalid exit code: '%d'", op);
            break;
        }
        this->append_instruction(instr);
    }

    void print_instrs(){
        for(int i = 0; i < this->instructions.size(); i++){
            // printf("%s\n", this->instructions.at(i));
            std::cout << this->instructions.at(i) << std::endl;
        }
    }
};

class VirtualStack{
    private:
    int reg_start = -1, reg_end = -1, mem_start = -1;
    int reg_stack_size = 0;
    int reg_stack_ptr = -1, mem_stack_ptr = -1, current_stack_size = 0;

    Register reg_push(){
        Register res = Register(this->reg_start - this->current_stack_size);
        this->current_stack_size++;
        return res;
    }

    Memory mem_push(){
        Memory res = Memory(this->mem_start - (this->current_stack_size - this->reg_stack_size));
        this->current_stack_size++;
        return res;
    }

    Register reg_pop(){
        Register res = Register(this->reg_start - this->current_stack_size + 1);
        this->current_stack_size--;
        return res;
    }

    Memory mem_pop(){
        Memory res = Memory(this->mem_start - (this->current_stack_size - this->reg_stack_size) + 1);
        this->current_stack_size--;
        return res;
    }

    public:
    VirtualStack(){
        // the stack grows from high address to low address
        this->reg_start = -1;
        this->reg_end = -1;
        this->mem_start = -1;

        this->reg_stack_ptr = -1;
        this->mem_stack_ptr = -1;

        this->reg_stack_size = 0;
        this->current_stack_size = 0;
    }

    VirtualStack(int reg_start, int reg_end, int mem_start){
        // the stack grows from high address to low address
        this->reg_start = reg_start;
        this->reg_end = reg_end;
        this->mem_start = mem_start;

        this->reg_stack_ptr = reg_start;
        this->mem_stack_ptr = mem_start;

        this->reg_stack_size = reg_start - reg_end + 1;
        this->current_stack_size = 0;
    }

    Space push(){
        if(this->current_stack_size < this->reg_stack_size){
            return Space(this->reg_push());
        }
        return Space(this->mem_push());
    }

    Space pop(){
        if(this->current_stack_size <= 0){
            code_gen_error(STACK_ERR, "invalid pop stack with stack size '%d' <= 0", this->current_stack_size);
            return Space(Space::REG, -1);
        }else if(this->current_stack_size <= this->reg_stack_size){
            return Space(this->reg_pop());
        }
        return Space(this->mem_pop());
    }
};

class MachineCode{
    private:
    VirtualStack vstack;
    ISA isa = ISA();
    std::vector<std::string> var_table;

    Memory find_symbol(std::string symbol){
        for(int i = 0; i < this->var_table.size(); i++){
            if(symbol == this->var_table.at(i)){
                return Memory(i);
            }
        }
        code_gen_error(MACHINE_CODE_ERR, "required symbol '%s' not found", symbol.data());
        return Memory(-1);
    }

    public:
    const Register TARGET_DEST_REG = Register(0);
    const Register TARGET_SRC_REG = Register(1);

    MachineCode(){
        this->vstack = VirtualStack();
        // this->isa = ISA();
    }
    MachineCode(int reg_start, int reg_end, int mem_start){
        this->vstack = VirtualStack(reg_start, reg_end, mem_start);
        // this->isa = ISA();
    }

    Memory add_symbol(char *symbol){
        this->var_table.push_back(std::string(symbol));
        return Memory(this->var_table.size() - 1);
    }

    Memory add_access_symbol(char *symbol){
        for(int i = 0; i < this->var_table.size(); i++){
            return Memory(i);
        }
        return this->add_symbol(symbol);
    }

    void move(Space dest, Space src){
        if(dest.type == Space::TYPE::REG){
            switch(src.type){
                case Space::TYPE::CONST:
                    isa.move(dest.reg, src.constant);
                break;
                case Space::TYPE::REG:
                    isa.move(dest.reg, src.reg);
                break;
                case Space::TYPE::MEM:
                    isa.move(dest.reg, src.mem);
                break;
                default:
                    code_gen_error(MACHINE_CODE_ERR, "invalid move source('%d') type", src.type);
                break;
            }
        }else if(dest.type == Space::TYPE::MEM){
            switch(src.type){
                case Space::TYPE::CONST:
                    isa.move(this->TARGET_DEST_REG, src.constant);
                    isa.move(dest.mem, this->TARGET_DEST_REG);
                break;
                case Space::TYPE::REG:
                    isa.move(dest.mem, src.reg);
                break;
                case Space::TYPE::MEM:
                    isa.move(this->TARGET_DEST_REG, src.mem);
                    isa.move(dest.mem, this->TARGET_DEST_REG);
                break;
                default:
                    code_gen_error(MACHINE_CODE_ERR, "invalid move source('%d') type", src.type);
                break;
            }
        }else{
            code_gen_error(MACHINE_CODE_ERR, "invalid move destination('%d') type", dest.type);
        }
    }

    void push(Space src){
        Space dest = this->vstack.push();
        // @TODO: Adapt to various stack push
        this->move(dest, src);
    }

    void pop(Space dest){
        Space src = this->vstack.pop();
        // @TODO: Adapt to various stack pop
        this->move(dest, src);
    }

    void arithmetic(ISA::OP op){
        Space src = this->vstack.pop();
        Space dest = this->vstack.pop();
        this->vstack.push();

        if(dest.type == Space::REG && src.type == Space::REG){
            isa.arithmetic(op, dest.reg, src.reg);
        }else if(dest.type == Space::MEM && src.type == Space::MEM){
            this->move(Space(this->TARGET_DEST_REG), dest);
            this->move(Space(this->TARGET_SRC_REG), src);
            isa.arithmetic(op, this->TARGET_DEST_REG, this->TARGET_SRC_REG);
            this->move(dest, Space(this->TARGET_DEST_REG));
        }else if(dest.type == Space::REG && src.type == Space::MEM){
            this->move(Space(this->TARGET_SRC_REG), src);
            isa.arithmetic(op, this->TARGET_DEST_REG, this->TARGET_SRC_REG);
            // isa.move(dest, this->TARGET_DEST_REG);
        }else if(dest.type == Space::MEM && src.type == Space::REG){
            this->move(Space(this->TARGET_DEST_REG), dest);
            isa.arithmetic(op, this->TARGET_DEST_REG, src.reg);
            this->move(dest, Space(this->TARGET_DEST_REG));
        }else{
            code_gen_error(MACHINE_CODE_ERR, "invalid arithmetic destination('%d') type or source('%d')", dest.type, src.type);
        }
    }

    int code_gen(BTNode *root){
        int retval = 0, lv = 0, rv = 0;

        if (root != NULL) {
            switch (root->data) {
                case ID:
                    this->push(Space(this->add_access_symbol(root->lexeme)));
                    retval = getval(root->lexeme);
                    break;
                case INT:
                    this->push(Space(Constant(atoi(root->lexeme))));
                    retval = atoi(root->lexeme);
                    break;
                case ASSIGN:
                    rv = evaluateTree(root->right);
                    this->pop(Space(this->add_access_symbol(root->left->lexeme)));
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
                        this->arithmetic(ISA::OP::ADD);
                        retval = lv + rv;
                    } else if (strcmp(root->lexeme, "-") == 0) {
                        this->arithmetic(ISA::OP::SUB);
                        retval = lv - rv;
                    } else if (strcmp(root->lexeme, "*") == 0) {
                        this->arithmetic(ISA::OP::MUL);
                        retval = lv * rv;
                    } else if (strcmp(root->lexeme, "/") == 0) {
                        if (rv == 0)
                            error(DIVZERO);
                        this->arithmetic(ISA::OP::DIV);
                        retval = lv / rv;
                    }
                    break;
                default:
                    retval = 0;
            }
        }
        return retval;
    }
};

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

void parse_statement(){
    BTNode *retp = statement();
    if(DEBUG){
        visualize_AST(retp);
    }
    MachineCode mc = MachineCode(7, 0, 64);
    printf(">> %d\n", mc.code_gen(retp));
    printf("Prefix traversal: ");
    printPrefix(retp);
    printf("\n===================\n");
    freeTree(retp);
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
        parse_statement();
    }
    return 0;
}
