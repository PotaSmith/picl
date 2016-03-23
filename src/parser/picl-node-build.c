#include "picl-node-build.h"

struct PiclNodeArray *PiclNodeArray_new(int nodes_size)
{
    struct PiclNodeArray *node_array = malloc(sizeof(struct PiclNodeArray));
    debug_print("call malloc PiclNodes\n");

    node_array->value = malloc(sizeof(struct PiclNode) * nodes_size);
    node_array->size = nodes_size;

    return node_array;
}

struct PiclNodeBuff *PiclNodeBuff_init(struct PiclNodeBuff *node_buff)
{
    node_buff->size = 0;
    return node_buff;
}

struct PiclNodeBuffStack *PiclNodeBuffStack_new()
{
    struct PiclNodeBuffStack *node_buff_stack = malloc(sizeof(struct PiclNodeBuffStack));
    debug_print("call malloc PiclNodeBuffStack\n");

    node_buff_stack->size = 0;
    node_buff_stack->current_buf = PiclNodeBuff_init(&node_buff_stack->data[node_buff_stack->size++]);

    return node_buff_stack;
}

struct PiclNodeArray *PiclNodeArray_pop(struct PiclNodeBuffStack *node_buff_stack)
{
    debug_print("PiclNodeArray_pop before %d : %d\n", node_buff_stack->size, node_buff_stack->current_buf->size);
    struct PiclNodeBuff *node_buff = &node_buff_stack->data[--node_buff_stack->size];
    node_buff_stack->current_buf = &node_buff_stack->data[node_buff_stack->size - 1];

    if(node_buff->size == 0){
        debug_print("PiclNodeArray_pop after %d : %d\n", node_buff_stack->size, node_buff_stack->current_buf->size);
        return NULL;
    }
    else{
        struct PiclNodeArray *node_array = PiclNodeArray_new(node_buff->size);

        for(int i = 0; i < node_buff->size; i++){
            node_array->value[i] = node_buff->data[i];
        }
        node_array->size = node_buff->size;

        debug_print("PiclNodeArray_pop after %d : %d\n", node_buff_stack->size, node_buff_stack->current_buf->size);
        return node_array;
    }
}

void PiclNodeBuff_new(struct PiclNodeBuffStack *node_buff_stack)
{
    if(node_buff_stack->size >= NODE_BUFF_STACK_DATA_SIZE){
        printf("Exception : node buff stack size was over limit\n");
        exit(1);
    }
    node_buff_stack->current_buf = PiclNodeBuff_init(&node_buff_stack->data[node_buff_stack->size++]);
    debug_print("PiclNodeBuffStack_new %d\n", node_buff_stack->size);
}

void PiclNodeBuffStack_push(struct PiclNodeBuffStack *node_buff_stack, struct PiclNode *node)
{
    if(node_buff_stack->current_buf->size >= NODE_BUFF_DATA_SIZE){
        printf("Exception : node buff size was over limit\n");
        exit(1);
    }
    node_buff_stack->current_buf->data[node_buff_stack->current_buf->size++] = node;
    debug_print("PiclNodeBuffStack_push %d\n", node_buff_stack->current_buf->size);
}

struct PiclNode_FuncHead *PiclNode_FuncHead_new(struct PiclStr *name, struct PiclNodeArray *args, struct PiclNodeArray *keyword_args)
{
    struct PiclNode_FuncHead *func_head = malloc(sizeof(struct PiclNode_FuncHead));
    func_head->name = name;
    func_head->args = args;
    func_head->keyword_args = keyword_args;
    return func_head;
}

struct PiclNode_FuncBody *PiclNode_FuncBody_new(struct PiclNodeArray *body, struct PiclNodeArray *lets)
{
    struct PiclNode_FuncBody *func_body = malloc(sizeof(struct PiclNode_FuncBody));
    func_body->body = body;
    func_body->lets = lets;
    return func_body;
}

struct PiclNode *PiclNode_new()
{
    struct PiclNode *node = malloc(sizeof(struct PiclNode));
//    printf("call malloc PiclNode\n");
    return node;
}

struct PiclNode *PiclNode_newClassKind(NodeType node_type, struct PiclStr *name, struct PiclNodeArray *extentions, struct PiclNodeArray *members)
{
    struct PiclNode *node = PiclNode_new();
    node->node_type = node_type;
    node->node_data_type = NodeDataType_ClassKind;

    node->class_kind_node.name = name;
    node->class_kind_node.decl_name_index = -1;
    node->class_kind_node.class_name_index = -1;

    int fields_size = 0;
    int methods_size = 0;
    int catchs_size = 0;

