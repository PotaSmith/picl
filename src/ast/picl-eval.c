# include "picl-node.h"
# include "picl-optimize.h"
# include "picl-runtime.h"

struct PiclObject *Picl_eval_node(struct PiclNode *node, struct PiclRuntime *runtime);
struct PiclObject *Picl_eval_nodes(struct PiclNodeArray *nodes, struct PiclRuntime *runtime);

void PiclObject_Stream(struct PiclObject *picl_obj, FILE *stream)
{
    switch (picl_obj->type) {
        case ObjectType_int:
            fprintf(stream, "%" PRId64, picl_obj->int_obj.value);
            break;
        case ObjectType_bool:
            if(picl_obj->bool_obj.value){
                fprintf(stream, "true");
            }
            else{
                fprintf(stream, "false");
            }
            break;
        case ObjectType_str:
            fprintf(stream, "%s", picl_obj->str_obj.value->value);
            break;
        case ObjectType_func:
            break;
        case ObjectType_class:
            break;
        case ObjectType_field:
            break;
        case ObjectType_method:
            break;
        case ObjectType_instance:
            break;
    }
}

void PiclObject_to_str(struct PiclObject *picl_obj, struct PiclStrBuf *strbuf)
{
    char buffer [64];
    int size = 0;
    int i;

    switch (picl_obj->type) {
        case ObjectType_int:

            sprintf(buffer, "%" PRId64, picl_obj->int_obj.value);

            for(; size < 63; size++){
                if(buffer[size] == '\0') break;
                PiclStrBuf_append(strbuf, buffer[size]);
            }
            break;
        case ObjectType_bool:
            if(picl_obj->bool_obj.value){
                PiclStrBuf_append(strbuf, 't');
                PiclStrBuf_append(strbuf, 'r');
                PiclStrBuf_append(strbuf, 'u');
                PiclStrBuf_append(strbuf, 'e');
            }
            else{
                PiclStrBuf_append(strbuf, 'f');
                PiclStrBuf_append(strbuf, 'a');
                PiclStrBuf_append(strbuf, 'l');
                PiclStrBuf_append(strbuf, 's');
                PiclStrBuf_append(strbuf, 'e');
            }
            break;
        case ObjectType_str:
            for(i = 0; i < picl_obj->str_obj.value->length; i++){
                PiclStrBuf_append(strbuf, picl_obj->str_obj.value->value[i]);
            }
            break;
        case ObjectType_func:
            break;
        case ObjectType_class:
            break;
        case ObjectType_field:
            break;
        case ObjectType_method:
            break;
        case ObjectType_instance:
            break;
    }
}
PiclInt PiclObject_to_int(struct PiclObject *picl_obj, struct PiclRuntime *runtime)
{
    switch (picl_obj->type) {
        case ObjectType_int:
            return picl_obj->int_obj.value;
        case ObjectType_bool:
            break;
        case ObjectType_str:{
            return strtoimax(picl_obj->str_obj.value->value, NULL, 0);
        }
        case ObjectType_func:
            break;
        case ObjectType_class:
            break;
        case ObjectType_field:
            break;
        case ObjectType_method:
            break;
        case ObjectType_instance:
            break;
    }
    return 0;
}
struct PiclObject *Picl_str_join(struct PiclObject *left, struct PiclObject *right, struct PiclRuntime *runtime)
{
    switch (left->type) {
        case ObjectType_int:{
            struct PiclStrBuf *strbuf = PiclStrBuf_new();
            PiclStrBuf_init(strbuf);


            PiclObject_to_str(left, strbuf);
            PiclObject_to_str(right, strbuf);

            struct PiclStr *new_str;
            PiclStrBuf_toStr(strbuf, &new_str);

            return PiclObject_new_str(&runtime->object_heap, new_str);
        }
        case ObjectType_bool:{
            struct PiclStrBuf *strbuf = PiclStrBuf_new();
            PiclStrBuf_init(strbuf);

            PiclObject_to_str(left, strbuf);
            PiclObject_to_str(right, strbuf);

            struct PiclStr *new_str;
            PiclStrBuf_toStr(strbuf, &new_str);

            return PiclObject_new_str(&runtime->object_heap, new_str);
        }
        case ObjectType_str:{
            struct PiclStrBuf *strbuf = PiclStrBuf_new();
            PiclStrBuf_init(strbuf);

            PiclObject_to_str(left, strbuf);
            PiclObject_to_str(right, strbuf);

            struct PiclStr *new_str;
            PiclStrBuf_toStr(strbuf, &new_str);

            return PiclObject_new_str(&runtime->object_heap, new_str);
        }
        case ObjectType_func:
            break;
        case ObjectType_class:
            break;
        case ObjectType_field:
            break;
        case ObjectType_method:
            break;
        case ObjectType_instance:
            break;
    }
    return NULL;
}

