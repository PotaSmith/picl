#include "picl-optimize-env.h"

struct PiclVariableNames *PiclVariableNames_new()
{
    struct PiclVariableNames *var_names = malloc(sizeof(struct PiclVariableNames));
    debug_print("call malloc PiclVariableNames\n");

    for (int i = 0; i < VARIABLE_NAMES_DATA_SIZE; ++i)
    {
        var_names->data[i] = NULL;
    }
    var_names->size = 0;
    return var_names;
}

void PiclVariableNames_delete(struct PiclVariableNames *var_names)
{
    free(var_names);
}

int PiclOptimizeEnv_find_field_index(struct PiclOptimizeEnv *optimize_env, struct PiclStr *name)
{
    if(optimize_env->this_node == NULL) return -1;
    if(optimize_env->this_node->class_kind_node.fields == NULL) return -1;

    for(int i = 0; i < optimize_env->this_node->class_kind_node.fields->size; i++){
        debug_print("compare names %s, %s\n", optimize_env->this_node->class_kind_node.fields->value[i]->field_node.name->value, name->value);
        if(PiclStr_equals(optimize_env->this_node->class_kind_node.fields->value[i]->field_node.name, name)){
            return i;
        }
    }
    return -1;
}
int PiclOptimizeEnv_find_method_index(struct PiclOptimizeEnv *optimize_env, struct PiclStr *name)
{
    if(optimize_env->this_node == NULL) return -1;
    if(optimize_env->this_node->class_kind_node.methods == NULL) return -1;

    for(int i = 0; i < optimize_env->this_node->class_kind_node.methods->size; i++){
        debug_print("compare names %s, %s\n", optimize_env->this_node->class_kind_node.methods->value[i]->method_node.name->value, name->value);
        if(PiclStr_equals(optimize_env->this_node->class_kind_node.methods->value[i]->method_node.name, name)){
            return i;
        }
    }
    return -1;
}
int PiclOptimizeEnv_find_catch_index(struct PiclOptimizeEnv *optimize_env, struct PiclStr *name)
{
    if(optimize_env->this_node == NULL) return -1;
    if(optimize_env->this_node->class_kind_node.catches == NULL) return -1;

    for(int i = 0; i < optimize_env->this_node->class_kind_node.catches->size; i++){
        debug_print("compare names %s, %s\n", optimize_env->this_node->class_kind_node.catches->value[i]->method_node.name->value, name->value);
        if(PiclStr_equals(optimize_env->this_node->class_kind_node.catches->value[i]->catch_node.name, name)){
            return i;
        }
    }
    return -1;
}


int PiclVariableNames_get_name_index(struct PiclVariableNames *var_names, struct PiclStr *name)
{
    for (int i = 0; i < var_names->size; ++i){
        if(var_names->data[i] == NULL) return -1;

        debug_print("compare names %s, %s\n", name->value, var_names->data[i]->value);

        if(PiclStr_equals(name, var_names->data[i])){
            return i;
        }
    }
    return -1;
}
int PiclVariableNames_set_name_index(struct PiclVariableNames *var_names, struct PiclStr *name)
{
    var_names->data[var_names->size] = name;
    return var_names->size++;
}

struct PiclFrameVariableNames *PiclFrameVariableNames_new()
{
    struct PiclFrameVariableNames *func_var_names = malloc(sizeof(struct PiclFrameVariableNames));
    debug_print("call malloc PiclFrameVariableNames\n");

    func_var_names->args = PiclVariableNames_new();
    func_var_names->locals = PiclVariableNames_new();
    func_var_names->prev = NULL;
    func_var_names->next = NULL;
    return func_var_names;

}
void PiclFrameVariableNames_delete(struct PiclFrameVariableNames *func_var_names)
{
    PiclVariableNames_delete(func_var_names->args);
    PiclVariableNames_delete(func_var_names->locals);

    free(func_var_names);
}

void PiclNode_set_variable_size(struct PiclNode *node, int *args_size, int *variables_size, struct PiclOptimizeEnv *optimize_env)
{
    *args_size = optimize_env->frame_var_names->args->size;
    *variables_size = optimize_env->frame_var_names->locals->size;

    debug_print("set arg size : %d\n", *args_size);
    debug_print("set local size: %d\n", *variables_size);
}

