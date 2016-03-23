# include "picl-parser.h"

struct PiclTokenStack *PiclTokenStack_new()
{
    struct PiclTokenStack *picl_token_stack = malloc(sizeof(struct PiclTokenStack));
    picl_token_stack->index = 0;
    return picl_token_stack;
}

bool PiclTokenStack_push(struct PiclTokenStack *stack, struct PiclToken *picl_token)
{
    if (stack->index < PICL_TOKEN_STACK_DATA_SIZE) {
        stack->data[stack->index++] = picl_token;
        return true;
    } else {
        return false;
    }
}

bool PiclTokenStack_pop(struct PiclTokenStack *stack, struct PiclToken **result)
{
    if (stack->index > 0) {
        *result = stack->data[--stack->index];
        return true;
    } else {
        return false;
    }
}
bool PiclTokenStack_is_empty(struct PiclTokenStack *stack)
{
    return stack->index == 0;
}

struct PiclToken *PiclToken_new()
{
    return malloc(sizeof(struct PiclToken));
}

struct PiclToken *str_to_picl_token(struct PiclDriver *picl_driver, int token_type, struct PiclStr *sval, struct PiclStr *name)
{
    struct PiclToken *newNode = PiclToken_new();
    newNode->line = picl_driver->line;
    newNode->column = picl_driver->column;
    newNode->token_type = token_type;
    newNode->ival = 0;
    newNode->sval = sval;
    newNode->name = name;
    return newNode;
}

struct PiclToken *token_type_to_picl_token(struct PiclDriver *picl_driver, int token_type, struct PiclStr *name)
{
    struct PiclToken *newNode = PiclToken_new();
    newNode->line = picl_driver->line;
    newNode->column = picl_driver->column;
    newNode->token_type = token_type;
    newNode->ival = 0;
    newNode->sval = NULL;
    newNode->name = name;
    return newNode;
}

struct PiclToken *int_to_picl_token(struct PiclDriver *picl_driver, int token_type, PiclInt ival, struct PiclStr *name)
{
    struct PiclToken *newNode = PiclToken_new();
    newNode->line = picl_driver->line;
    newNode->column = picl_driver->column;
    newNode->token_type = token_type;
    newNode->ival = ival;
    newNode->sval = NULL;
    newNode->name = name;
    return newNode;
}
struct PiclToken *const_to_picl_token(struct PiclDriver *picl_driver, int token_type, const char *name)
{
    struct PiclToken *newNode = PiclToken_new();
    newNode->line = picl_driver->line;
    newNode->column = picl_driver->column;
    newNode->token_type = token_type;
    newNode->ival = 0;
    newNode->sval = NULL;
    newNode->name = PiclStr_newByConst(name);
    return newNode;
}

bool is_new_line(struct PiclToken *picl_token);
bool is_infix_expr(struct PiclDriver *picl_driver, struct PiclToken *picl_token);

void scan_begin(struct PiclDriver *picl_driver);
void scan_end(struct PiclDriver *picl_driver);

int lex(struct PiclDriver *picl_driver, YYSTYPE *lvalp, YYLTYPE *llocp);
int set_token_value(struct PiclToken *picl_token, YYSTYPE *lvalp, YYLTYPE *llocp, bool trace_scanning);


bool in_round_bracket(struct PiclDriver *picl_driver);
bool in_str_join(struct PiclDriver *picl_driver);
struct PiclToken *get_token(struct PiclDriver *picl_driver, bool pass_new_line);
struct PiclToken *read_token(struct PiclDriver *picl_driver);
struct PiclToken *get_num_token(struct PiclDriver *picl_driver);
struct PiclToken *get_str_token(struct PiclDriver *picl_driver, bool continuous);
struct PiclToken *get_here_doc(struct PiclDriver *picl_driver, int hereDocStartLength);
struct PiclToken *get_alfa_token(struct PiclDriver *picl_driver);
struct PiclToken *lex_nomal_return(struct PiclDriver *picl_driver, int value);

