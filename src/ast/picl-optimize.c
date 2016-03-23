#include "picl-optimize-env.h"

void Picl_optimize_node_local(struct PiclNode *node, struct PiclOptimizeEnv *optimize_env);
void Picl_optimize_node_global(struct PiclNode *node, struct PiclOptimizeEnv *optimize_env);





void Picl_optimize_nodes_global(struct PiclNodeArray *nodes, struct PiclOptimizeEnv *optimize_env)
{
    if(nodes == NULL) return;
    for(int i = 0; i < nodes->size; i++){
        Picl_optimize_node_global(nodes->value[i], optimize_env);
    }
}

void Picl_optimize_class_member(struct PiclNode *class_node, struct PiclNode *node, struct PiclOptimizeEnv *optimize_env)
{
    switch (node->node_type) {
        case NodeType_Const:
//            node->left.str_value->value;
//            Picl_optimize_node_global(node->right.node, optimize_env);
            break;

        case NodeType_Field:
            PiclOptimizeEnv_set_field_name_index(optimize_env, node, node->field_node.name, &node->field_node.name_index);
            break;

        case NodeType_Method:
            PiclOptimizeEnv_set_method_name_index(optimize_env, node, node->method_node.name, &node->method_node.name_index);
            break;

        case NodeType_Catch:
            if(node->catch_node.name != NULL){
            PiclOptimizeEnv_set_catch_name_index(optimize_env, node, node->catch_node.name, &node->catch_node.name_index);
            }
            break;

        default:
            break;
    }
}

void Picl_optimize_node_assign(struct PiclNode *node, struct PiclOptimizeEnv *optimize_env)
{
    Picl_optimize_node_local(node->binary_node.left, optimize_env);
    Picl_optimize_node_local(node->binary_node.right, optimize_env);

    switch (node->binary_node.left->node_type) {
        case NodeType_Val_IdentArg:
            node->node_type = NodeType_Op_Assign_Arg;
            break;
        case NodeType_Val_IdentCurrentField:
            node->node_type = NodeType_Op_Assign_CurrentField;
            break;

        case NodeType_Op_Dot:
            node->node_type = NodeType_Op_Assign_Member;
            break;
        default:
            break;
    }
}

void Picl_optimize_node_global(struct PiclNode *node, struct PiclOptimizeEnv *optimize_env)
{
    switch (node->node_type) {
        case NodeType_Function:
            PiclOptimizeEnv_set_decl_name_index(optimize_env, node, node->function_node.name, &node->function_node.name_index);
            break;

        case NodeType_Class:
            PiclOptimizeEnv_set_decl_name_index(optimize_env, node, node->class_kind_node.name, &node->class_kind_node.decl_name_index);
            PiclOptimizeEnv_set_class_name_index(optimize_env, node, node->class_kind_node.name, &node->class_kind_node.class_name_index);

            if(node->class_kind_node.extentions != NULL){
                for(int i = 0; i < node->class_kind_node.extentions->size; i++){
                    Picl_optimize_class_member(node, node->class_kind_node.extentions->value[i], optimize_env);
                }
            }
            if(node->class_kind_node.fields != NULL){
                for(int i = 0; i < node->class_kind_node.fields->size; i++){
                    Picl_optimize_class_member(node, node->class_kind_node.fields->value[i], optimize_env);
                }
            }
            if(node->class_kind_node.methods != NULL){
                for(int i = 0; i < node->class_kind_node.methods->size; i++){
                    Picl_optimize_class_member(node, node->class_kind_node.methods->value[i], optimize_env);
                }
            }
            if(node->class_kind_node.catches != NULL && node->class_kind_node.catches->size > 0){
                fprintf(stderr, "Tell Developer : Picl_optimize_node_local cactches found in class node\n");
                exit(1);
            }
            break;

        case NodeType_Sequence:
            PiclOptimizeEnv_set_decl_name_index(optimize_env, node, node->class_kind_node.name, &node->class_kind_node.decl_name_index);
            PiclOptimizeEnv_set_class_name_index(optimize_env, node, node->class_kind_node.name, &node->class_kind_node.class_name_index);

            if(node->class_kind_node.extentions != NULL){
                for(int i = 0; i < node->class_kind_node.extentions->size; i++){
                    Picl_optimize_class_member(node, node->class_kind_node.extentions->value[i], optimize_env);
                }
            }
            if(node->class_kind_node.fields != NULL){
                for(int i = 0; i < node->class_kind_node.fields->size; i++){
                    Picl_optimize_class_member(node, node->class_kind_node.fields->value[i], optimize_env);
                }
            }
            if(node->class_kind_node.methods != NULL){
                for(int i = 0; i < node->class_kind_node.methods->size; i++){
                    Picl_optimize_class_member(node, node->class_kind_node.methods->value[i], optimize_env);
                }
            }
            if(node->class_kind_node.catches != NULL){
                for(int i = 0; i < node->class_kind_node.catches->size; i++){
                    Picl_optimize_class_member(node, node->class_kind_node.methods->value[i], optimize_env);
                }
            }
            break;

        case NodeType_Let:
//            Picl_optimize_node_global(node->left.node, optimize_env);
//            Picl_optimize_node_global(node->right.node, optimize_env);
            break;

        case NodeType_Val_Ident:
            PiclOptimizeEnv_set_decl_name_index(optimize_env, node, node->ident_node.name, &node->ident_node.name_index);
            break;

        default:
            break;
    }
}