    for(int i = 0; i < members->size; i++){
        switch(members->value[i]->node_type){
            case NodeType_Field:
                ++fields_size;
                break;

            case NodeType_Method:
                ++methods_size;
                break;

            case NodeType_Alias:
                break;

            case NodeType_Catch:
                ++catchs_size;
                break;

            default:
                printf("Exception : PiclNode_newClassKind not member %d\n", members->value[i]->node_type);
                exit(1);
        }
    }
    struct PiclNodeArray *fields = NULL;
    struct PiclNodeArray *methods = NULL;
    struct PiclNodeArray *catches = NULL;

    if(fields_size > 0) fields = PiclNodeArray_new(fields_size);
    if(methods_size > 0) methods = PiclNodeArray_new(methods_size);
    if(catchs_size > 0) catches = PiclNodeArray_new(catchs_size);

    int fields_index = 0;
    int methods_index = 0;
    int catches_index = 0;

    for(int i = 0; i < members->size; i++){
        switch(members->value[i]->node_type){
            case NodeType_Field:
                fields->value[fields_index++] = members->value[i];
                break;

            case NodeType_Method:
                methods->value[methods_index++] = members->value[i];
                break;

            case NodeType_Catch:
                catches->value[catches_index++] = members->value[i];
                break;

            default:
                printf("Exception : PiclNode_newClassKind not member %d\n", members->value[i]->node_type);
                exit(1);
        }
    }


    node->class_kind_node.fields = fields;
    node->class_kind_node.methods = methods;
    node->class_kind_node.catches = catches;

    return node;
}

struct PiclNode *PiclNode_newFunction(struct PiclNode_FuncHead *head, struct PiclNode_FuncBody *func_body)
{
    struct PiclNode *node = PiclNode_new();
    node->node_type = NodeType_Function;
    node->node_data_type = NodeDataType_Function;

    node->function_node.args_size = 0;
    node->function_node.variables_size = 0;

    // head と bodyはもうつかわないので開放すること 

    node->function_node.name = head->name;
    node->function_node.name_index = -1;

    if(head->args != NULL){
        node->function_node.args = head->args;
    }

    // keyword argはどうしよう

    node->function_node.body = func_body->body;
    if(func_body->lets != NULL){
        node->function_node.lets = func_body->lets;
    }

    return node;
}

struct PiclNode *PiclNode_newLet(struct PiclNode_FuncHead *head, struct PiclNodeArray *nodes)
{
    struct PiclNode *node = PiclNode_new();
    node->node_type = NodeType_Let;
    node->node_data_type = NodeDataType_Function;

    node->function_node.args_size = 0;
    node->function_node.variables_size = 0;

    // head と bodyはもうつかわないので開放すること 

    node->function_node.name = head->name;
    node->function_node.name_index = -1;

    if(head->args != NULL){
        node->function_node.args = head->args;
    }

    // keyword argはどうしよう

    node->function_node.body = nodes;

    return node;
}

struct PiclNode *PiclNode_newField(MemberScope scope, struct PiclStr *name, struct PiclNode *value)
{
    struct PiclNode *node = PiclNode_new();
    node->node_type = NodeType_Field;
    node->node_data_type = NodeDataType_Field;

    node->field_node.scope = scope;
    node->field_node.name = name;
    node->field_node.value = value;

    return node;
}
struct PiclNode *PiclNode_newMethod(MemberScope scope, struct PiclNode_FuncHead *head, struct PiclNode_FuncBody *func_body)
{
    struct PiclNode *node = PiclNode_new();
    node->node_type = NodeType_Method;
    node->node_data_type = NodeDataType_Method;

    node->method_node.args_size = 0;
    node->method_node.variables_size = 0;

    node->method_node.scope = scope;

    // head と bodyはもうつかわないので開放すること 

    node->method_node.name = head->name;
    node->method_node.name_index = -1;

    if(head->args != NULL){
        node->method_node.args = head->args;
    }

    // keyword argはどうしよう

    node->method_node.body = func_body->body;
    if(func_body->lets != NULL){
        node->method_node.lets = func_body->lets;
    }

    return node;
}
struct PiclNode *PiclNode_newAlias(struct PiclStr *name, struct PiclNode *value)
{
    struct PiclNode *node = PiclNode_new();
    node->node_type = NodeType_Alias;
    node->node_data_type = NodeDataType_Alias;

    node->field_node.name = name;
    node->field_node.value = value;

    return node;
}

struct PiclNode *PiclNode_newCatch(struct PiclNode_FuncHead *head, struct PiclNode_FuncBody *func_body)
{
    struct PiclNode *node = PiclNode_new();
    node->node_type = NodeType_Catch;
    node->node_data_type = NodeDataType_Catch;

    node->catch_node.args_size = 0;
    node->catch_node.variables_size = 0;

    // head と bodyはもうつかわないので開放すること 

    node->catch_node.name = head->name;
    node->catch_node.name_index = -1;