int yylex(YYSTYPE *lvalp, YYLTYPE *llocp, struct PiclDriver *picl_driver)
{
    return lex(picl_driver, lvalp, llocp);
}
void yyerror(YYLTYPE *llocp, struct PiclDriver *picl_driver, char const *msg)
{
    printf("line %i,%i : %s\n", llocp->first_line, llocp->first_column, msg);
}

int get_char(struct PiclDriver *picl_driver)
{
    int c = fgetc(picl_driver->yyin);
    if (c != -1){
        picl_driver->column++;
    }
    return c;
}
void unget_char(int c, struct PiclDriver *picl_driver)
{
    ungetc(c, picl_driver->yyin);
    if (c != -1){
        picl_driver->column--;
    }
}

bool is_alfa(char c)
{
    return ('a' <= c && c<= 'z') || ('A' <= c && c <= 'Z') || c == '_';
}
bool is_alfa_next(char c)
{
    return ('a' <= c && c<= 'z') || ('A' <= c && c <= 'Z') || c == '_' || ('0' <= c && c <= '9');
}
bool is_number(char c)
{
    return '0' <= c && c <= '9';
}

bool is_new_line(struct PiclToken *picl_token)
{
    return picl_token->token_type == T_NEWLINE;
}

bool ignore_next_new_line(struct PiclDriver *picl_driver, struct PiclToken *picl_token)
{
    switch(picl_token->token_type){
        case '(' :
        case '[' :
        case '{' :
        case T_IF :
        case T_WHILE :
        case T_CASE :
            return true;
        default :
            return is_infix_expr(picl_driver, picl_token);
        }
}
bool ignore_prev_new_line(struct PiclDriver *picl_driver, struct PiclToken *picl_token)
{
    switch(picl_token->token_type){
        case ')' :
        case ']' :
        case '}' :
        case T_END :
        case T_WHEN :
            return true;
        default :
            return is_infix_expr(picl_driver, picl_token);
        }
}

bool is_infix_expr(struct PiclDriver *picl_driver, struct PiclToken *picl_token)
{
    switch(picl_token->token_type){
        case '+' :
        case '-' :
        case '*' :
        case '/' :
        case '%' :
            return in_round_bracket(picl_driver);

        case DOUBLE_EQUAL :
        case NOT_EQUAL :
        case GT_EQUAL :
        case LT_EQUAL :
        case '>' :
        case '<' :

        case T_THEN :
        case T_ELSE :
        case T_EACH :
        case T_MAP :
        case T_REDUCE :
        case T_FILTER :

        case '|' :
        case DOUBLE_ANB :
        case DOUBLE_PIPE :

        case T_AND :
        case T_OR :
        case T_NOT :

        case T_ASSIGN :
        case T_MOVE :
        case ':' :
        case ',' :
        case '.' :

        case '^' :
        case '$' :

        case T_ARROW :

        case '=' :
            return true;
        default :
            return false;
    }
}

struct PiclToken *lex_nomal_return(struct PiclDriver *picl_driver, int value)
{
    return token_type_to_picl_token(picl_driver, value, PiclStr_newByInt(value));
}

bool in_round_bracket(struct PiclDriver *picl_driver)
{
    return picl_driver->in_round_bracket_count != 0;
}

bool in_str_join(struct PiclDriver *picl_driver)
{
    return picl_driver->in_str_join == true;
}

/*
    後の改行
        中置演算子  無視する
        ([{　      無視する
    前の改行
        中置演算子  無視する
        )]}　      無視する
*/