void Picl_optimize_nodes_local(struct PiclNodeArray *nodes, struct PiclOptimizeEnv *optimize_env)
{
    if(nodes == NULL) return;
    for(int i = 0; i < nodes->size; i++){
        Picl_optimize_node_local(nodes->value[i], optimize_env);
    }
}

void Picl_optimize_node_local(struct PiclNode *node, struct PiclOptimizeEnv *optimize_env)
{
    switch (node->node_type) {

        case NodeType_Function:
        	PiclOptimizeEnv_push(optimize_env);

            Picl_optimize_nodes_local(node->function_node.args, optimize_env);
            Picl_optimize_nodes_local(node->function_node.body, optimize_env);

        	PiclOptimizeEnv_pop(optimize_env, node, &node->function_node.args_size, &node->function_node.variables_size);
            break;

        case NodeType_Class:
            // オブジェクトを見に行かないといけない
            PiclOptimizeEnv_set_object(node, optimize_env);

            Picl_optimize_nodes_local(node->class_kind_node.fields, optimize_env);
            Picl_optimize_nodes_local(node->class_kind_node.methods, optimize_env);

            PiclOptimizeEnv_unset_object(optimize_env);
            break;

        case NodeType_Sequence:
            // オブジェクトを見に行かないといけない
            PiclOptimizeEnv_set_object(node, optimize_env);

            Picl_optimize_nodes_local(node->class_kind_node.fields, optimize_env);
            Picl_optimize_nodes_local(node->class_kind_node.methods, optimize_env);
            Picl_optimize_nodes_local(node->class_kind_node.catches, optimize_env);

            PiclOptimizeEnv_unset_object(optimize_env);
            break;

        case NodeType_Const:
//            node->left.str_value->value;
//            Picl_optimize_node_local(node->right.node, optimize_env);
            break;

        case NodeType_Field:
//            node->left.str_value->value;
//            Picl_optimize_node_local(node->right.node, optimize_env);
            break;

        case NodeType_Method:
            PiclOptimizeEnv_push(optimize_env);

            Picl_optimize_nodes_local(node->method_node.args, optimize_env);
            Picl_optimize_nodes_local(node->method_node.body, optimize_env);

            PiclOptimizeEnv_pop(optimize_env, node, &node->method_node.args_size, &node->method_node.variables_size);
            break;

        case NodeType_Catch:
            PiclOptimizeEnv_push(optimize_env);

            Picl_optimize_nodes_local(node->catch_node.args, optimize_env);
            Picl_optimize_nodes_local(node->catch_node.body, optimize_env);

            PiclOptimizeEnv_pop(optimize_env, node, &node->method_node.args_size, &node->method_node.variables_size);
            break;

        case NodeType_Let:
//            Picl_optimize_node_local(node->left.node, optimize_env);
//            Picl_optimize_node_local(node->right.node, optimize_env);
            break;

        case NodeType_CallFuncArg:
            Picl_optimize_node_local(node->call_func_node.func, optimize_env);
            Picl_optimize_nodes_local(node->call_func_node.args, optimize_env);
            break;

        case NodeType_CallMethodArg:
            Picl_optimize_node_local(node->call_method_node.node, optimize_env);
            PiclOptimizeEnv_find_method_name_index(optimize_env, node->call_method_node.name, &node->call_method_node.name_index);
            Picl_optimize_nodes_local(node->call_method_node.args, optimize_env);
            break;

        case NodeType_CallMethodNewArg:
            Picl_optimize_node_local(node->call_method_node.node, optimize_env);
            PiclOptimizeEnv_find_method_name_index(optimize_env, node->call_method_node.name, &node->call_method_node.name_index);
            Picl_optimize_nodes_local(node->call_method_node.args, optimize_env);
            break;

        case NodeType_Stmts:
            Picl_optimize_nodes_local(node->stmts_node.nodes, optimize_env);
            break;

        case NodeType_IfElse:
            Picl_optimize_node_local(node->cond_binary_node.cond, optimize_env);
            Picl_optimize_nodes_local(node->cond_binary_node.left, optimize_env);
            Picl_optimize_nodes_local(node->cond_binary_node.right, optimize_env);
            break;

        case NodeType_If:
        case NodeType_While:
        case NodeType_Case:
        case NodeType_When:
            Picl_optimize_node_local(node->cond_unary_node.cond, optimize_env);
            Picl_optimize_nodes_local(node->cond_unary_node.nodes, optimize_env);
            break;


        case NodeType_Op_StrJoin:
        case NodeType_Op_Add:
        case NodeType_Op_Sub:
        case NodeType_Op_Mul:
        case NodeType_Op_Div:
        case NodeType_Op_Mod:
        case NodeType_Op_Equal:
        case NodeType_Op_NotEqual:
        case NodeType_Op_GtEqual:
        case NodeType_Op_LtEqual:
        case NodeType_Op_Gt:
        case NodeType_Op_Lt:
        case NodeType_Op_Colon:
        case NodeType_Op_Comma:
        case NodeType_Op_Method:
            Picl_optimize_node_local(node->binary_node.left, optimize_env);
            Picl_optimize_node_local(node->binary_node.right, optimize_env);
            break;
        case NodeType_Op_Assign:
            Picl_optimize_node_assign(node, optimize_env);
            break;

        case NodeType_Stmt_Return_Var:
        case NodeType_Stmt_Echo_Var:
        case NodeType_Val_List_Var:
        case NodeType_Val_Dict_Var:
        case NodeType_Op_Minus:
        case NodeType_Op_FuncLazy:
            Picl_optimize_node_local(node->unary_node.node, optimize_env);
            break;

        case NodeType_Val_Ident:
	        PiclOptimizeEnv_find_name_index(optimize_env, node, node->ident_node.name, &node->ident_node.name_index);
            break;

        case NodeType_Decl_ArgIdent:
            PiclOptimizeEnv_set_arg_index(optimize_env, node->ident_node.name);
            break;

        case NodeType_Op_Dot:
            PiclOptimizeEnv_find_field_name_index(optimize_env, node->naming_node.name, &node->call_method_node.name_index);
            Picl_optimize_node_local(node->naming_node.node, optimize_env);
            break;

        case NodeType_Val_Var_Dict:
//            node->left.str_value->value;
            Picl_optimize_node_local(node->naming_node.node, optimize_env);
            break;

        case NodeType_Val_Str_Dict:
//            node->left.str_value->value;
            Picl_optimize_node_local(node->naming_node.node, optimize_env);
            break;

        case NodeType_Str:
            node->str_node.cache = PiclObject_new_literal_str(node->str_node.str_value);
            break;

        case NodeType_Int:
            node->int_node.cache = PiclObject_new_literal_int(node->int_node.int_value);
            break;

        default:
            break;
    }
}

void Picl_optimize_nodes(struct PiclNodeArray *nodes, struct PiclOptimizeEnv *optimize_env)
{
    if(nodes == NULL) return;
    for(int i = 0; i < nodes->size; i++){
        Picl_optimize_node_global(nodes->value[i], optimize_env);
    }
    for(int i = 0; i < nodes->size; i++){
        Picl_optimize_node_local(nodes->value[i], optimize_env);
    }
}

