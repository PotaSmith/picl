%code requires {
#include <stdio.h>
#include <stdlib.h>
#include "picl-driver.h"
#include "picl-lex.h"
#include "picl-node-build.h"
}
%locations
%define api.pure
%debug
%parse-param {struct PiclDriver *picl_driver}
%lex-param   {struct PiclDriver *picl_driver}
%union {
    PiclInt  ival;
    struct PiclStr *sval;
    struct PiclNode *node;
    struct PiclNodeArray *nodes;
    struct PiclNode_FuncBody *func_body;
    struct PiclNode_FuncHead *func_head;
}
%code {
extern int yylex(YYSTYPE *lvalp, YYLTYPE *llocp, struct PiclDriver *picl_driver);
extern void yyerror(YYLTYPE *llocp, struct PiclDriver *picl_driver, char const *msg);
}
%token        END        0 "end of file"

%token        T_SEQ
%token        T_FUN
%token        T_DEF
%token        T_CLA
%token        T_BEH

%token        T_PUB
%token        T_PRI
%token        T_DYN
%token        T_ALI
%token        T_CATCH
%token        T_REDEF
%token        T_AFT
%token        T_BEF

%token        T_LET
%token        T_FIN

%token        T_RETURN
%token        T_THROW
%token <sval> T_IF
%token <sval> T_THEN
%token <sval> T_ELSE
%token <sval> T_WHILE
%token <sval> T_DO
%token <sval> T_THAT
%token <sval> T_CASE
%token <sval> T_WHEN
%token <sval> T_EACH
%token <sval> T_MAP
%token <sval> T_REDUCE
%token <sval> T_FILTER
%token <sval> T_END
%token        T_BREAK
%token        T_CONTINUE
%token <sval> T_ECHO

%token        T_MINUS


%token        T_ASSIGN
%token        T_MOVE


%token        T_ARROW

%token        T_NEWLINE

%token        DOUBLE_EQUAL
%token        NOT_EQUAL
%token        GT_EQUAL
%token        LT_EQUAL
%token        T_AND
%token        T_OR
%token        T_NOT

%token        DOUBLE_ANB
%token        DOUBLE_PIPE

%token        COMPARE

%token <sval> STRING_LITERAL
%token <sval> IDENT
%token <sval> DICT_IDENT
%token <ival> LONG_LITERAL

%left T_NEWLINE
%right T_ECHO
%right T_RETURN
%right T_THROW
%left T_WHILE
%left T_THEN
%left T_ELSE
%left T_IF
%left T_FOR
%left T_EACH
%left T_MAP
%left T_REDUCE
%left T_FILTER
%left T_CASE
%left T_WHEN
%left '=' T_ASSIGN T_MOVE
%left T_ARROW
%left '|' '&'
%nonassoc DOUBLE_EQUAL NOT_EQUAL '>' '<' GT_EQUAL LT_EQUAL
%left ','
%left '^' '$'
%left COMPARE
%left ':'
%left '+' '-'
%left '/' '*' '%'
%left '`'
%left T_AND T_OR T_NOT
%left NEG
%left '.'
%left '(' '{'

%type  <func_body> func_body
%type  <func_head> func_head catch_head

%type  <nodes> seq_members_nodes cla_members_nodes beh_members_nodes let_decls_nodes
%type  <nodes> without_guard_stmts_nodes when_stmts_nodes stmts_nodes
%type  <nodes> extentions call_func_args call_func_stmts func_def_args func_def_keyword_args

%type  <node> decl func_decl seq_decl def_decl cla_decl beh_decl
%type  <node> seq_member redef_decls redef_decl decl_body decl_value decl_primary cla_member beh_member
%type  <node> field_value alias_value let_decl
%type  <node> stmt list_stmt_chain list_stmt when_stmts when_stmt expr indent_value primary dict_values
%type  <node> arg dict_value arg_def arg_pattern primary_value

%type  <sval> keyword_and_ident

%%
%start top_level;

top_level
  : /* Nothing */ { }
  |           decls { picl_driver->nodes = PiclNodeArray_pop(picl_driver->node_buff_stack); }
  | T_NEWLINE decls { picl_driver->nodes = PiclNodeArray_pop(picl_driver->node_buff_stack); }

new_node_stack /* 空 */
  : { PiclNodeBuff_new(picl_driver->node_buff_stack); }

decls
  : decl       { PiclNodeBuffStack_push(picl_driver->node_buff_stack, $1); }
  | decls decl { PiclNodeBuffStack_push(picl_driver->node_buff_stack, $2); }