    if(head->args != NULL){
        node->catch_node.args = head->args;
    }

    // keyword argはどうしよう

    node->catch_node.body = func_body->body;
    if(func_body->lets != NULL){
        node->catch_node.lets = func_body->lets;
    }

    return node;
}

struct PiclNode *PiclNode_newCallFunc(NodeType node_type, struct PiclNode *func, struct PiclNodeArray *args)
{
    if(func->node_type == NodeType_Op_Dot){

        struct PiclNode *new_node = PiclNode_new();

        switch(node_type){
            case NodeType_CallFuncArg:
                if(PiclStr_equalsConst(func->naming_node.name, "new")){
                    new_node->node_type = NodeType_CallMethodNewArg;
                }
                else{
                    new_node->node_type = NodeType_CallMethodArg;
                }
                break;

            case NodeType_CallFuncStmt:
                if(PiclStr_equalsConst(func->naming_node.name, "new")){
                    new_node->node_type = NodeType_CallMethodNewStmt;
                }
                else{
                    new_node->node_type = NodeType_CallMethodStmt;
                }
                break;

            default:
                printf("Exception : PiclNode_newCallFunc %d\n", node_type);
                exit(1);
        }

        new_node->node_data_type = NodeDataType_CallMethod;
        new_node->call_method_node.name = func->naming_node.name;
        new_node->call_method_node.node = func->naming_node.node;
        new_node->call_method_node.args = args;
        return new_node;
    }
    else{
        struct PiclNode *new_node = PiclNode_new();
        new_node->node_type = node_type;
        new_node->node_data_type = NodeDataType_CallFunc;
        new_node->call_func_node.func = func;
        new_node->call_func_node.args = args;
        return new_node;
    }
}

struct PiclNode *PiclNode_newNodes(NodeType node_type, struct PiclNodeArray *nodes)
{
    struct PiclNode *new_node = PiclNode_new();
    new_node->node_type = node_type;
    new_node->node_data_type = NodeDataType_Nodes;
    new_node->stmts_node.nodes = nodes;
    return new_node;
}
struct PiclNode *PiclNode_newOneArgListStmt(NodeType node_type, struct PiclStr *name, struct PiclNodeArray *nodes)
{
    struct PiclNode *new_node = PiclNode_new();
    new_node->node_type = node_type;
    new_node->node_data_type = NodeDataType_OneArgListStmt;
    new_node->one_arg_list_stmt_node.name = name;
    new_node->one_arg_list_stmt_node.nodes = nodes;
    return new_node;
}
struct PiclNode *PiclNode_newTwoArgListStmt(NodeType node_type, struct PiclStr *name1, struct PiclStr *name2, struct PiclNodeArray *nodes)
{
    struct PiclNode *new_node = PiclNode_new();
    new_node->node_type = node_type;
    new_node->node_data_type = NodeDataType_TwoArgListStmt;
    new_node->two_arg_list_stmt_node.name1 = name1;
    new_node->two_arg_list_stmt_node.name2 = name2;
    new_node->two_arg_list_stmt_node.nodes = nodes;
    return new_node;
}
struct PiclNode *PiclNode_setListStmtCond(struct PiclNode *list_stmt, struct PiclNode *cond)
{
    switch(list_stmt->node_data_type){
        case NodeDataType_OneArgListStmt:
            list_stmt->one_arg_list_stmt_node.cond = cond;
            break;

        case NodeDataType_TwoArgListStmt:
            list_stmt->two_arg_list_stmt_node.cond = cond;
            break;

        default:
            printf("Exception : PiclNode_setListStmtCond %d\n", list_stmt->node_data_type);
            exit(1);
    }

    return list_stmt;
}

