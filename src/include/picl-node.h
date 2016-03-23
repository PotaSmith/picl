#ifndef PICL_NODE_H
# define PICL_NODE_H
# include "picl-object.h"

/*
    node 関係
    void ポインタはどうなのか

    class類
        name
        members*
        options* 継承等
    関数類
        name
        args*
        args_size
        body*
        variables_size
        scope
    list類 stmts exprs args 
        body*
    expr and stmt
        left
        right
        mid
    value
        string or int

 */

typedef enum _NodeType {

    // class_kind_node

    NodeType_Sequence = 1,
    NodeType_Class,
    NodeType_Behavior,

    // function_node

    NodeType_Function = 10,

    // member_node

    NodeType_Const = 20,
    NodeType_Field,
    NodeType_Method,
    NodeType_Alias,
    NodeType_Catch,

    NodeType_Let,

    NodeType_ArgDef,
    NodeType_Arg,

    NodeType_List,
    NodeType_Dict,

    // call_func_node

    NodeType_CallFuncArg,
    NodeType_CallFuncStmt,
    NodeType_Catch_Ident,

    // call_method_node

    NodeType_CallMethodArg,
    NodeType_CallMethodStmt,
    NodeType_CallMethodNewArg,
    NodeType_CallMethodNewStmt,

    // nodes_node

    NodeType_Stmts,
    NodeType_WhenElse,

    // two_arg_list_stmt_node

    NodeType_ListReduce,

    // one_arg_list_stmt_node

    NodeType_ListEach,
    NodeType_ListEachWhen,
    NodeType_ListMap,
    NodeType_ListMapWhen,
    NodeType_ListFilter,
    NodeType_ListFilterWhen,

    // cond_binary_node

    NodeType_IfElse,

    // cond_unary_node

    NodeType_If,
    NodeType_While,
    NodeType_Case,
    NodeType_When,


    // binary_node

    NodeType_Body_Opt,

    NodeType_Op_StrJoin = 100,

    NodeType_Op_Add,
    NodeType_Op_Sub,
    NodeType_Op_Mul,
    NodeType_Op_Div,
    NodeType_Op_Mod,

    NodeType_Op_Equal,
    NodeType_Op_NotEqual,
    NodeType_Op_GtEqual,
    NodeType_Op_LtEqual,
    NodeType_Op_Gt,
    NodeType_Op_Lt,
    NodeType_Op_Compare,

    NodeType_Op_Assign,
    NodeType_Op_Assign_Arg,
    NodeType_Op_Assign_CurrentField,
    NodeType_Op_Assign_Member,

    NodeType_Op_Colon,
    NodeType_Op_Comma,
    NodeType_Op_Method,

    NodeType_Op_Def_Or,

    // unary_node

    NodeType_Stmt_Return_Var = 200,
    NodeType_Stmt_Throw_Var,
    NodeType_Stmt_Echo_Var,

    NodeType_Val_List_Var,
    NodeType_Val_Dict_Var,
    NodeType_Op_Minus,

    NodeType_Op_FuncLazy,

    // Atom

    NodeType_Stmt_Return = 300,
    NodeType_Stmt_Throw,
    NodeType_Stmt_Break,
    NodeType_Stmt_Continue,
    NodeType_Val_Dict,
    NodeType_Val_List,

    // Ident ident_node

    NodeType_Val_IdentGlobal = 400,
    NodeType_Val_IdentCurrentField,
    NodeType_Val_IdentCurrentMethod,
    NodeType_Val_IdentArg,
    NodeType_Val_Ident,

    NodeType_Decl_ArgIdent,

    // Namign naming_node

    NodeType_Dict_Arg = 500,

    NodeType_Decl_Type_Arg,
    NodeType_Decl_Func_Arg_KeywordArg,

    NodeType_Op_Dot,
    NodeType_Val_Var_Dict,
    NodeType_Val_Str_Dict,

    // Value str_node

    NodeType_Str,

    // Value int_node

    NodeType_Int,

} NodeType;

typedef enum _NodeDataType {
    NodeDataType_ClassKind,
    NodeDataType_Function,
    NodeDataType_Field,
    NodeDataType_Method,
    NodeDataType_Alias,
    NodeDataType_Catch,
    NodeDataType_CallFunc,
    NodeDataType_CallMethod,
    NodeDataType_Nodes,

    NodeDataType_OneArgListStmt,
    NodeDataType_TwoArgListStmt,
    NodeDataType_CondBinary,
    NodeDataType_CondUnary,

    NodeDataType_Binary,
    NodeDataType_Unary,
    NodeDataType_Naming,
    NodeDataType_Ident,
    NodeDataType_Atom,
    NodeDataType_Str,
    NodeDataType_Int,
} NodeDataType;