decl
  : func_decl
  | seq_decl
  | def_decl
  | cla_decl
  | beh_decl

def_newline
  : T_NEWLINE
  | '='

func_decl
  : T_FUN func_head def_newline func_body { $$ = PiclNode_newFunction($2, $4); }

seq_decl
  : T_SEQ keyword_and_ident extentions def_newline seq_members_nodes { $$ = PiclNode_newClassKind(NodeType_Sequence, $2, $3, $5); }

seq_members_nodes
  : new_node_stack seq_members { $$ = PiclNodeArray_pop(picl_driver->node_buff_stack); }

seq_members
  : seq_member             { PiclNodeBuffStack_push(picl_driver->node_buff_stack, $1); }
  | seq_members seq_member { PiclNodeBuffStack_push(picl_driver->node_buff_stack, $2); }

seq_member
  : cla_member
  | T_CATCH catch_head def_newline func_body { $$ = PiclNode_newCatch($2, $4); }
  | T_REDEF '{' redef_decls '}' { $$ = $3; }

redef_decls
  : redef_decl             { PiclNodeBuffStack_push(picl_driver->node_buff_stack, $1); }
  | redef_decls redef_decl { PiclNodeBuffStack_push(picl_driver->node_buff_stack, $2); }

redef_decl
  : cla_decl
  | beh_decl

def_decl
  : T_DEF keyword_and_ident def_newline decl_body { $$ = PiclNode_newNaming(NodeType_Op_Dot, $2, $4); }

decl_body
  : decl_value                { $$ = $1; }
  | decl_value T_NEWLINE      { $$ = $1; }

decl_value
  : decl_primary              { $$ = $1; }
  | decl_value '|' decl_value { $$ = PiclNode_newBinary(NodeType_Op_Def_Or, $1, $3); }

decl_primary
  : keyword_and_ident          { $$ = PiclNode_newIdent(NodeType_Val_Ident, $1); }
  | primary_value  { $$ = $1; }

cla_decl
  : T_CLA keyword_and_ident extentions def_newline cla_members_nodes { $$ = PiclNode_newClassKind(NodeType_Class, $2, $3, $5); }

extentions
  : { $$ = NULL; }
  | ':' new_node_stack indent_values { $$ = PiclNodeArray_pop(picl_driver->node_buff_stack); }

indent_values
  : indent_value                   { PiclNodeBuffStack_push(picl_driver->node_buff_stack, $1); }
  | indent_values ',' indent_value { PiclNodeBuffStack_push(picl_driver->node_buff_stack, $3); }

cla_members_nodes
  : new_node_stack cla_members { $$ = PiclNodeArray_pop(picl_driver->node_buff_stack); }

cla_members
  : cla_member             { PiclNodeBuffStack_push(picl_driver->node_buff_stack, $1); }
  | cla_members cla_member { PiclNodeBuffStack_push(picl_driver->node_buff_stack, $2); }

cla_member
  : T_PUB keyword_and_ident     T_ASSIGN    field_value { $$ = PiclNode_newField(MemberScope_Public, $2, $4); }
  | T_PRI keyword_and_ident     T_ASSIGN    field_value { $$ = PiclNode_newField(MemberScope_Private, $2, $4); }
  | T_PUB func_head def_newline func_body   { $$ = PiclNode_newMethod(MemberScope_Public, $2, $4); }
  | T_PRI func_head def_newline func_body   { $$ = PiclNode_newMethod(MemberScope_Private, $2, $4); }
  | T_ALI keyword_and_ident '=' alias_value             { $$ = PiclNode_newAlias($2, $4); }


field_value
  : expr T_NEWLINE

alias_value
  : indent_value T_NEWLINE


beh_decl
  : T_BEH keyword_and_ident extentions def_newline beh_members_nodes { $$ = PiclNode_newClassKind(NodeType_Behavior, $2, $3, $5); }

beh_members_nodes
  : new_node_stack beh_members { $$ = PiclNodeArray_pop(picl_driver->node_buff_stack); }

beh_members
  : beh_member             { PiclNodeBuffStack_push(picl_driver->node_buff_stack, $1); }
  | beh_members beh_member { PiclNodeBuffStack_push(picl_driver->node_buff_stack, $2); }

beh_member
  : T_PUB keyword_and_ident T_ASSIGN expr     { $$ = PiclNode_newField(MemberScope_Public, $2, $4); }
  | T_PRI keyword_and_ident T_ASSIGN expr     { $$ = PiclNode_newField(MemberScope_Private, $2, $4); }
  | T_PRI func_head '=' func_body { $$ = PiclNode_newMethod(MemberScope_Private, $2, $4); }