int lex(struct PiclDriver *picl_driver, YYSTYPE *lvalp, YYLTYPE *llocp)
{
    struct PiclToken *token = get_token(picl_driver, false); // 通常

    if(is_new_line(token)){
        struct PiclToken *token2 = get_token(picl_driver, true); // 改行飛ばし
        if(ignore_prev_new_line(picl_driver, token2)){
            PiclTokenStack_push(picl_driver->token_cache, token2);
            return lex(picl_driver, lvalp, llocp);
        }
        else{
            PiclTokenStack_push(picl_driver->token_cache, token2);
            return set_token_value(token, lvalp, llocp, picl_driver->trace_scanning);
        }
    }

    if(ignore_next_new_line(picl_driver, token)){
        // 先読みをして改行を消す
        PiclTokenStack_push(picl_driver->token_cache, get_token(picl_driver, true));
    }
    return set_token_value(token, lvalp, llocp, picl_driver->trace_scanning);
}

int set_token_value(struct PiclToken *picl_token, YYSTYPE *lvalp, YYLTYPE *llocp, bool trace_scanning)
{
    if(picl_token->sval != NULL){
        lvalp->sval = picl_token->sval;
    }
    else{
        lvalp->ival = picl_token->ival;
    }
    llocp->first_line = picl_token->line;
    llocp->first_column = picl_token->column;
    if(trace_scanning){
        printf("%s\n", picl_token->name->value);
    }
    return picl_token->token_type;
}

void skip_line_comment(struct PiclDriver *picl_driver)
{
    int c = fgetc(picl_driver->yyin);
    while(c != -1){
        if(c == '\r' || c == '\n'){
            unget_char(c, picl_driver);
            break;
        }
        c = fgetc(picl_driver->yyin);
    }
}
void skip_comment(struct PiclDriver *picl_driver)
{
    int c = fgetc(picl_driver->yyin);
    while(c != -1){
        if(c == '\r' || c == '\n'){
            picl_driver->line++;
            picl_driver->column = 1;
        }
        else if(c == '*'){
            int c2 = get_char(picl_driver);
            if(c2 == '/'){
                break;
            }
        }
        c = fgetc(picl_driver->yyin);
    }
}

struct PiclToken *get_token(struct PiclDriver *picl_driver, bool pass_new_line)
{
    struct PiclToken *token = NULL;
    if(PiclTokenStack_is_empty(picl_driver->token_cache) == false){
        PiclTokenStack_pop(picl_driver->token_cache, &token);
    }
    else{
        token = read_token(picl_driver);
    }

    if(pass_new_line && is_new_line(token)){
        return get_token(picl_driver, pass_new_line);
    }
    else{
        return token;
    }
}

struct PiclToken *get_num_token(struct PiclDriver *picl_driver)
{
    int c = get_char(picl_driver);
    if(is_number(c) == false){
        unget_char(c, picl_driver);
        return 0;
    }

    PiclStrBuf_init(picl_driver->strbuf);
    do{
        PiclStrBuf_append(picl_driver->strbuf, (char)c);
        c = get_char(picl_driver);
    }
    while (c != -1 && is_number(c));

    unget_char(c, picl_driver);

    PiclInt ival;
    struct PiclStr *sval;
    PiclStrBuf_toInt(picl_driver->strbuf, &sval, &ival);

    return int_to_picl_token(picl_driver, LONG_LITERAL, ival, sval);
}

struct PiclToken *get_str_token(struct PiclDriver *picl_driver, bool continuous)
{
    int c;
    int c2;
    struct PiclStr *sval;

    if(continuous == false){
        int c = get_char(picl_driver);
        if(c != '"'){
            unget_char(c, picl_driver);
            return 0;
        }
    }