struct PiclOptimizeEnv *PiclOptimizeEnv_new()
{
    struct PiclOptimizeEnv *optimize_env = malloc(sizeof(struct PiclOptimizeEnv));
    debug_print("call malloc PiclOptimizeEnv\n");

    optimize_env->this_node = NULL;
    optimize_env->frame_var_names = PiclFrameVariableNames_new();
    optimize_env->decl_names = PiclVariableNames_new();
    optimize_env->class_names = PiclVariableNames_new();
    optimize_env->field_names = PiclVariableNames_new();
    optimize_env->method_names = PiclVariableNames_new();
    optimize_env->method_size = 0;

    PiclVariableNames_set_name_index(optimize_env->method_names, PiclStr_newByConst("new"));

    return optimize_env;
}
void PiclOptimizeEnv_delete(struct PiclOptimizeEnv *optimize_env)
{
    PiclFrameVariableNames_delete(optimize_env->frame_var_names);
    free(optimize_env);
}
void PiclOptimizeEnv_push(struct PiclOptimizeEnv *optimize_env)
{
    struct PiclFrameVariableNames *next = PiclFrameVariableNames_new();

    optimize_env->frame_var_names->next = next;
    next->prev = optimize_env->frame_var_names;

    optimize_env->frame_var_names = next;
}

void PiclOptimizeEnv_pop(struct PiclOptimizeEnv *optimize_env, struct PiclNode *node, int *args_size, int *variables_size)
{
    PiclNode_set_variable_size(node, args_size, variables_size, optimize_env);

    struct PiclFrameVariableNames *prev = optimize_env->frame_var_names->prev;
    PiclFrameVariableNames_delete(optimize_env->frame_var_names);
    optimize_env->frame_var_names = prev;
}

void PiclOptimizeEnv_set_object(struct PiclNode *node, struct PiclOptimizeEnv *optimize_env)
{
    optimize_env->this_node = node;
}

void PiclOptimizeEnv_unset_object(struct PiclOptimizeEnv *optimize_env)
{
    optimize_env->this_node = NULL;
}

void set_class_name_index(struct PiclNode *node, int class_name_index)
{
    switch (node->node_type) {
        case NodeType_Const:
//            node->left.str_value->value;
//            Picl_optimize_node_global(node->right.node, optimize_env);
            break;

        case NodeType_Field:
            node->field_node.class_name_index = class_name_index;
            break;

        case NodeType_Method:
            node->method_node.class_name_index = class_name_index;
            break;

        default:
            printf("Exception : set_class_name_index %d\n", node->node_type);
            exit(1);
    }
}

int PiclOptimizeEnv_set_decl_name_index(struct PiclOptimizeEnv *optimize_env, struct PiclNode *node, struct PiclStr *name, int *name_index)
{
    int index = PiclVariableNames_set_name_index(optimize_env->decl_names, name);
    *name_index = index;
    debug_print("set decl name : %s : %d\n", name->value, index);

    return index;
}
int PiclOptimizeEnv_find_decl_name_index(struct PiclOptimizeEnv *optimize_env, struct PiclStr *name)
{
    return PiclVariableNames_get_name_index(optimize_env->decl_names, name);
}