func_body
  : stmts_nodes { $$ = PiclNode_FuncBody_new($1, NULL); }
  | stmts_nodes let_decls_nodes { $$ = PiclNode_FuncBody_new($1, $2); }

let_decls_nodes
  : new_node_stack let_decls { $$ = PiclNodeArray_pop(picl_driver->node_buff_stack); }

let_decls
  : let_decl           { PiclNodeBuffStack_push(picl_driver->node_buff_stack, $1); }
  | let_decls let_decl { PiclNodeBuffStack_push(picl_driver->node_buff_stack, $2); }

let_decl
  : T_LET func_head def_newline stmts_nodes { $$ = PiclNode_newLet($2, $4); }

stmt_newline
  : T_NEWLINE
  | T_ARROW

then_newline
  : T_NEWLINE
  | T_THEN

stmts_nodes
  : new_node_stack stmts { $$ = PiclNodeArray_pop(picl_driver->node_buff_stack); }

stmts
  : stmt_line T_NEWLINE
  | stmt_line
  | guard_stmts

stmt_line
  : stmt_line T_NEWLINE stmt { PiclNodeBuffStack_push(picl_driver->node_buff_stack, $3); }
  | stmt                     { PiclNodeBuffStack_push(picl_driver->node_buff_stack, $1); }

guard_stmts
  : guard_stmt
  | guard_stmts guard_stmt {  }

guard_stmt
  : '|' expr stmt_newline without_guard_stmts_nodes {  }

without_guard_stmts_nodes
  : new_node_stack without_guard_stmts { $$ = PiclNodeArray_pop(picl_driver->node_buff_stack); }

without_guard_stmts
  : without_guard_stmt_line T_NEWLINE
  | without_guard_stmt_line

without_guard_stmt_line
  : without_guard_stmt_line T_NEWLINE stmt { PiclNodeBuffStack_push(picl_driver->node_buff_stack, $3); }
  | stmt                              { PiclNodeBuffStack_push(picl_driver->node_buff_stack, $1); }




do_newline
  : T_NEWLINE
  | T_DO

list_stmt_chain
  : T_FOR expr list_stmt            { $$ = PiclNode_setListStmtCond($3, $2); }
  | list_stmt_chain list_stmt { $$ = PiclNode_setListStmtCond($2, $1); }

list_stmt
  : T_EACH   keyword_and_ident do_newline stmts_nodes      { $$= PiclNode_newOneArgListStmt(NodeType_ListEach, $2, $4); }
  | T_EACH   keyword_and_ident            when_stmts_nodes { $$= PiclNode_newOneArgListStmt(NodeType_ListEachWhen, $2, $3); }
  | T_MAP    keyword_and_ident do_newline stmts_nodes      { $$= PiclNode_newOneArgListStmt(NodeType_ListMap, $2, $4); }
  | T_MAP    keyword_and_ident            when_stmts_nodes { $$= PiclNode_newOneArgListStmt(NodeType_ListMapWhen, $2, $3); }
  | T_FILTER keyword_and_ident do_newline stmts_nodes      { $$= PiclNode_newOneArgListStmt(NodeType_ListFilter, $2, $4); }
  | T_FILTER keyword_and_ident            when_stmts_nodes { $$= PiclNode_newOneArgListStmt(NodeType_ListFilterWhen, $2, $3); }
  | T_REDUCE keyword_and_ident ',' keyword_and_ident do_newline stmts_nodes { $$= PiclNode_newTwoArgListStmt(NodeType_ListReduce, $2, $4, $6); }

stmt
  : expr { $$ = $1; }
  | T_RETURN expr       { $$ = PiclNode_newUnary(NodeType_Stmt_Return_Var, $2); }
  | T_RETURN            { $$ = PiclNode_newAtom(NodeType_Stmt_Return); }
  | T_THROW expr        { $$ = PiclNode_newUnary(NodeType_Stmt_Throw_Var, $2); }
  | T_THROW             { $$ = PiclNode_newAtom(NodeType_Stmt_Throw); }
  | T_BREAK             { $$ = PiclNode_newAtom(NodeType_Stmt_Break); }
  | T_CONTINUE          { $$ = PiclNode_newAtom(NodeType_Stmt_Continue); }
  | T_ECHO expr         { $$ = PiclNode_newUnary(NodeType_Stmt_Echo_Var, $2); }
  | expr T_ASSIGN expr  { $$ = PiclNode_newBinary(NodeType_Op_Assign, $1, $3); }

