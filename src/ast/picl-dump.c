#include "picl-node.h"

struct PiclDumpEnv
{
    FILE *dump_stream;

    int indent_level;
};

struct PiclDumpEnv *PiclDumpEnv_new()
{
    struct PiclDumpEnv *dump_env = malloc(sizeof(struct PiclDumpEnv));
    debug_print("call malloc PiclDumpEnv\n");

    dump_env->indent_level = 0;
    dump_env->dump_stream = stdout;

    return dump_env;
}

void PiclDumpEnv_delete(struct PiclDumpEnv *dump_env)
{
    free(dump_env);
}

#define indent_up dump_env->indent_level += 2;
#define indent_down dump_env->indent_level -= 2;
#define print_indent_open fprintf(dump_env->dump_stream, "\n%*s(", dump_env->indent_level, "");
#define print_indent_close fprintf(dump_env->dump_stream, "\n%*s)", dump_env->indent_level, "");

void Picl_dump_node(struct PiclNode *node, struct PiclDumpEnv *dump_env);
void Picl_dump_nodes(struct PiclNodeArray *nodes, struct PiclDumpEnv *dump_env);

void Picl_dump_inline_node(struct PiclNode *node, struct PiclDumpEnv *dump_env)
{
    switch (node->node_type) {
        case NodeType_Function:
            fprintf(dump_env->dump_stream, "(NodeType_Function ");
            indent_up;
            fprintf(dump_env->dump_stream, "\n%*s%s", dump_env->indent_level, "", node->function_node.name->value);
            print_indent_open;
            Picl_dump_nodes(node->function_node.args, dump_env);
            fprintf(dump_env->dump_stream, "\n%*s)=", dump_env->indent_level, "");
            Picl_dump_nodes(node->function_node.body, dump_env);
            Picl_dump_nodes(node->function_node.lets, dump_env);
            indent_down;
            print_indent_close;
            break;

        case NodeType_Sequence:
            fprintf(dump_env->dump_stream, "(NodeType_Sequence");
            indent_up;
            fprintf(dump_env->dump_stream, "%s", node->class_kind_node.name->value);

            fprintf(dump_env->dump_stream, "\n%*sextentions", dump_env->indent_level, "");
            Picl_dump_nodes(node->class_kind_node.extentions, dump_env);
            fprintf(dump_env->dump_stream, "\n%*sfields", dump_env->indent_level, "");
            Picl_dump_nodes(node->class_kind_node.fields, dump_env);
            fprintf(dump_env->dump_stream, "\n%*smethods", dump_env->indent_level, "");
            Picl_dump_nodes(node->class_kind_node.methods, dump_env);
            fprintf(dump_env->dump_stream, "\n%*scatches", dump_env->indent_level, "");
            Picl_dump_nodes(node->class_kind_node.catches, dump_env);
            indent_down;
            print_indent_close;
            break;

        case NodeType_Class:
            fprintf(dump_env->dump_stream, "(NodeType_Class");
            indent_up;
            fprintf(dump_env->dump_stream, "%s", node->class_kind_node.name->value);

            fprintf(dump_env->dump_stream, "\n%*sextentions", dump_env->indent_level, "");
            Picl_dump_nodes(node->class_kind_node.extentions, dump_env);
            fprintf(dump_env->dump_stream, "\n%*sfields", dump_env->indent_level, "");
            Picl_dump_nodes(node->class_kind_node.fields, dump_env);
            fprintf(dump_env->dump_stream, "\n%*smethods", dump_env->indent_level, "");
            Picl_dump_nodes(node->class_kind_node.methods, dump_env);
            fprintf(dump_env->dump_stream, "\n%*scatches", dump_env->indent_level, "");
            Picl_dump_nodes(node->class_kind_node.catches, dump_env);
            indent_down;
            print_indent_close;
            break;

        case NodeType_Field:
            fprintf(dump_env->dump_stream, "(NodeType_Field");
            indent_up;
            fprintf(dump_env->dump_stream, "\n%*s%s", dump_env->indent_level, "", node->field_node.name->value);
            fprintf(dump_env->dump_stream, "\n%*s << ", dump_env->indent_level, "");
            Picl_dump_node(node->field_node.value, dump_env);
            indent_down;
            print_indent_close;
            break;

        case NodeType_Method:
            fprintf(dump_env->dump_stream, "(NodeType_Method");
            indent_up;
            fprintf(dump_env->dump_stream, "\n%*s%s", dump_env->indent_level, "", node->method_node.name->value);
            print_indent_open;
            Picl_dump_nodes(node->method_node.args, dump_env);
            fprintf(dump_env->dump_stream, "\n%*s)=", dump_env->indent_level, "");

            Picl_dump_nodes(node->method_node.body, dump_env);

            Picl_dump_nodes(node->method_node.lets, dump_env);
            indent_down;
            print_indent_close;
            break;

        case NodeType_Catch:
            fprintf(dump_env->dump_stream, "(NodeType_Catch");
            indent_up;
            if(node->catch_node.name != NULL){
                fprintf(dump_env->dump_stream, "\n%*s%s", dump_env->indent_level, "", node->catch_node.name->value);
            }
            print_indent_open;
            Picl_dump_nodes(node->catch_node.args, dump_env);
            fprintf(dump_env->dump_stream, "\n%*s)=", dump_env->indent_level, "");

            Picl_dump_nodes(node->catch_node.body, dump_env);

            Picl_dump_nodes(node->catch_node.lets, dump_env);
            indent_down;
            print_indent_close;
            break;

        case NodeType_Let:
            fprintf(dump_env->dump_stream, "(NodeType_Let");
            indent_up;
            fprintf(dump_env->dump_stream, "\n%*s%s", dump_env->indent_level, "", node->function_node.name->value);
            print_indent_open;
            Picl_dump_nodes(node->function_node.args, dump_env);
            fprintf(dump_env->dump_stream, "\n%*s)=", dump_env->indent_level, "");
            Picl_dump_nodes(node->function_node.body, dump_env);
            indent_down;
            print_indent_close;
            break;

        case NodeType_CallFuncArg:
            fprintf(dump_env->dump_stream, "(NodeType_CallFuncArg");
            Picl_dump_node(node->call_func_node.func, dump_env);
            if(node->call_func_node.args != NULL){
                indent_up;
                print_indent_open;
                Picl_dump_nodes(node->call_func_node.args, dump_env);
                print_indent_close;
                indent_down;
            }
            else{
                fprintf(dump_env->dump_stream, "()");
            }
            print_indent_close;
            break;

        case NodeType_CallMethodArg:
            fprintf(dump_env->dump_stream, "(NodeType_CallMethodArg");
            Picl_dump_node(node->call_method_node.node, dump_env);
            fprintf(dump_env->dump_stream, ".%s", node->method_node.name->value);
            if(node->call_method_node.args != NULL){
                indent_up;
                print_indent_open;
                Picl_dump_nodes(node->call_method_node.args, dump_env);
                print_indent_close;
                indent_down;
            }
            else{
                fprintf(dump_env->dump_stream, "()");
            }
            print_indent_close;
            break;

        case NodeType_CallMethodNewArg:
            fprintf(dump_env->dump_stream, "(NodeType_CallMethodNewArg");
            Picl_dump_node(node->call_method_node.node, dump_env);
            fprintf(dump_env->dump_stream, ".%s", node->method_node.name->value);
            if(node->call_method_node.args != NULL){
                indent_up;
                print_indent_open;
                Picl_dump_nodes(node->call_method_node.args, dump_env);
                print_indent_close;
                indent_down;
            }
            else{
                fprintf(dump_env->dump_stream, "()");
            }
            print_indent_close;
            break;

        case NodeType_Body_Opt:
            fprintf(dump_env->dump_stream, "(NodeType_Body_Opt");
            Picl_dump_node(node->binary_node.left, dump_env);
            Picl_dump_node(node->binary_node.right, dump_env);
            print_indent_close;
            break;

            
        /*
         * stmts
         */

        case NodeType_IfElse:
            fprintf(dump_env->dump_stream, "(NodeType_IfElse");
            Picl_dump_node(node->cond_unary_node.cond, dump_env);
            indent_up;
            fprintf(dump_env->dump_stream, "\n%*sthen", dump_env->indent_level, "");
            Picl_dump_nodes(node->cond_binary_node.left, dump_env);
            fprintf(dump_env->dump_stream, "\n%*selse", dump_env->indent_level, "");
            Picl_dump_nodes(node->cond_binary_node.right, dump_env);
            indent_down;
            print_indent_close;
            break;

        case NodeType_If:
            fprintf(dump_env->dump_stream, "(NodeType_If");
            Picl_dump_node(node->cond_unary_node.cond, dump_env);
            indent_up;
            fprintf(dump_env->dump_stream, "\n%*sthen", dump_env->indent_level, "");
            Picl_dump_nodes(node->cond_unary_node.nodes, dump_env);
            indent_down;
            print_indent_close;
            break;

        case NodeType_While:
            fprintf(dump_env->dump_stream, "(NodeType_While");
            Picl_dump_node(node->cond_unary_node.cond, dump_env);
            indent_up;
            fprintf(dump_env->dump_stream, "\n%*sthen", dump_env->indent_level, "");
            Picl_dump_nodes(node->cond_unary_node.nodes, dump_env);
            indent_down;
            print_indent_close;
            break;

        case NodeType_Case:
            fprintf(dump_env->dump_stream, "(NodeType_Case");
            Picl_dump_node(node->cond_unary_node.cond, dump_env);
            indent_up;
            Picl_dump_nodes(node->cond_unary_node.nodes, dump_env);
            indent_down;
            print_indent_close;
            break;

        case NodeType_When:
            fprintf(dump_env->dump_stream, "(NodeType_When");
            Picl_dump_node(node->cond_unary_node.cond, dump_env);
            indent_up;
            fprintf(dump_env->dump_stream, "\n%*sthen", dump_env->indent_level, "");
            Picl_dump_nodes(node->cond_unary_node.nodes, dump_env);
            indent_down;
            print_indent_close;
            break;

        case NodeType_ListEach:
            fprintf(dump_env->dump_stream, "(NodeType_Each");
            Picl_dump_node(node->one_arg_list_stmt_node.cond, dump_env);
            indent_up;
            Picl_dump_nodes(node->one_arg_list_stmt_node.nodes, dump_env);
            indent_down;
            print_indent_close;
            break;

        case NodeType_ListEachWhen:
            fprintf(dump_env->dump_stream, "(NodeType_EachWhen");
            Picl_dump_node(node->one_arg_list_stmt_node.cond, dump_env);
            indent_up;
            fprintf(dump_env->dump_stream, "\n%*sthen", dump_env->indent_level, "");
            Picl_dump_nodes(node->one_arg_list_stmt_node.nodes, dump_env);
            indent_down;
            print_indent_close;
            break;

        case NodeType_ListMap:
            fprintf(dump_env->dump_stream, "(NodeType_Map");
            Picl_dump_node(node->one_arg_list_stmt_node.cond, dump_env);
            indent_up;
            fprintf(dump_env->dump_stream, "\n%*sthen", dump_env->indent_level, "");
            Picl_dump_nodes(node->one_arg_list_stmt_node.nodes, dump_env);
            indent_down;
            print_indent_close;
            break;

        case NodeType_ListMapWhen:
            fprintf(dump_env->dump_stream, "(NodeType_ListMapWhen");
            Picl_dump_node(node->one_arg_list_stmt_node.cond, dump_env);
            indent_up;
            fprintf(dump_env->dump_stream, "\n%*sthen", dump_env->indent_level, "");
            Picl_dump_nodes(node->one_arg_list_stmt_node.nodes, dump_env);
            indent_down;
            print_indent_close;
            break;

        case NodeType_ListFilter:
            fprintf(dump_env->dump_stream, "(NodeType_Filter");
            Picl_dump_node(node->one_arg_list_stmt_node.cond, dump_env);
            indent_up;
            fprintf(dump_env->dump_stream, "\n%*sthen", dump_env->indent_level, "");
            Picl_dump_nodes(node->one_arg_list_stmt_node.nodes, dump_env);
            indent_down;
            print_indent_close;
            break;

        case NodeType_ListFilterWhen:
            fprintf(dump_env->dump_stream, "(NodeType_ListFilterWhen");
            Picl_dump_node(node->one_arg_list_stmt_node.cond, dump_env);
            indent_up;
            fprintf(dump_env->dump_stream, "\n%*sthen", dump_env->indent_level, "");
            Picl_dump_nodes(node->one_arg_list_stmt_node.nodes, dump_env);
            indent_down;
            print_indent_close;
            break;

        case NodeType_ListReduce:
            fprintf(dump_env->dump_stream, "(NodeType_Reduce");
            fprintf(dump_env->dump_stream, " %s, %s", node->two_arg_list_stmt_node.name2->value, node->two_arg_list_stmt_node.name2->value);
            indent_up;
            fprintf(dump_env->dump_stream, "\n%*sthen", dump_env->indent_level, "");
            Picl_dump_nodes(node->two_arg_list_stmt_node.nodes, dump_env);
            indent_down;
            print_indent_close;
            break;

        /*
         * operator
         */

        case NodeType_Op_StrJoin:
            fprintf(dump_env->dump_stream, "(NodeType_Op_StrJoin &");
            Picl_dump_node(node->binary_node.left, dump_env);
            Picl_dump_node(node->binary_node.right, dump_env);
            print_indent_close;
            break;

        case NodeType_Op_Add:
            fprintf(dump_env->dump_stream, "(NodeType_Op_Add +");
            Picl_dump_node(node->binary_node.left, dump_env);
            Picl_dump_node(node->binary_node.right, dump_env);
            print_indent_close;
            break;
        
        case NodeType_Op_Sub:
            fprintf(dump_env->dump_stream, "(NodeType_Op_Sub -");
            Picl_dump_node(node->binary_node.left, dump_env);
            Picl_dump_node(node->binary_node.right, dump_env);
            print_indent_close;
            break;
        
        case NodeType_Op_Mul:
            fprintf(dump_env->dump_stream, "(NodeType_Op_Mul *");
            Picl_dump_node(node->binary_node.left, dump_env);
            Picl_dump_node(node->binary_node.right, dump_env);
            print_indent_close;
            break;
        
        case NodeType_Op_Div:
            fprintf(dump_env->dump_stream, "(NodeType_Op_Div /");
            Picl_dump_node(node->binary_node.left, dump_env);
            Picl_dump_node(node->binary_node.right, dump_env);
            print_indent_close;
            break;
        
        case NodeType_Op_Mod:
            fprintf(dump_env->dump_stream, "(NodeType_Op_Mod %%");
            Picl_dump_node(node->binary_node.left, dump_env);
            Picl_dump_node(node->binary_node.right, dump_env);
            print_indent_close;
            break;

        case NodeType_Op_Equal:
            fprintf(dump_env->dump_stream, "(NodeType_Op_Equal ==");
            Picl_dump_node(node->binary_node.left, dump_env);
            Picl_dump_node(node->binary_node.right, dump_env);
            print_indent_close;
            break;

        case NodeType_Op_NotEqual:
            fprintf(dump_env->dump_stream, "(NodeType_Op_NotEqual !=");
            Picl_dump_node(node->binary_node.left, dump_env);
            Picl_dump_node(node->binary_node.right, dump_env);
            print_indent_close;
            break;

        case NodeType_Op_GtEqual:
            fprintf(dump_env->dump_stream, "(NodeType_Op_GtEqual >=");
            Picl_dump_node(node->binary_node.left, dump_env);
            Picl_dump_node(node->binary_node.right, dump_env);
            print_indent_close;
            break;

        case NodeType_Op_LtEqual:
            fprintf(dump_env->dump_stream, "(NodeType_Op_LtEqual <=");
            Picl_dump_node(node->binary_node.left, dump_env);
            Picl_dump_node(node->binary_node.right, dump_env);
            print_indent_close;
            break;

        case NodeType_Op_Gt:
            fprintf(dump_env->dump_stream, "(NodeType_Op_Gt >");
            Picl_dump_node(node->binary_node.left, dump_env);
            Picl_dump_node(node->binary_node.right, dump_env);
            print_indent_close;
            break;

        case NodeType_Op_Lt:
            fprintf(dump_env->dump_stream, "(NodeType_Op_Lt <");
            Picl_dump_node(node->binary_node.left, dump_env);
            Picl_dump_node(node->binary_node.right, dump_env);
            print_indent_close;
            break;

        case NodeType_Op_Compare:
            fprintf(dump_env->dump_stream, "(NodeType_Op_Compare <=>");
            Picl_dump_node(node->binary_node.left, dump_env);
            Picl_dump_node(node->binary_node.right, dump_env);
            print_indent_close;
            break;

        case NodeType_Op_Assign:
            fprintf(dump_env->dump_stream, "(NodeType_Op_Assign <<");
            Picl_dump_node(node->binary_node.left, dump_env);
            Picl_dump_node(node->binary_node.right, dump_env);
            print_indent_close;
            break;

        case NodeType_Op_Colon:
            Picl_dump_node(node->binary_node.left, dump_env);
            fprintf(dump_env->dump_stream, ":");
            Picl_dump_node(node->binary_node.right, dump_env);
            break;

        case NodeType_Op_Comma:
            Picl_dump_node(node->binary_node.left, dump_env);
            fprintf(dump_env->dump_stream, ",");
            Picl_dump_node(node->binary_node.right, dump_env);
            break;

        case NodeType_Op_Method:
            Picl_dump_node(node->binary_node.left, dump_env);
            fprintf(dump_env->dump_stream, ".");
            Picl_dump_node(node->binary_node.right, dump_env);
            break;

        case NodeType_Stmt_Return_Var:
            fprintf(dump_env->dump_stream, "(NodeType_Stmt_Return_Var");
            Picl_dump_node(node->unary_node.node, dump_env);
            print_indent_close;
            break;

        case NodeType_Stmt_Echo_Var:
            fprintf(dump_env->dump_stream, "(NodeType_Stmt_Echo_Var");
            Picl_dump_node(node->unary_node.node, dump_env);
            print_indent_close;
            break;

        case NodeType_Val_List_Var:
            fprintf(dump_env->dump_stream, "NodeType_Val_List_Var");
            Picl_dump_node(node->unary_node.node, dump_env);
            break;

        case NodeType_Val_Dict_Var:
            fprintf(dump_env->dump_stream, "NodeType_Val_Dict_Var");
            Picl_dump_node(node->unary_node.node, dump_env);
            break;

        case NodeType_Op_Minus:
            fprintf(dump_env->dump_stream, "NodeType_Op_Minus -");
            Picl_dump_node(node->unary_node.node, dump_env);
            break;

        case NodeType_Op_FuncLazy:
            Picl_dump_node(node->unary_node.node, dump_env);
            fprintf(dump_env->dump_stream, "!()");
            break;

        case NodeType_Stmt_Return:
            fprintf(dump_env->dump_stream, "NodeType_Stmt_Return");
            break;

        case NodeType_Stmt_Break:
            fprintf(dump_env->dump_stream, "NodeType_Stmt_Break");
            break;

        case NodeType_Stmt_Continue:
            fprintf(dump_env->dump_stream, "NodeType_Stmt_Continue");
            break;

        case NodeType_Val_Dict:
            fprintf(dump_env->dump_stream, "NodeType_Val_Dict [=>]");
            break;

        case NodeType_Val_List:
            fprintf(dump_env->dump_stream, "NodeType_Val_List []");
            break;

        case NodeType_Val_IdentGlobal:
            fprintf(dump_env->dump_stream, "NodeType_Val_IdentGlobal %s", node->ident_node.name->value);
            break;
        case NodeType_Val_IdentCurrentField:
            fprintf(dump_env->dump_stream, "NodeType_Val_IdentCurrentField %s", node->ident_node.name->value);
            break;
        case NodeType_Val_IdentCurrentMethod:
            fprintf(dump_env->dump_stream, "NodeType_Val_IdentCurrentMethod %s", node->ident_node.name->value);
            break;
        case NodeType_Val_IdentArg:
            fprintf(dump_env->dump_stream, "NodeType_Val_IdentArg %s", node->ident_node.name->value);
            break;
        case NodeType_Val_Ident:
            fprintf(dump_env->dump_stream, "NodeType_Val_Ident %s", node->ident_node.name->value);
            break;
        case NodeType_Decl_ArgIdent:
            fprintf(dump_env->dump_stream, "NodeType_Decl_ArgIdent %s", node->ident_node.name->value);
            break;

        case NodeType_Op_Dot:
            Picl_dump_inline_node(node->naming_node.node, dump_env);
            fprintf(dump_env->dump_stream, ".");
            fprintf(dump_env->dump_stream, "%s", node->naming_node.name->value);
            break;

        case NodeType_Val_Var_Dict:
            fprintf(dump_env->dump_stream, "%s", node->naming_node.name->value);
            fprintf(dump_env->dump_stream, "=>");
            Picl_dump_node(node->naming_node.node, dump_env);
            break;

        case NodeType_Val_Str_Dict:
            fprintf(dump_env->dump_stream, "\"");
            fprintf(dump_env->dump_stream, "%s", node->naming_node.name->value);
            fprintf(dump_env->dump_stream, "\"=>");
            Picl_dump_node(node->naming_node.node, dump_env);
            break;

        case NodeType_Str:
            fprintf(dump_env->dump_stream, "str \"%s\"", node->str_node.str_value->value);
            break;

        case NodeType_Int:
            fprintf(dump_env->dump_stream, "int %lld", node->int_node.int_value);
            break;
        default:
            fprintf(dump_env->dump_stream, "dump undefined node %d", node->node_type);
            break;
    }
}

void Picl_dump_node(struct PiclNode *node, struct PiclDumpEnv *dump_env)
{
    indent_up
    fprintf(dump_env->dump_stream, "\n%*s", dump_env->indent_level, "");
    Picl_dump_inline_node(node, dump_env);
    indent_down;
}

void Picl_dump_nodes(struct PiclNodeArray *nodes, struct PiclDumpEnv *dump_env)
{
    if(nodes == NULL) return;
    for(int i = 0; i < nodes->size; i++){
        Picl_dump_node(nodes->value[i], dump_env);
    }
}

void Picl_dump_program(struct PiclNodeArray *nodes)
{
    if(nodes == NULL) return;
    struct PiclDumpEnv *dump_env = PiclDumpEnv_new();
    Picl_dump_nodes(nodes, dump_env);
    fprintf(dump_env->dump_stream, "\n");
    PiclDumpEnv_delete(dump_env);
}