    PiclStrBuf_init(picl_driver->strbuf);
    c = get_char(picl_driver);
    while(c != -1 && c != '"'){
        if(c == '\r' || c == '\n'){
            picl_driver->line++;
            picl_driver->column = 1;
        }
        if(c == '\\'){
            c = get_char(picl_driver);
            switch(c){
                case 'b':
                    PiclStrBuf_append(picl_driver->strbuf, '\b');
                    break;
                case 't':
                    PiclStrBuf_append(picl_driver->strbuf, '\t');
                    break;
                case 'n':
                    PiclStrBuf_append(picl_driver->strbuf, '\n');
                    break;
                case 'f':
                    PiclStrBuf_append(picl_driver->strbuf, '\f');
                    break;
                case 'r':
                    PiclStrBuf_append(picl_driver->strbuf, '\r');
                    break;
                case '"':
                    PiclStrBuf_append(picl_driver->strbuf, '\"');
                    break;
                case '\'':
                    PiclStrBuf_append(picl_driver->strbuf, '\'');
                    break;
                case '\\':
                    PiclStrBuf_append(picl_driver->strbuf, '\\');
                    break;
                default:
                    PiclStrBuf_append(picl_driver->strbuf, (char)c);
            }
        }
        else if(c == '$'){
            c2 = get_char(picl_driver);
            if(c2 == '{'){
                picl_driver->in_str_join = true;

                if(PiclStrBuf_isEmpty(picl_driver->strbuf)){
                    if(continuous){
                        return lex_nomal_return(picl_driver, '&');
                    }
                    else{
                        return read_token(picl_driver);
                    }
                }
                else{
                    PiclStrBuf_toStr(picl_driver->strbuf, &sval);

                    PiclTokenStack_push(picl_driver->token_cache, lex_nomal_return(picl_driver, '&'));

                    if(continuous){
                        PiclTokenStack_push(picl_driver->token_cache, str_to_picl_token(picl_driver, STRING_LITERAL, sval, sval));
                        return lex_nomal_return(picl_driver, '&');
                    }
                    else{
                        return str_to_picl_token(picl_driver, STRING_LITERAL, sval, sval);
                    }
                }
            }
            else{
                unget_char(c2, picl_driver);
                PiclStrBuf_append(picl_driver->strbuf, (char)c);
            }
        }
        else{
            PiclStrBuf_append(picl_driver->strbuf, (char)c);
        }
        c = get_char(picl_driver);
    }

    if(continuous){
        if(PiclStrBuf_isEmpty(picl_driver->strbuf)){
            return read_token(picl_driver);
        }
        else{
            PiclStrBuf_toStr(picl_driver->strbuf, &sval);

            PiclTokenStack_push(picl_driver->token_cache, str_to_picl_token(picl_driver, STRING_LITERAL, sval, sval));
            return lex_nomal_return(picl_driver, '&');
        }
    }
    else{
        PiclStrBuf_toStr(picl_driver->strbuf, &sval);

        return str_to_picl_token(picl_driver, STRING_LITERAL, sval, sval);
    }
}

struct PiclToken *get_here_doc(struct PiclDriver *picl_driver, int here_doc_start_length)
{
    int c = 0;
    int count_under_score = 0;
    bool hit_quate = false;
    int count = 0;

    PiclStrBuf_init(picl_driver->strbuf);

    while ((c = get_char(picl_driver)) != -1){
        if(c == '_' && hit_quate){
            count_under_score++;
        }
        if(count_under_score == here_doc_start_length){

            struct PiclStr *all_str;
            PiclStrBuf_toStr(picl_driver->strbuf, &all_str);
            struct PiclStr *sval = PiclStr_substr(all_str, all_str->length - here_doc_start_length);

            return str_to_picl_token(picl_driver, STRING_LITERAL, sval, sval);
        }
        if(c == '\''){
            hit_quate= true;
            count_under_score = 0;
        }
        if(c == '\r' || c == '\n'){
            picl_driver->line++;
            picl_driver->column = 1;
        }
        PiclStrBuf_append(picl_driver->strbuf, (char)c);
        count++;
        if(count > HERE_DOC_CHAR_LIMIT){
            // throw "over here document char size limit"; 
            return NULL;
        }
    }
    // throw "picl internal exeption"; 
    return NULL;
}

struct PiclToken *get_alfa_token(struct PiclDriver *picl_driver)
{
    int c = get_char(picl_driver);
    if(is_alfa(c) == false){
        unget_char(c, picl_driver);
        return 0;
    }