when_stmts_nodes
  : new_node_stack when_stmts { $$ = PiclNodeArray_pop(picl_driver->node_buff_stack); }

when_stmts
  : when_stmt            { PiclNodeBuffStack_push(picl_driver->node_buff_stack, $1); }
  | when_stmts when_stmt { PiclNodeBuffStack_push(picl_driver->node_buff_stack, $2); }

when_stmt
  : T_WHEN expr stmt_newline stmts_nodes { $$= PiclNode_newCondUnary(NodeType_When, $2, $4); }
  | T_ELSE stmts_nodes                   { $$= PiclNode_newNodes(NodeType_WhenElse, $2); }

expr
  : primary { $$ = $1; }

  | list_stmt_chain T_END   { $$ = $1; }
  | T_IF    expr then_newline stmts_nodes T_END  { $$= PiclNode_newCondUnary(NodeType_If, $2, $4); }
  | T_IF    expr then_newline stmts_nodes T_ELSE stmts_nodes T_END { $$= PiclNode_newCondBinary(NodeType_IfElse, $2, $4, $6); }
  | T_WHILE expr do_newline   stmts_nodes T_END  { $$= PiclNode_newCondUnary(NodeType_While, $2, $4); }
  | T_CASE  expr when_stmts_nodes T_END          { $$= PiclNode_newCondUnary(NodeType_Case, $2, $3); }

  | expr '.' keyword_and_ident  { $$ = PiclNode_newNaming(NodeType_Op_Dot, $3, $1); }

  | expr '(' call_func_args  { $$ = PiclNode_newCallFunc(NodeType_CallFuncArg, $1, $3); }
  | expr '{' call_func_stmts { $$ = PiclNode_newCallFunc(NodeType_CallFuncStmt, $1, $3); }

  | expr '+' expr            { $$ = PiclNode_newBinary(NodeType_Op_Add, $1, $3); }
  | expr '-' expr            { $$ = PiclNode_newBinary(NodeType_Op_Sub, $1, $3); }
  | expr '*' expr            { $$ = PiclNode_newBinary(NodeType_Op_Mul, $1, $3); }
  | expr '/' expr            { $$ = PiclNode_newBinary(NodeType_Op_Div, $1, $3); }
  | expr '%' expr            { $$ = PiclNode_newBinary(NodeType_Op_Mod, $1, $3); }

  | expr T_AND expr          { $$ = PiclNode_newBinary(NodeType_Op_Mod, $1, $3); }
  | expr T_OR  expr          { $$ = PiclNode_newBinary(NodeType_Op_Mod, $1, $3); }
  | expr T_NOT expr          { $$ = PiclNode_newBinary(NodeType_Op_Mod, $1, $3); }

  | expr '^' expr            { $$ = PiclNode_newBinary(NodeType_Op_Mod, $1, $3); }
  | expr '$' expr            { $$ = PiclNode_newBinary(NodeType_Op_Mod, $1, $3); }

  | expr DOUBLE_EQUAL expr   { $$ = PiclNode_newBinary(NodeType_Op_Equal,     $1, $3); }
  | expr NOT_EQUAL    expr   { $$ = PiclNode_newBinary(NodeType_Op_NotEqual, $1, $3); }
  | expr GT_EQUAL     expr   { $$ = PiclNode_newBinary(NodeType_Op_GtEqual,  $1, $3); }
  | expr LT_EQUAL     expr   { $$ = PiclNode_newBinary(NodeType_Op_LtEqual,  $1, $3); }
  | expr '>'          expr   { $$ = PiclNode_newBinary(NodeType_Op_Gt,        $1, $3); }
  | expr '<'          expr   { $$ = PiclNode_newBinary(NodeType_Op_Lt,        $1, $3); }

  | expr '&'          expr   { $$ = PiclNode_newBinary(NodeType_Op_StrJoin,  $1, $3); }

  | expr COMPARE      expr   { $$ = PiclNode_newBinary(NodeType_Op_Compare,  $1, $3); }

  | expr T_MOVE expr         { $$ = PiclNode_newBinary(NodeType_Op_Colon,   $1, $3); }
  | expr ':' expr            { $$ = PiclNode_newBinary(NodeType_Op_Colon,  $1, $3); }

  | expr '`' expr '`' expr   { $$ = PiclNode_newBinary(NodeType_Op_Method, $1, $3); }
  | '-' expr %prec NEG       { $$ = PiclNode_newUnary(NodeType_Op_Minus,    $2); }
  | '&' expr %prec NEG       { $$ = PiclNode_newUnary(NodeType_Op_Minus,    $2); }