typedef enum _MemberScope {
    MemberScope_Public,
    MemberScope_Private,
} MemberScope;

struct PiclNode;

struct PiclNodeArray
{
    struct PiclNode **value;
    int size;
};


struct PiclNode
{
    NodeType node_type;
    NodeDataType node_data_type;

    union {
        struct PiclClassKindNodeData
        {
            struct PiclStr *name;
            int decl_name_index;
            int class_name_index;
            struct PiclNodeArray *extentions;
            struct PiclNodeArray *fields;
            struct PiclNodeArray *methods;
            struct PiclNodeArray *catches;
            struct PiclNodeArray *options;
        } class_kind_node;

        struct PiclFieldNode
        {
            int class_name_index;

            MemberScope scope;
            struct PiclStr *name;
            int name_index;
            struct PiclNode *value;
        } field_node;

        struct PiclMethodNode
        {
            int class_name_index;

            MemberScope scope;
            struct PiclStr *name;
            int name_index;
            struct PiclNodeArray *args;
            int args_size;
            struct PiclNodeArray *body;
            int variables_size;
            struct PiclNodeArray *lets;
            int lets_size;
        } method_node;

        struct PiclFieldAlias
        {
            struct PiclStr *name;
            int name_index;
            struct PiclNode *value;
        } alias_node;

        struct PiclCatchNode
        {
            struct PiclStr *name;
            int name_index;
            struct PiclNodeArray *args;
            int args_size;
            struct PiclNodeArray *body;
            int variables_size;
            struct PiclNodeArray *lets;
            int lets_size;
        } catch_node;

        struct PiclFunctionNodeData
        {
            struct PiclStr *name;
            int name_index;
            struct PiclNodeArray *args;
            int args_size;
            struct PiclNodeArray *body;
            int variables_size;
            struct PiclNodeArray *lets;
            int lets_size;
        } function_node;

        struct PiclCallFuncNodeData
        {
            int operand;
            struct PiclNode *func;
            struct PiclNodeArray *args;
        } call_func_node;

        struct PiclCallMethodNodeData
        {
            int operand;
            struct PiclStr *name;
            int name_index;
            struct PiclNode *node;
            struct PiclNodeArray *args;
        } call_method_node;


        struct PiclStmtsNodeData{
            int operand;
            struct PiclNodeArray *nodes;
        } stmts_node;

        struct PiclOneArgListStmtNodeData
        {
            int operand;
            struct PiclNode *cond;
            struct PiclStr *name;
            int name_index;
            struct PiclNodeArray *nodes;
        } one_arg_list_stmt_node;

        struct PiclTwoArgListStmtNodeData
        {
            int operand;
            struct PiclNode *cond;
            struct PiclStr *name1;
            int name_index1;
            struct PiclStr *name2;
            int name_index2;
            struct PiclNodeArray *nodes;
        } two_arg_list_stmt_node;

        struct PiclCondBinaryNodeData
        {
            int operand;
            struct PiclNode *cond;
            struct PiclNodeArray *left;
            struct PiclNodeArray *right;
        } cond_binary_node;

        struct PiclCondUnaryNodeData
        {
            int operand;
            struct PiclNode *cond;
            struct PiclNodeArray *nodes;
        } cond_unary_node;

        struct PiclBinaryNodeData
        {
            int operand;
            struct PiclNode *left;
            struct PiclNode *right;
        } binary_node;

        struct PiclUnaryNodeData
        {
            int operand;
            struct PiclNode *node;
        } unary_node;

        struct PiclIdentNodeData
        {
            int operand;
            struct PiclStr *name;
            int name_index;
        } ident_node;

        struct PiclNamingNodeData
        {
            int operand;
            struct PiclStr *name;
            int name_index;
            struct PiclNode *node;
        } naming_node;

        struct PiclStrNodeData
        {
            int operand;
            struct PiclObject *cache;
            struct PiclStr *str_value;
        } str_node;

        struct PiclIntNodeData
        {
            int operand;
            struct PiclObject *cache;
            PiclInt int_value;
        } int_node;
    };
};



#endif /* PICL_NODE_H */