/*
 * call
 */

struct PiclFrame *PiclNode_set_argument(struct PiclNodeArray *args, struct PiclFrame *frame, struct PiclRuntime *runtime)
{
    debug_print("PiclNode_set_argument eval start");
    debug_obj(frame->this_obj);

    struct PiclObject *result;
    for(int i = 0; i < args->size; i++){
        result = Picl_eval_node(args->value[i], runtime);
        PiclFrame_add_argument(frame, result);
    }
    debug_print("PiclNode_set_argument eval end");
    debug_obj(frame->this_obj);

    return frame;
}

struct PiclObject *PiclObject_call(struct PiclObject *func_obj, struct PiclFrame *frame, struct PiclRuntime *runtime)
{
    struct PiclObject *result;

    PiclRuntime_push_Frame(runtime, frame);

    debug_print("PiclObject_call FuncObj");
    debug_obj(func_obj);

    switch (func_obj->type) {
        case ObjectType_func:
            Picl_eval_nodes(func_obj->func_obj.body, runtime);
            break;
        case ObjectType_method:
            Picl_eval_nodes(func_obj->func_obj.body, runtime);
            break;
        case ObjectType_int:
            printf("Exception : call int object %lld\n", func_obj->int_obj.value);
            exit(1);
            break;
        case ObjectType_bool:
            printf("Exception : call bool object\n");
            exit(1);
            break;
        case ObjectType_str:
            printf("Exception : call str object\n");
            exit(1);
            break;
        default: 
            printf("Exception : call not func object\n");
            exit(1);
    }

    PiclRuntime_pop_Frame(runtime);

    result = PiclRuntime_get_result(runtime);
    PiclRuntime_push_Stack(runtime, result);
    return result;
}

void PiclObject_call_entry(struct PiclRuntime *runtime, int main_index)
{
    debug_print("start main %d\n", main_index);

    struct PiclObject *func_obj = PiclRuntime_get_decl(runtime, main_index);

    if(func_obj == NULL){
        printf("Exception : main not found\n");
        exit(1);
    }

    if(func_obj->func_obj.args != NULL){
        printf("Exception : main could not has argument\n");
    }

    struct PiclFrame *frame = PiclRuntime_new_Frame(runtime, NULL, func_obj->func_obj.args_size, func_obj->func_obj.variables_size);

    PiclObject_call(func_obj, frame, runtime);
}

struct PiclObject *PiclNode_callFunc(struct PiclNode *node, struct PiclRuntime *runtime)
{
    struct PiclFrame *frame;
    struct PiclObject *func_obj = Picl_eval_node(node->call_func_node.func, runtime);

    if(func_obj->type == ObjectType_method){
        debug_print("call func %s\n", func_obj->func_obj.name->value);
        frame = PiclRuntime_new_ObjectFrame(runtime, func_obj->func_obj.args_size, func_obj->func_obj.variables_size);
    }
    else{
        debug_print("call func %s\n", func_obj->func_obj.name->value);
        frame = PiclRuntime_new_Frame(runtime, NULL, func_obj->func_obj.args_size, func_obj->func_obj.variables_size);
    }

    if(node->call_func_node.args != NULL){
        debug_print("PiclNode_set_argument: before this obj");
        debug_obj(frame->this_obj);
        PiclNode_set_argument(node->call_func_node.args, frame, runtime);
        debug_print("PiclNode_set_argument: after this obj");
        debug_obj(frame->this_obj);
    }

    return PiclObject_call(func_obj, frame, runtime);
}

struct PiclObject *PiclNode_callMethod(struct PiclNode *node, struct PiclRuntime *runtime)
{
    struct PiclObject *result;
    struct PiclFrame *frame;