    PiclStrBuf_init(picl_driver->strbuf);

    bool under_score_only = false;
    if(c == '_'){
        under_score_only = true;
    }
    do{
        if(c == '_'){
            under_score_only &= true;
        }
        else{
            under_score_only = false;
        }
        PiclStrBuf_append(picl_driver->strbuf, (char)c);
        c = get_char(picl_driver);
    }
    while (c != -1 && is_alfa_next(c));

    struct PiclStr *sval;
    PiclStrBuf_toStr(picl_driver->strbuf, &sval);

    if(c == '\'' && under_score_only == true){
        return get_here_doc(picl_driver, sval->length);
    }

    if(c == ':'){
        return str_to_picl_token(picl_driver, DICT_IDENT, sval, sval);
    }

    unget_char(c, picl_driver);

    if(PiclStr_equalsConst(sval, "seq")){
        return const_to_picl_token(picl_driver, T_SEQ, "T_SEQ");
    }
    if(PiclStr_equalsConst(sval, "fun")){
        return const_to_picl_token(picl_driver, T_FUN, "T_FUN");
    }
    if(PiclStr_equalsConst(sval, "def")){
        return const_to_picl_token(picl_driver, T_DEF, "T_DEF");
    }
    if(PiclStr_equalsConst(sval, "cla")){
        return const_to_picl_token(picl_driver, T_CLA, "T_CLA");
    }
    if(PiclStr_equalsConst(sval, "beh")){
        return const_to_picl_token(picl_driver, T_BEH, "T_BEH");
    }

    if(PiclStr_equalsConst(sval, "pub")){
        return const_to_picl_token(picl_driver, T_PUB, "T_PUB");
    }
    if(PiclStr_equalsConst(sval, "pri")){
        return const_to_picl_token(picl_driver, T_PRI, "T_PRI");
    }
    if(PiclStr_equalsConst(sval, "dyn")){
        return const_to_picl_token(picl_driver, T_DYN, "T_DYN");
    }
    if(PiclStr_equalsConst(sval, "ali")){
        return const_to_picl_token(picl_driver, T_ALI, "T_ALI");
    }
    if(PiclStr_equalsConst(sval, "catch")){
        return const_to_picl_token(picl_driver, T_CATCH, "T_CATCH");
    }
    if(PiclStr_equalsConst(sval, "redef")){
        return const_to_picl_token(picl_driver, T_REDEF, "T_REDEF");
    }
    if(PiclStr_equalsConst(sval, "aft")){
        return const_to_picl_token(picl_driver, T_AFT, "T_AFT");
    }
    if(PiclStr_equalsConst(sval, "bef")){
        return const_to_picl_token(picl_driver, T_BEF, "T_BEF");
    }

    if(PiclStr_equalsConst(sval, "let")){
        return const_to_picl_token(picl_driver, T_LET, "T_LET");
    }
    if(PiclStr_equalsConst(sval, "fin")){
        return const_to_picl_token(picl_driver, T_FIN, "T_FIN");
    }

    if(PiclStr_equalsConst(sval, "and")){
        return const_to_picl_token(picl_driver, T_AND, "T_AND");
    }
    if(PiclStr_equalsConst(sval, "or")){
        return const_to_picl_token(picl_driver, T_OR, "T_OR");
    }
    if(PiclStr_equalsConst(sval, "not")){
        return const_to_picl_token(picl_driver, T_NOT, "T_NOT");
    }