struct PiclNode *PiclNode_newCondBinary(NodeType node_type, struct PiclNode *cond, struct PiclNodeArray *left, struct PiclNodeArray *right)
{
    struct PiclNode *new_node = PiclNode_new();
    new_node->node_type = node_type;
    new_node->node_data_type = NodeDataType_CondBinary;
    new_node->cond_binary_node.cond = cond;
    new_node->cond_binary_node.left = left;
    new_node->cond_binary_node.right = right;
    return new_node;
}
struct PiclNode *PiclNode_newCondUnary(NodeType node_type, struct PiclNode *cond, struct PiclNodeArray *nodes)
{
    struct PiclNode *new_node = PiclNode_new();
    new_node->node_type = node_type;
    new_node->node_data_type = NodeDataType_CondUnary;
    new_node->cond_unary_node.cond = cond;
    new_node->cond_unary_node.nodes = nodes;
    return new_node;
}
struct PiclNode *PiclNode_newBinary(NodeType node_type, struct PiclNode *left, struct PiclNode *right)
{
    struct PiclNode *new_node = PiclNode_new();
    new_node->node_type = node_type;
    new_node->node_data_type = NodeDataType_Binary;
    new_node->binary_node.left = left;
    new_node->binary_node.right = right;
    return new_node;
}
struct PiclNode *PiclNode_newUnary(NodeType node_type, struct PiclNode *value)
{
    struct PiclNode *new_node = PiclNode_new();
    new_node->node_type = node_type;
    new_node->node_data_type = NodeDataType_Unary;
    new_node->unary_node.node = value;
    return new_node;
}
struct PiclNode *PiclNode_newAtom(NodeType node_type)
{
    struct PiclNode *new_node = PiclNode_new();
    new_node->node_type = node_type;
    new_node->node_data_type = NodeDataType_Atom;
    return new_node;
}
struct PiclNode *PiclNode_newIdent(NodeType node_type, struct PiclStr *name)
{
    struct PiclNode *new_node = PiclNode_new();
    new_node->node_type = node_type;
    new_node->node_data_type = NodeDataType_Ident;
    new_node->ident_node.name = name;
    return new_node;
}
struct PiclNode *PiclNode_newNaming(NodeType node_type, struct PiclStr *name, struct PiclNode *node)
{
    struct PiclNode *new_node = PiclNode_new();
    new_node->node_type = node_type;
    new_node->node_data_type = NodeDataType_Naming;
    new_node->naming_node.name = name;
    new_node->naming_node.node = node;
    return new_node;
}
struct PiclNode *PiclNode_newStr(struct PiclStr *value)
{
    struct PiclNode *new_node = PiclNode_new();
    new_node->node_type = NodeType_Str;
    new_node->node_data_type = NodeDataType_Str;
    new_node->str_node.str_value = value;
    return new_node;
}
struct PiclNode *PiclNode_newInt(PiclInt value)
{
    struct PiclNode *new_node = PiclNode_new();
    new_node->node_type = NodeType_Int;
    new_node->node_data_type = NodeDataType_Int;
    new_node->int_node.int_value = value;
    return new_node;
}

void PiclMemberNode_delete(struct PiclNode *members)
{
}

void PiclNodeArray_delete(struct PiclNodeArray *nodes)
{
    for(int i = 0; i < nodes->size; i++){
        PiclNode_delete(nodes->value[i]);
    }
}

void PiclNode_delete(struct PiclNode *node)
{
    switch (node->node_data_type) {
        case NodeDataType_ClassKind:
            PiclStr_delete(node->class_kind_node.name);
            PiclNodeArray_delete(node->class_kind_node.fields);
            PiclNodeArray_delete(node->class_kind_node.methods);
            PiclNodeArray_delete(node->class_kind_node.catches);
            PiclNodeArray_delete(node->class_kind_node.options);
            break;

        case NodeDataType_Field:
        case NodeDataType_Method:
        case NodeDataType_Alias:
        case NodeDataType_Catch:
        case NodeDataType_Function:
        case NodeDataType_CallFunc:
        case NodeDataType_CallMethod:

        case NodeDataType_Nodes:
            PiclNodeArray_delete(node->cond_unary_node.nodes);
            break;

        case NodeDataType_OneArgListStmt:
            PiclStr_delete(node->one_arg_list_stmt_node.name);
            PiclNodeArray_delete(node->one_arg_list_stmt_node.nodes);
            break;
        case NodeDataType_TwoArgListStmt:
            PiclStr_delete(node->two_arg_list_stmt_node.name1);
            PiclStr_delete(node->two_arg_list_stmt_node.name2);
            PiclNodeArray_delete(node->two_arg_list_stmt_node.nodes);
            break;
        case NodeDataType_CondBinary:
            PiclNode_delete(node->cond_unary_node.cond);
            PiclNodeArray_delete(node->cond_binary_node.left);
            PiclNodeArray_delete(node->cond_binary_node.right);
            break;
        case NodeDataType_CondUnary:
            PiclNode_delete(node->cond_unary_node.cond);
            PiclNodeArray_delete(node->cond_unary_node.nodes);
            break;
        case NodeDataType_Binary:
            PiclNode_delete(node->binary_node.left);
            PiclNode_delete(node->binary_node.right);
            break;
        case NodeDataType_Unary:
            PiclNode_delete(node->unary_node.node);
            break;
        case NodeDataType_Ident:
            PiclStr_delete(node->ident_node.name);
            break;
        case NodeDataType_Atom:
            break;
        case NodeDataType_Naming:
            PiclStr_delete(node->naming_node.name);
            PiclNode_delete(node->naming_node.node);
            break;
        case NodeDataType_Str:
            PiclStr_delete(node->str_node.str_value);
            break;
        case NodeDataType_Int:
            break;
    }
    free(node);
}