    struct PiclObject *obj = Picl_eval_node(node->call_method_node.node, runtime);
    debug_print("PiclNode_callMethod: obj");
    debug_obj(obj);

    struct PiclObject *method_obj = NULL;
    switch (obj->type) {
        case ObjectType_class:
            method_obj = PiclRuntime_get_method(runtime, obj->class_obj.class_name_index, node->call_method_node.name_index);
            break;
        case ObjectType_instance:
            method_obj = PiclRuntime_get_method(runtime, obj->instance.class_obj->class_obj.class_name_index, node->call_method_node.name_index);
            break;
        default: 
            printf("Exception : call not class method");
            debug_obj(obj);
            exit(1);
    }


    switch (node->node_type) {
        case NodeType_CallMethodArg:
            if(method_obj == NULL){
                printf("Exception : method not found: %d, %d\n", obj->class_obj.class_name_index, node->call_method_node.name_index);
            }
            frame = PiclRuntime_new_Frame(runtime, obj, method_obj->method_obj.args_size, method_obj->method_obj.variables_size);

            if(node->call_method_node.args != NULL){
                debug_print("PiclNode_set_argument: before this obj");
                debug_obj(frame->this_obj);
                PiclNode_set_argument(node->call_method_node.args, frame, runtime);
                debug_print("PiclNode_set_argument: after this obj");
                debug_obj(frame->this_obj);
            }

            return PiclObject_call(method_obj, frame, runtime);
        case NodeType_CallMethodNewArg:
            result = PiclObject_new_instance(&runtime->object_heap, obj);
            PiclRuntime_push_Stack(runtime, result);
            debug_print("PiclObject_new_instance:");
            debug_obj(obj);

            if(method_obj == NULL){
                debug_print("call empty new\n");
                PiclObjectHeap_release(&runtime->object_heap, obj);
                return result;
            }

            frame = PiclRuntime_new_Frame(runtime, result, method_obj->method_obj.args_size, method_obj->method_obj.variables_size);

            if(node->call_method_node.args != NULL){
                debug_print("PiclNode_set_argument: before this obj");
                debug_obj(frame->this_obj);
                PiclNode_set_argument(node->call_method_node.args, frame, runtime);
                debug_print("PiclNode_set_argument: after this obj");
                debug_obj(frame->this_obj);
            }

            PiclObject_call(method_obj, frame, runtime);
            PiclObjectHeap_release(&runtime->object_heap, obj);

            return result;
        default: 
            printf("Exception : call not method node\n");
            exit(1);
    }
}


/*
 * eval
 */

void Picl_eval_field_node(struct PiclNode *class_node, struct PiclObject *class_obj, struct PiclNode *node, struct PiclRuntime *runtime, int index)
{
    if(node->node_type != NodeType_Field) {
        printf("Exception : eval member %d\n", node->node_type);
        exit(1);
    }

    struct PiclObject *member_obj = PiclObject_new_field(
        &runtime->object_heap,
        class_obj,
        node->field_node.name,
        node->field_node.value
    );
    PiclRuntime_set_field(
        runtime,
        class_node->class_kind_node.class_name_index,
        node->field_node.name_index,
        index
    );
    class_obj->class_obj.fields[index] = member_obj;
}
void Picl_eval_method_node(struct PiclNode *class_node, struct PiclObject *class_obj, struct PiclNode *node, struct PiclRuntime *runtime, int index)
{
    if(node->node_type != NodeType_Method) {
        printf("Exception : eval method %d\n", node->node_type);
        exit(1);
    }

    struct PiclObject *member_obj = PiclObject_new_method(
        &runtime->object_heap,
        class_obj,
        node->method_node.name,
        node->method_node.args,
        node->method_node.body,
        node->method_node.args_size,
        node->method_node.variables_size,
        0,
        0
    );
    PiclRuntime_set_method(
        runtime,
        class_node->class_kind_node.class_name_index,
        node->method_node.name_index,
        member_obj
    );
    class_obj->class_obj.methods[index] = member_obj;
}

struct PiclObject *Picl_eval_node(struct PiclNode *node, struct PiclRuntime *runtime)
{
    struct PiclObject *result = NULL;
    struct PiclObject *value1 = NULL;
    struct PiclObject *value2 = NULL;