    if(PiclStr_equalsConst(sval, "return")){
        return const_to_picl_token(picl_driver, T_RETURN, "T_RETURN");
    }
    if(PiclStr_equalsConst(sval, "throw")){
        return const_to_picl_token(picl_driver, T_THROW, "T_THROW");
    }
    if(PiclStr_equalsConst(sval, "break")){
        return const_to_picl_token(picl_driver, T_BREAK, "T_BREAK");
    }
    if(PiclStr_equalsConst(sval, "continue")){
        return const_to_picl_token(picl_driver, T_CONTINUE, "T_CONTINUE");
    }
    if(PiclStr_equalsConst(sval, "end")){
        return const_to_picl_token(picl_driver, T_END, "T_END");
    }
    if(PiclStr_equalsConst(sval, "if")){
        return const_to_picl_token(picl_driver, T_IF, "T_IF");
    }
    if(PiclStr_equalsConst(sval, "then")){
        return const_to_picl_token(picl_driver, T_THEN, "T_THEN");
    }
    if(PiclStr_equalsConst(sval, "else")){
        return const_to_picl_token(picl_driver, T_ELSE, "T_ELSE");
    }
    if(PiclStr_equalsConst(sval, "while")){
        return const_to_picl_token(picl_driver, T_WHILE, "T_WHILE");
    }
    if(PiclStr_equalsConst(sval, "do")){
        return const_to_picl_token(picl_driver, T_DO, "T_DO");
    }
    if(PiclStr_equalsConst(sval, "for")){
        return const_to_picl_token(picl_driver, T_WHEN, "T_FOR");
    }
    if(PiclStr_equalsConst(sval, "that")){
        return const_to_picl_token(picl_driver, T_THAT, "T_THAT");
    }
    if(PiclStr_equalsConst(sval, "case")){
        return const_to_picl_token(picl_driver, T_CASE, "T_CASE");
    }
    if(PiclStr_equalsConst(sval, "when")){
        return const_to_picl_token(picl_driver, T_WHEN, "T_WHEN");
    }
    if(PiclStr_equalsConst(sval, "each")){
        return const_to_picl_token(picl_driver, T_EACH, "T_EACH");
    }
    if(PiclStr_equalsConst(sval, "map")){
        return const_to_picl_token(picl_driver, T_MAP, "T_MAP");
    }
    if(PiclStr_equalsConst(sval, "reduce")){
        return const_to_picl_token(picl_driver, T_REDUCE, "T_REDUCE");
    }
    if(PiclStr_equalsConst(sval, "filter")){
        return const_to_picl_token(picl_driver, T_FILTER, "T_FILTER");
    }


    if(PiclStr_equalsConst(sval, "echo")){
        return const_to_picl_token(picl_driver, T_ECHO, "T_ECHO");
    }
    return str_to_picl_token(picl_driver, IDENT, sval, sval);
}