int PiclOptimizeEnv_set_class_name_index(struct PiclOptimizeEnv *optimize_env, struct PiclNode *node, struct PiclStr *name, int *name_index)
{
    int index = PiclVariableNames_set_name_index(optimize_env->class_names, name);
    *name_index = index;
    debug_print("set class name : %s : %d\n", name->value, index);

    return index;
}
int PiclOptimizeEnv_set_field_name_index(struct PiclOptimizeEnv *optimize_env, struct PiclNode *node, struct PiclStr *name, int *name_index)
{
    int index = PiclVariableNames_get_name_index(optimize_env->field_names, name);
    if(index != -1){
        *name_index = index;
        debug_print("set field name : %s : %d\n", name->value, index);
        return index;
    }

    index = PiclVariableNames_set_name_index(optimize_env->field_names, name);
    *name_index = index;
    debug_print("set field name : %s : %d\n", name->value, index);

    return index;
}
int PiclOptimizeEnv_set_method_name_index(struct PiclOptimizeEnv *optimize_env, struct PiclNode *node, struct PiclStr *name, int *name_index)
{
    int index = PiclVariableNames_get_name_index(optimize_env->method_names, name);
    if(index != -1){
        *name_index = index;
        debug_print("set method name : %s : %d\n", name->value, index);
        return index;
    }

    index = PiclVariableNames_set_name_index(optimize_env->method_names, name);
    *name_index = index;
    ++optimize_env->method_size;
    debug_print("set method name : %s : %d\n", name->value, index);

    return index;
}
int PiclOptimizeEnv_set_catch_name_index(struct PiclOptimizeEnv *optimize_env, struct PiclNode *node, struct PiclStr *name, int *name_index)
{
    int index = PiclVariableNames_get_name_index(optimize_env->catch_names, name);
    if(index != -1){
        *name_index = index;
        debug_print("set catch name : %s : %d\n", name->value, index);
        return index;
    }

    index = PiclVariableNames_set_name_index(optimize_env->catch_names, name);
    *name_index = index;
    debug_print("set method name : %s : %d\n", name->value, index);

    return index;
}

int PiclOptimizeEnv_set_arg_index(struct PiclOptimizeEnv *optimize_env, struct PiclStr *name)
{
    int index = PiclVariableNames_set_name_index(optimize_env->frame_var_names->args, name);
    debug_print("set argument name : %s : %d\n", name->value, index);
    return index;
}

int PiclOptimizeEnv_find_name_index(struct PiclOptimizeEnv *optimize_env, struct PiclNode *node, struct PiclStr *name, int *name_index)
{
    int index = PiclVariableNames_get_name_index(optimize_env->frame_var_names->locals, name);
    if(index != -1){
        *name_index = index;
        debug_print("get variable is local. name : %s : %d\n", name->value, index);
        return index;
    }
    index = PiclVariableNames_get_name_index(optimize_env->frame_var_names->args, name);
    if(index != -1){
        node->node_type = NodeType_Val_IdentArg;
        *name_index = index;
        debug_print("get variable is arg. name : %s : %d\n", name->value, index);
        return index;
    }
    index = PiclOptimizeEnv_find_field_index(optimize_env, name);
    if(index != -1){
        node->node_type = NodeType_Val_IdentCurrentField;
        *name_index = index;
        debug_print("get variable is member field. name : %s : %d\n", name->value, index);
        return index;
    }
    index = PiclOptimizeEnv_find_method_index(optimize_env, name);
    if(index != -1){
        node->node_type = NodeType_Val_IdentCurrentMethod;
        *name_index = index;
        debug_print("get variable is member method. name : %s : %d\n", name->value, index);
        return index;
    }
    index = PiclVariableNames_get_name_index(optimize_env->decl_names, name);
    if(index != -1){
        node->node_type = NodeType_Val_IdentGlobal;
        *name_index = index;
        debug_print("get variable is global. name : %s : %d\n", name->value, index);
        return index;
    }

    index = PiclVariableNames_set_name_index(optimize_env->frame_var_names->locals, name);
    *name_index = index;
    debug_print("get variable not found. set local. name : %s : %d\n", name->value, index);
    return index;
}

int PiclOptimizeEnv_find_field_name_index(struct PiclOptimizeEnv *optimize_env, struct PiclStr *name, int *name_index)
{
    int index = PiclVariableNames_get_name_index(optimize_env->field_names, name);
    if(index != -1){
        *name_index = index;
        debug_print("get field. name : %s : %d\n", name->value, index);
        return index;
    }
    else{
        debug_print("field not found. name : %s\n", name->value);
        exit(1);
    }
}
int PiclOptimizeEnv_find_method_name_index(struct PiclOptimizeEnv *optimize_env, struct PiclStr *name, int *name_index)
{
    int index = PiclVariableNames_get_name_index(optimize_env->method_names, name);
    if(index != -1){
        *name_index = index;
        debug_print("get method. name : %s : %d\n", name->value, index);
        return index;
    }
    else{
        debug_print("method not found. name : %s\n", name->value);
        exit(1);
    }
}