    switch (node->node_type) {
        case NodeType_Function:
            PiclRuntime_set_decl(
                runtime,
                node->function_node.name_index,
                PiclObject_new_function(
                    &runtime->object_heap,
                    node->function_node.name,
                    node->function_node.name_index,
                    node->function_node.args,
                    node->function_node.body,
                    node->function_node.args_size,
                    node->function_node.variables_size,
                    0,
                    0
                )
            );
            break;

        case NodeType_Class:
            result = PiclObject_new_class(
                &runtime->object_heap,
                node->class_kind_node.name,
                node->class_kind_node.decl_name_index,
                node->class_kind_node.class_name_index,
                (node->class_kind_node.fields == NULL ? 0 : node->class_kind_node.fields->size),
                (node->class_kind_node.methods == NULL ? 0 : node->class_kind_node.methods->size)
            );
            PiclRuntime_set_decl(
                runtime,
                node->class_kind_node.decl_name_index,
                result
            );

            if(node->class_kind_node.fields != NULL){
                for(int i = 0; i < node->class_kind_node.fields->size; i++){
                    Picl_eval_field_node(node, result, node->class_kind_node.fields->value[i], runtime, i);
                }
            }
            if(node->class_kind_node.methods != NULL){
                for(int i = 0; i < node->class_kind_node.methods->size; i++){
                    Picl_eval_method_node(node, result, node->class_kind_node.methods->value[i], runtime, i);
                }
            }

            break;

        case NodeType_CallFuncArg:
            debug_print("\nNodeType_CallFuncArg start\n");
            result = PiclNode_callFunc(node, runtime);
            debug_print("NodeType_CallFuncArg end");
            debug_obj(result);
            debug_print("\n\n");
            break;

        case NodeType_CallMethodArg:
            debug_print("\nNodeType_CallMethodArg: start method name %s\n", node->call_method_node.name->value);
            result = PiclNode_callMethod(node, runtime);
            debug_print("NodeType_CallMethodArg end");
            debug_obj(result);
            debug_print("\n\n");
            break;

        case NodeType_CallMethodNewArg:
            debug_print("\nNodeType_CallMethodNewArg: start method name %s\n", node->call_method_node.name->value);
            result = PiclNode_callMethod(node, runtime);
            debug_print("NodeType_CallMethodNewArg end: start method name %s", node->call_method_node.name->value);
            debug_obj(result);
            debug_print("\n\n");
            break;

        case NodeType_IfElse:
            result = Picl_eval_node(node->cond_binary_node.cond, runtime);
            debug_print("NodeType_IfElse:");
            debug_obj(result);

            if(result == trueObject){
                result = Picl_eval_nodes(node->cond_binary_node.left, runtime);
            }
            else{
                result = Picl_eval_nodes(node->cond_binary_node.right, runtime);
            }
            break;

        case NodeType_If:
            result = Picl_eval_node(node->cond_unary_node.cond, runtime);
            debug_print("NodeType_If:");
            debug_obj(result);

            if(result == trueObject){
                result = Picl_eval_nodes(node->cond_unary_node.nodes, runtime);
            }
            break;

        case NodeType_Op_StrJoin:
            result = Picl_str_join(Picl_eval_node(node->binary_node.left, runtime), Picl_eval_node(node->binary_node.right, runtime), runtime);
            PiclRuntime_push_Stack(runtime, result);
            break;

        case NodeType_Op_Add:
            debug_print("NodeType_Op_Add:");
            debug_obj(result);
            result = PiclObject_new_int(&runtime->object_heap,
                PiclObject_to_int(Picl_eval_node(node->binary_node.left, runtime), runtime)
                    + PiclObject_to_int(Picl_eval_node(node->binary_node.right, runtime), runtime));

            PiclRuntime_push_Stack(runtime, result);
            break;

        case NodeType_Op_Sub:
            debug_print("NodeType_Op_Sub:");
            debug_obj(result);
            result = PiclObject_new_int(&runtime->object_heap,
                PiclObject_to_int(Picl_eval_node(node->binary_node.left, runtime), runtime)
                    - PiclObject_to_int(Picl_eval_node(node->binary_node.right, runtime), runtime));

            PiclRuntime_push_Stack(runtime, result);
            break;
        
        case NodeType_Op_Mul:
            result = PiclObject_new_int(&runtime->object_heap, 
                PiclObject_to_int(Picl_eval_node(node->binary_node.left, runtime), runtime)
                    * PiclObject_to_int(Picl_eval_node(node->binary_node.right, runtime), runtime));

            PiclRuntime_push_Stack(runtime, result);
            break;
        
        case NodeType_Op_Div:
            result = PiclObject_new_int(&runtime->object_heap, 
                PiclObject_to_int(Picl_eval_node(node->binary_node.left, runtime), runtime)
                    / PiclObject_to_int(Picl_eval_node(node->binary_node.right, runtime), runtime));

            PiclRuntime_push_Stack(runtime, result);
            break;
        
        case NodeType_Op_Mod:
            result = PiclObject_new_int(&runtime->object_heap, 
                PiclObject_to_int(Picl_eval_node(node->binary_node.left, runtime), runtime)
                    % PiclObject_to_int(Picl_eval_node(node->binary_node.right, runtime), runtime));

            PiclRuntime_push_Stack(runtime, result);
            break;

        case NodeType_Op_Equal:
            value1 = Picl_eval_node(node->binary_node.left, runtime);
            value2 = Picl_eval_node(node->binary_node.right, runtime);
            break;

        case NodeType_Op_NotEqual:
            value1 = Picl_eval_node(node->binary_node.left, runtime);
            value2 = Picl_eval_node(node->binary_node.right, runtime);
            break;

        case NodeType_Op_GtEqual:
            if(PiclObject_to_int(Picl_eval_node(node->binary_node.left, runtime), runtime)
                 >= PiclObject_to_int(Picl_eval_node(node->binary_node.right, runtime), runtime)){
                result = trueObject;
            }
            else{
                result = falseObject;
            }
            break;

        case NodeType_Op_LtEqual:
            if(PiclObject_to_int(Picl_eval_node(node->binary_node.left, runtime), runtime)
                 <= PiclObject_to_int(Picl_eval_node(node->binary_node.right, runtime), runtime)){
                result = trueObject;
            }
            else{
                result = falseObject;
            }
            break;

        case NodeType_Op_Gt:
            if(PiclObject_to_int(Picl_eval_node(node->binary_node.left, runtime), runtime)
                 > PiclObject_to_int(Picl_eval_node(node->binary_node.right, runtime), runtime)){
                result = trueObject;
            }
            else{
                result = falseObject;
            }
            debug_print("NodeType_Op_Gt:");
            debug_obj(result);
            break;

        case NodeType_Op_Lt:
            if(PiclObject_to_int(Picl_eval_node(node->binary_node.left, runtime), runtime)
                < PiclObject_to_int(Picl_eval_node(node->binary_node.right, runtime), runtime)){
                result = trueObject;
            }
            else{
                result = falseObject;
            }
            debug_print("NodeType_Op_Lt:");
            debug_obj(result);
            break;

        case NodeType_Op_Assign:
            result = Picl_eval_node(node->binary_node.right, runtime);
            PiclRuntime_set_variable(runtime, node->binary_node.left->ident_node.name_index, result);
            debug_print("NodeType_Op_Assign:");
            debug_obj(result);
            break;

        case NodeType_Op_Assign_Arg:
            result = Picl_eval_node(node->binary_node.right, runtime);
            PiclRuntime_set_argument(runtime, node->binary_node.left->ident_node.name_index, result);
            debug_print("NodeType_Op_Assign_Arg:");
            debug_obj(result);
            break;

        case NodeType_Op_Assign_CurrentField:
            result = Picl_eval_node(node->binary_node.right, runtime);
            PiclRuntime_set_current_field(runtime, node->binary_node.left->ident_node.name_index, result);
            debug_print("NodeType_Op_Assign_CurrentField:");
            debug_obj(result);
            break;

        case NodeType_Op_Assign_Member:
            result = Picl_eval_node(node->binary_node.right, runtime);
            value1 = Picl_eval_node(node->binary_node.left->naming_node.node, runtime);
            PiclRuntime_set_member_field(runtime, value1, node->binary_node.left->naming_node.name_index, result);
            debug_print("NodeType_Op_Assign_Member:");
            debug_obj(result);
            break;

        case NodeType_Stmt_Return_Var:
            debug_print("NodeType_Stmt_Return_Var: start node type %d\n", node->unary_node.node->node_type);
            result = Picl_eval_node(node->unary_node.node, runtime);
            debug_print("NodeType_Stmt_Return_Var: return");
            debug_obj(result);
            PiclRuntime_set_result(runtime, result);
            break;

        case NodeType_Stmt_Echo_Var:
            result = Picl_eval_node(node->unary_node.node, runtime);
            PiclObject_Stream(result, runtime->echo_stream);
            break;

        case NodeType_Val_List_Var:
            Picl_eval_node(node->unary_node.node, runtime);
            break;

        case NodeType_Val_Dict_Var:
            Picl_eval_node(node->unary_node.node, runtime);
            break;

        case NodeType_Op_Minus:
            value1 = Picl_eval_node(node->unary_node.node, runtime);
            result = PiclObject_new_int(&runtime->object_heap, PiclObject_to_int(value1, runtime));
            PiclRuntime_push_Stack(runtime, result);
            break;

        case NodeType_Op_FuncLazy:
            Picl_eval_node(node->unary_node.node, runtime);
            break;

        case NodeType_Val_IdentGlobal:
            result = PiclRuntime_get_decl(runtime, node->ident_node.name_index);
            debug_print("NodeType_Val_IdentGlobal");
            debug_obj(result);
            break;
        case NodeType_Val_IdentCurrentField:
            result = PiclRuntime_get_current_field(runtime, node->ident_node.name_index);
            debug_print("NodeType_Val_IdentCurrentField");
            debug_obj(result);
            break;
        case NodeType_Val_IdentCurrentMethod:
            result = PiclRuntime_get_current_method(runtime, node->ident_node.name_index);
            debug_print("NodeType_Val_IdentCurrentMethod");
            debug_obj(result);
            break;
        case NodeType_Val_IdentArg:
            result = PiclRuntime_get_argument(runtime, node->ident_node.name_index);
            debug_print("NodeType_Val_IdentArg");
            debug_obj(result);
            break;
        case NodeType_Val_Ident:
            result = PiclRuntime_get_variable(runtime, node->ident_node.name_index);
            debug_print("NodeType_Val_Ident");
            debug_obj(result);
            break;

        case NodeType_Op_Dot:
            Picl_eval_node(node->naming_node.node, runtime);
            debug_print("NodeType_Op_Dot");
            debug_obj(result);
            break;

        case NodeType_Val_Var_Dict:
            Picl_eval_node(node->naming_node.node, runtime);
            break;

        case NodeType_Val_Str_Dict:
            Picl_eval_node(node->naming_node.node, runtime);
            break;

        case NodeType_Str:
            result = node->str_node.cache;
            debug_print("NodeType_Str");
            debug_obj(result);
            break;

        case NodeType_Int:
            result = node->str_node.cache;
            debug_print("NodeType_Int");
            debug_obj(result);
            break;

        default:
            printf("Exception : eval node type %d\n", node->node_type);
            exit(1);
    }
    return result;
}