struct PiclToken *read_token(struct PiclDriver *picl_driver)
{
    int c;
    int c2;
    int c3;
    while((c = get_char(picl_driver)) != EOF){
        switch(c){
            case '=' :{
                c2 = get_char(picl_driver);
                if(c2 == '='){
                    return const_to_picl_token(picl_driver, DOUBLE_EQUAL, "DOUBLE_EQUAL");
                }
                else{
                    unget_char(c2, picl_driver);
                    return lex_nomal_return(picl_driver, c);
                }
            }
            case '!' :{
                c2 = get_char(picl_driver);
                if(c2 == '='){
                    return const_to_picl_token(picl_driver, NOT_EQUAL, "NOT_EQUAL");
                }
                else{
                    unget_char(c2, picl_driver);
                    return lex_nomal_return(picl_driver, c);
                }
            }
            case '>' :{
                c2 = get_char(picl_driver);
                if(c2 == '='){
                    return const_to_picl_token(picl_driver, GT_EQUAL, "GT_EQUAL");
                }
                else if(c2 == '>'){
                    return const_to_picl_token(picl_driver, T_MOVE, "T_MOVE");
                }
                else{
                    unget_char(c2, picl_driver);
                    return lex_nomal_return(picl_driver, c);
                }
            }
            case '<' :{
                c2 = get_char(picl_driver);
                if(c2 == '='){
                    c3 = get_char(picl_driver);
                    if(c3 == '>'){
                        return const_to_picl_token(picl_driver, COMPARE, "COMPARE");
                    }
                    else{
                        unget_char(c3, picl_driver);
                        return const_to_picl_token(picl_driver, LT_EQUAL, "LT_EQUAL");
                    }
                }
                else if(c2 == '<'){
                    return const_to_picl_token(picl_driver, T_ASSIGN, "T_ASSIGN");
                }
                else{
                    unget_char(c2, picl_driver);
                    return lex_nomal_return(picl_driver, c);
                }
            }
            case '+' :{
                return lex_nomal_return(picl_driver, c);
            }
            case '-' :{
                c2 = get_char(picl_driver);
                if(c2 == '>'){
                    return const_to_picl_token(picl_driver, T_ARROW, "ARROW");
                }
                else{
                    unget_char(c2, picl_driver);
                    return lex_nomal_return(picl_driver, c);
                }
            }
            case '&' :{
                c2 = get_char(picl_driver);
                if(c2 == '&'){
                    return const_to_picl_token(picl_driver, DOUBLE_ANB, "DOUBLE_ANB");
                }
                else{
                    unget_char(c2, picl_driver);
                    return lex_nomal_return(picl_driver, c);
                }
            }
            case '|' :{
                c2 = get_char(picl_driver);
                if(c2 == '|'){
                    return const_to_picl_token(picl_driver, DOUBLE_PIPE, "DOUBLE_PIPE");
                }
                else{
                    unget_char(c2, picl_driver);
                    return lex_nomal_return(picl_driver, c);
                }
            }
            case '*' :{
                return lex_nomal_return(picl_driver, c);
            }
            case '/' :{
                c2 = get_char(picl_driver);
                if(c2 == '/'){
                    skip_line_comment(picl_driver);
                    break;
                }
                else if(c2 == '*'){
                    skip_comment(picl_driver);
                    break;
                }
                else{
                    unget_char(c2, picl_driver);
                    return lex_nomal_return(picl_driver, c);
                }
            }
            case ',' :{
                return lex_nomal_return(picl_driver, c);
            }
            case '(' :{
                picl_driver->in_round_bracket_count++;
                return lex_nomal_return(picl_driver, c);
            }
            case ')' :{
                picl_driver->in_round_bracket_count--;
                return lex_nomal_return(picl_driver, c);
            }
            case '{' :{
                return lex_nomal_return(picl_driver, c);
            }
            case '}' :{
                if(in_str_join(picl_driver)){
                    picl_driver->in_str_join = false;
                    return get_str_token(picl_driver, true);
                }
                else{
                    return lex_nomal_return(picl_driver, c);
                }
            }
            case '[' :{
                picl_driver->in_list_bracket_count++;
                return lex_nomal_return(picl_driver, c);
            }
            case ']' :{
                picl_driver->in_list_bracket_count--;
                return lex_nomal_return(picl_driver, c);
            }
            case '$' :{
                return lex_nomal_return(picl_driver, c);
            }
            case '#' :{
                return lex_nomal_return(picl_driver, c);
            }
            case ':' :{
                return lex_nomal_return(picl_driver, c);
            }
            case '`' :{
                return lex_nomal_return(picl_driver, c);
            }
            case ' ' :
            case '\t' :
                break;
            case '\r' :
            case '\n' :
                picl_driver->line++;
                picl_driver->column = 1;
            case ';' :
                return const_to_picl_token(picl_driver, T_NEWLINE, "T_NEWLINE");
            default :{
                unget_char(c, picl_driver);
                struct PiclToken *token;

                token = get_num_token(picl_driver);
                if(token != NULL) return token;

                token = get_str_token(picl_driver, false);
                if(token != NULL) return token;

                token = get_alfa_token(picl_driver);
                if(token != NULL) return token;

                c = get_char(picl_driver);
                return lex_nomal_return(picl_driver, c);
            }
        }
    }
    return const_to_picl_token(picl_driver, END, "EOF");
}