indent_value
  : primary { $$ = $1; }
  | indent_value '.' keyword_and_ident { $$ = PiclNode_newNaming(NodeType_Op_Dot, $3, $1); }

primary
  : primary_value          { $$ = $1; }
  | keyword_and_ident      { $$ = PiclNode_newIdent(NodeType_Val_Ident, $1); }
  | '[' ']'                { $$ = PiclNode_newAtom(NodeType_Val_List); }
  | '[' dict_values ']'    { $$ = PiclNode_newUnary(NodeType_Val_Dict_Var, $2); }
  | '(' expr ')'           { $$ = $2; }
  | '{' stmts_nodes '}'    { PiclNode_newNodes(NodeType_Stmts, $2); }

call_func_args
  : ')' { $$ = NULL; }
  | new_node_stack args ')' { $$ = PiclNodeArray_pop(picl_driver->node_buff_stack); }

call_func_stmts
  : '}' { $$ = NULL; }
  | stmts_nodes '}' { $$ = $1; }

args
  : arg           { PiclNodeBuffStack_push(picl_driver->node_buff_stack, $1); }
  | args ',' arg  { PiclNodeBuffStack_push(picl_driver->node_buff_stack, $3); }

arg
  : expr                  { $$ = $1; }
  | '-'                   { $$ = PiclNode_newAtom(NodeType_Stmt_Return); }
  | DICT_IDENT expr       { $$ = PiclNode_newNaming(NodeType_Dict_Arg, $1, $2); }

dict_values
  : dict_value                    { PiclNodeBuffStack_push(picl_driver->node_buff_stack, $1); }
  | dict_values ',' dict_value    { PiclNodeBuffStack_push(picl_driver->node_buff_stack, $3); }

dict_value
  : DICT_IDENT                expr     { $$ = PiclNode_newNaming(NodeType_Val_Var_Dict, $1, $2); }
  | keyword_and_ident ':' expr   { $$ = PiclNode_newNaming(NodeType_Val_Var_Dict, $1, $3); }
  | STRING_LITERAL    ':' expr   { $$ = PiclNode_newNaming(NodeType_Val_Str_Dict, $1, $3); }


func_head
  : keyword_and_ident                                             { $$ = PiclNode_FuncHead_new($1, NULL, NULL); }
  | keyword_and_ident '(' func_def_args                           { $$ = PiclNode_FuncHead_new($1, $3, NULL); }
  | keyword_and_ident '(' func_def_args '{' func_def_keyword_args { $$ = PiclNode_FuncHead_new($1, $3, $5); }

catch_head
  : '(' new_node_stack args_def ')'         { $$ = PiclNode_FuncHead_new(NULL, PiclNodeArray_pop(picl_driver->node_buff_stack), NULL); }
  | keyword_and_ident '(' new_node_stack args_def ')'   { $$ = PiclNode_FuncHead_new($1, PiclNodeArray_pop(picl_driver->node_buff_stack), NULL); }

func_def_args
  : ')' { $$ = NULL; }
  | new_node_stack args_def ')' { $$ = PiclNodeArray_pop(picl_driver->node_buff_stack); }

func_def_keyword_args
  : '}' { $$ = NULL; }
  | new_node_stack args_def '}' { $$ = PiclNodeArray_pop(picl_driver->node_buff_stack); }

args_def
  : arg_def                    { PiclNodeBuffStack_push(picl_driver->node_buff_stack, $1); }
  | args_def ',' arg_def       { PiclNodeBuffStack_push(picl_driver->node_buff_stack, $3); }

arg_def
  : arg_pattern                    { $$ = $1; }
  | keyword_and_ident arg_pattern  { $$ = PiclNode_newNaming(NodeType_Decl_Type_Arg, $1, $2); }

arg_pattern
  : keyword_and_ident       { $$ = PiclNode_newIdent(NodeType_Decl_ArgIdent, $1); }
  | primary_value           { $$ = $1; }

primary_value
  : LONG_LITERAL            { $$ = PiclNode_newInt($1); }
  | STRING_LITERAL          { $$ = PiclNode_newStr($1); }

keyword_and_ident
  : IDENT
  | T_IF
  | T_THEN
  | T_ELSE
  | T_WHILE
  | T_THAT
  | T_EACH
  | T_MAP
  | T_REDUCE
  | T_FILTER
  | T_ECHO

%%