struct PiclObject *Picl_eval_nodes(struct PiclNodeArray *nodes, struct PiclRuntime *runtime)
{
    if(nodes == NULL) return NULL;
    struct PiclObject *result = NULL;

    for(int i = 0; i < nodes->size; i++){
        result = Picl_eval_node(nodes->value[i], runtime);
    }

    return result;
}

void Picl_eval_program(struct PiclNodeArray *nodes)
{
    struct PiclOptimizeEnv *optimize_env = PiclOptimizeEnv_new();
    Picl_optimize_nodes(nodes, optimize_env);

    struct PiclRuntime *runtime = PiclRuntime_new(optimize_env);

    Picl_eval_nodes(nodes, runtime);

    printf("all_free_object_size %d\n", runtime->object_heap.all_free_object_size);
    printf("all_pool_object_size %d\n", runtime->object_heap.all_pool_object_size);

    int main_index = PiclOptimizeEnv_find_decl_name_index(optimize_env, PiclStr_newByConst("main"));

    debug_print("get main : %d\n", main_index);

    PiclObject_call_entry(runtime, main_index);

    debug_print("\n");

    printf("all_free_object_size %d\n", runtime->object_heap.all_free_object_size);
    printf("all_pool_object_size %d\n", runtime->object_heap.all_pool_object_size);

}
