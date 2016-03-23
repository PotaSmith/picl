#include "picl-node.h"
#include "picl-optimize.h"
#include "picl-compile-env.h"
#include "picl-vm.h"

int Picl_compile_node(struct PiclNode *node, struct PiclVmProgram *program, struct PiclVm *vm, struct PiclCompileEnv *compile_env);
void Picl_compile_nodes(struct PiclNodeArray *nodes, struct PiclVmProgram *program, struct PiclVm *vm, struct PiclCompileEnv *compile_env);

int Picl_compile_binary_node(struct PiclNode *node, PiclOpCode opcode, struct PiclVmProgram *program, struct PiclVm *vm, struct PiclCompileEnv *compile_env)
{
    int operand1 = Picl_compile_node(node->binary_node.left, program, vm, compile_env);
    int operand2 = Picl_compile_node(node->binary_node.right, program, vm, compile_env);

    PiclVmProgram_append(program, opcode, operand1, operand2, operand1);
    PiclCompileEnv_release_operand(compile_env, 1);
    return operand1;
}

int Picl_compile_unary_node(struct PiclNode *node, PiclOpCode opcode, struct PiclVmProgram *program, struct PiclVm *vm, struct PiclCompileEnv *compile_env)
{
    int operand1 = Picl_compile_node(node->unary_node.node, program, vm, compile_env);

    PiclVmProgram_append(program, opcode, operand1, 0, operand1);
    return operand1;
}

int Picl_compile_ident_node(struct PiclNode *node, PiclOpCode opcode, struct PiclVmProgram *program, struct PiclVm *vm, struct PiclCompileEnv *compile_env)
{
    int operand1 = PiclCompileEnv_use_operand(compile_env);
    PiclVmProgram_append(program, opcode, VM_STACK_FRAME_RESERVED_SIZE + node->ident_node.name_index, 0, operand1);
    return operand1;
}

/*
 * class field method
 */

void Picl_compile_field_node(struct PiclNode *node, struct PiclVmProgram *program, struct PiclVm *vm, struct PiclCompileEnv *compile_env, struct PiclNode *class_node, struct PiclObject *class_obj, int index)
{
    if(node->node_type != NodeType_Field) {
        printf("Exception : eval member %d\n", node->node_type);
        exit(1);
    }

    struct PiclObject *member_obj = PiclObject_new_field(
        &vm->object_heap,
        class_obj,
        node->field_node.name,
        node->field_node.value
    );
    PiclVm_set_field(
        vm,
        class_node->class_kind_node.class_name_index,
        node->field_node.name_index,
        index
    );
    class_obj->class_obj.fields[index] = member_obj;
}
void Picl_compile_method_node(struct PiclNode *node, struct PiclVmProgram *program, struct PiclVm *vm, struct PiclCompileEnv *compile_env, struct PiclNode *class_node, struct PiclObject *class_obj, int index)
{
    if(node->node_type != NodeType_Method) {
        printf("Exception : eval method %d\n", node->node_type);
        exit(1);
    }

    PiclCompileEnv_push(compile_env, node->method_node.args_size, node->method_node.variables_size);

    int start_index = PiclVmProgram_get_next_index(program);

    Picl_compile_nodes(node->method_node.body, program, vm, compile_env);
    PiclVmProgram_append(program, PiclOpCode_end_frame, 0, 0, 0);

    int all_operand_size = PiclCompileEnv_pop(compile_env);

    struct PiclObject *member_obj = PiclObject_new_method(
        &vm->object_heap,
        class_obj,
        node->method_node.name,
        node->method_node.args,
        node->method_node.body,
        node->method_node.args_size,
        node->method_node.variables_size,
        all_operand_size,
        start_index
    );
    PiclVm_set_method(
        vm,
        class_node->class_kind_node.class_name_index,
        node->method_node.name_index,
        member_obj
    );
    class_obj->class_obj.methods[index] = member_obj;
}





/*
 * compile
 */


int Picl_compile_node(struct PiclNode *node, struct PiclVmProgram *program, struct PiclVm *vm, struct PiclCompileEnv *compile_env)
{
    int operand1 = 0;
    int operand2 = 0;
    int start_index = 0;
    int all_operand_size = 0;
    struct PiclVmCode *code1 = NULL;
    struct PiclVmCode *code2 = NULL;
    struct PiclObject *object1 = NULL;

    switch (node->node_type) {
        case NodeType_Function:
            PiclCompileEnv_push(compile_env, node->function_node.args_size, node->function_node.variables_size);

            start_index = PiclVmProgram_get_next_index(program);

            Picl_compile_nodes(node->function_node.body, program, vm, compile_env);
            PiclVmProgram_append(program, PiclOpCode_end_frame, 0, 0, 0);

            all_operand_size = PiclCompileEnv_pop(compile_env);

            PiclVm_set_decl(
                vm,
                node->function_node.name_index,
                PiclObject_new_function(
                    &vm->object_heap,
                    node->function_node.name,
                    node->function_node.name_index,
                    node->function_node.args,
                    node->function_node.body,
                    node->function_node.args_size,
                    node->function_node.variables_size,
                    all_operand_size,
                    start_index
                )
            );
            break;

        case NodeType_Class:
            object1 = PiclObject_new_class(
                &vm->object_heap,
                node->class_kind_node.name,
                node->class_kind_node.decl_name_index,
                node->class_kind_node.class_name_index,
                (node->class_kind_node.fields == NULL ? 0 : node->class_kind_node.fields->size),
                (node->class_kind_node.methods == NULL ? 0 : node->class_kind_node.methods->size)
            );
            PiclVm_set_decl(
                vm,
                node->class_kind_node.decl_name_index,
                object1
            );

            if(node->class_kind_node.fields != NULL){
                for(int i = 0; i < node->class_kind_node.fields->size; i++){
                    Picl_compile_field_node(node->class_kind_node.fields->value[i], program, vm, compile_env, node, object1, i);
                }
            }
            if(node->class_kind_node.methods != NULL){
                for(int i = 0; i < node->class_kind_node.methods->size; i++){
                    Picl_compile_method_node(node->class_kind_node.methods->value[i], program, vm, compile_env, node, object1, i);
                }
            }
            break;

        case NodeType_CallFuncArg:
            if(node->call_func_node.args != NULL){
                for(int i = 0; i < node->call_func_node.args->size; i++){
                    operand1 = Picl_compile_node(node->call_func_node.args->value[i], program, vm, compile_env);
                    PiclVmProgram_append(program, PiclOpCode_set_arg, operand1, 0, i);
                    PiclCompileEnv_release_operand(compile_env, 1);
                }
            }

            operand1 = Picl_compile_node(node->call_func_node.func, program, vm, compile_env);

            PiclVmProgram_append(program, PiclOpCode_call_func, operand1, 0, 0);
            PiclVmProgram_append(program, PiclOpCode_get_return, 0, 0, operand1);
            break;

        case NodeType_CallMethodArg:
            operand1 = Picl_compile_node(node->call_method_node.node, program, vm, compile_env); // object

            if(node->call_method_node.args != NULL){
                for(int i = 0; i < node->call_method_node.args->size; i++){
                    operand2 = Picl_compile_node(node->call_method_node.args->value[i], program, vm, compile_env);
                    PiclVmProgram_append(program, PiclOpCode_set_arg, operand2, 0, i);
                    PiclCompileEnv_release_operand(compile_env, 1);
                }
            }

            PiclVmProgram_append(program, PiclOpCode_call_method, operand1, node->call_method_node.name_index, 0);
            PiclVmProgram_append(program, PiclOpCode_get_return, 0, 0, operand1);
            break;

        case NodeType_CallMethodNewArg:
            operand1 = Picl_compile_node(node->call_method_node.node, program, vm, compile_env); // object

            if(node->call_method_node.args != NULL){
                for(int i = 0; i < node->call_method_node.args->size; i++){
                    operand2 = Picl_compile_node(node->call_method_node.args->value[i], program, vm, compile_env);
                    PiclVmProgram_append(program, PiclOpCode_set_arg, operand2, 0, i);
                    PiclCompileEnv_release_operand(compile_env, 1);
                }
            }

            PiclVmProgram_append(program, PiclOpCode_call_method_new, operand1, node->call_method_node.name_index, 0);
            PiclVmProgram_append(program, PiclOpCode_get_new_instance, 0, 0, operand1);
            break;

        case NodeType_IfElse:
            operand1 = Picl_compile_node(node->cond_binary_node.cond, program, vm, compile_env);

            code1 = PiclVmProgram_append(program, PiclOpCode_if_else, operand1, PiclVmProgram_get_next_index(program), operand1);

            Picl_compile_nodes(node->cond_binary_node.right, program, vm, compile_env);

            code2 = PiclVmProgram_append(program, PiclOpCode_jump, PiclVmProgram_get_next_index(program), 0, 0);

            code1->src2 = PiclVmProgram_get_next_index(program) - code1->src2 - 1; // -1 は vmでnextが呼ばれるため

            Picl_compile_nodes(node->cond_binary_node.left, program, vm, compile_env);

            code2->src1 = PiclVmProgram_get_next_index(program) - code2->src1 - 1; // -1 は vmでnextが呼ばれるため
            
            PiclCompileEnv_release_operand(compile_env, 1);

            code2->dst1 = code1->src2;
            break;

        case NodeType_If:
            operand1 = Picl_compile_node(node->cond_unary_node.cond, program, vm, compile_env);

            code1 = PiclVmProgram_append(program, PiclOpCode_if, operand1, PiclVmProgram_get_next_index(program), operand1);

            Picl_compile_nodes(node->cond_unary_node.nodes, program, vm, compile_env);

            code1->src2 = PiclVmProgram_get_next_index(program) - code1->src2 - 1; // -1 は vmでnextが呼ばれるため

            PiclCompileEnv_release_operand(compile_env, 1);

            break;

        case NodeType_Op_StrJoin:
            operand1 = Picl_compile_binary_node(node, PiclOpCode_str_join, program, vm, compile_env);
            break;

        case NodeType_Op_Add:
            operand1 = Picl_compile_binary_node(node, PiclOpCode_add, program, vm, compile_env);
            break;

        case NodeType_Op_Sub:
            operand1 = Picl_compile_binary_node(node, PiclOpCode_sub, program, vm, compile_env);
            break;
        
        case NodeType_Op_Mul:
            operand1 = Picl_compile_binary_node(node, PiclOpCode_mul, program, vm, compile_env);
            break;
        
        case NodeType_Op_Div:
            operand1 = Picl_compile_binary_node(node, PiclOpCode_div, program, vm, compile_env);
            break;
        
        case NodeType_Op_Mod:
            operand1 = Picl_compile_binary_node(node, PiclOpCode_mod, program, vm, compile_env);
            break;

        case NodeType_Op_Equal:
            break;

        case NodeType_Op_NotEqual:
            break;

        case NodeType_Op_GtEqual:
            operand1 = Picl_compile_binary_node(node, PiclOpCode_gt_equal, program, vm, compile_env);
            break;

        case NodeType_Op_LtEqual:
            operand1 = Picl_compile_binary_node(node, PiclOpCode_lt_equal, program, vm, compile_env);
            break;

        case NodeType_Op_Gt:
            operand1 = Picl_compile_binary_node(node, PiclOpCode_gt, program, vm, compile_env);
            break;

        case NodeType_Op_Lt:
            operand1 = Picl_compile_binary_node(node, PiclOpCode_lt, program, vm, compile_env);
            break;

        case NodeType_Op_Assign:
            operand1 = Picl_compile_node(node->binary_node.right, program, vm, compile_env);
            PiclVmProgram_append(program, PiclOpCode_assign_variable, operand1, 0, node->binary_node.left->ident_node.name_index);
            break;

        case NodeType_Op_Assign_Arg:
            operand1 = Picl_compile_node(node->binary_node.right, program, vm, compile_env);
            PiclVmProgram_append(program, PiclOpCode_assign_argument, operand1, 0, node->binary_node.left->ident_node.name_index);
            break;

        case NodeType_Op_Assign_CurrentField:
            operand1 = Picl_compile_node(node->binary_node.right, program, vm, compile_env);
            PiclVmProgram_append(program, PiclOpCode_assign_this_field, operand1, 0, node->binary_node.left->ident_node.name_index);
            break;

        case NodeType_Op_Assign_Member:
            operand1 = Picl_compile_node(node->binary_node.right, program, vm, compile_env);
            operand2 = Picl_compile_node(node->binary_node.left->naming_node.node, program, vm, compile_env);
            PiclVmProgram_append(program, PiclOpCode_assign_instance_field, operand1, operand2, node->binary_node.left->ident_node.name_index);
            break;

        case NodeType_Stmt_Return_Var:
            Picl_compile_unary_node(node, PiclOpCode_return_var, program, vm, compile_env);
            break;

        case NodeType_Stmt_Echo_Var:
            Picl_compile_unary_node(node, PiclOpCode_echo_var, program, vm, compile_env);
            break;

        case NodeType_Val_List_Var:
            break;

        case NodeType_Val_Dict_Var:
            break;

        case NodeType_Op_Minus:
            break;

        case NodeType_Op_FuncLazy:
            break;

        case NodeType_Val_IdentGlobal:
            operand1 = PiclCompileEnv_use_operand(compile_env);
            PiclVmProgram_append(program, PiclOpCode_ref_global, node->ident_node.name_index, 0, operand1);
            break;
        case NodeType_Val_IdentCurrentField:
            operand1 = PiclCompileEnv_use_operand(compile_env);
            PiclVmProgram_append(program, PiclOpCode_ref_this_field, node->ident_node.name_index, 0, operand1);
            break;
        case NodeType_Val_IdentCurrentMethod:
            operand1 = PiclCompileEnv_use_operand(compile_env);
            PiclVmProgram_append(program, PiclOpCode_ref_this_method, node->ident_node.name_index, 0, operand1);
            break;
        case NodeType_Val_IdentArg:
            operand1 = Picl_compile_ident_node(node, PiclOpCode_ref_arg, program, vm, compile_env);
            break;
        case NodeType_Val_Ident:
            operand1 = Picl_compile_ident_node(node, PiclOpCode_ref_variable, program, vm, compile_env);
            break;

        case NodeType_Decl_ArgIdent:
            break;

        case NodeType_Op_Dot:
            break;

        case NodeType_Val_Var_Dict:
            break;

        case NodeType_Val_Str_Dict:
            break;

        case NodeType_Str:
            operand1 = PiclCompileEnv_use_operand(compile_env);
            code1 = PiclVmProgram_append(program, PiclOpCode_str, (uintptr_t)node->str_node.cache, 0, operand1);
            break;

        case NodeType_Int:
            operand1 = PiclCompileEnv_use_operand(compile_env);
            code1 = PiclVmProgram_append(program, PiclOpCode_int, (uintptr_t)node->int_node.cache, 0, operand1);
            break;

        default:
            printf("Exception : compile node type %d\n", node->node_type);
            exit(1);
    }
    return operand1;
}


void Picl_compile_nodes(struct PiclNodeArray *nodes, struct PiclVmProgram *program, struct PiclVm *vm, struct PiclCompileEnv *compile_env)
{
    if(nodes == NULL) return;

    int operand1 = 0;

    for(int i = 0; i < nodes->size; i++){
        operand1 = PiclCompileEnv_current_operand(compile_env);
        Picl_compile_node(nodes->value[i], program, vm, compile_env);
        PiclCompileEnv_release_operand(compile_env, PiclCompileEnv_current_operand(compile_env) - operand1);
    }
}

void Picl_compile_program(struct PiclNodeArray *nodes)
{
    struct PiclOptimizeEnv *optimize_env = PiclOptimizeEnv_new();
    Picl_optimize_nodes(nodes, optimize_env);

    struct PiclVm *vm = PiclVm_new(
        optimize_env->decl_names->size,
        optimize_env->class_names->size,
        optimize_env->field_names->size,
        optimize_env->method_names->size,
        optimize_env->method_size);

    struct PiclCompileEnv *compile_env = PiclCompileEnv_new(optimize_env);

    struct PiclVmProgram *program = PiclVmProgram_new();

    Picl_compile_nodes(nodes, program, vm, compile_env);

    printf("all_free_object_size %d\n", vm->object_heap.all_free_object_size);
    printf("all_pool_object_size %d\n", vm->object_heap.all_pool_object_size);

    int main_index = PiclOptimizeEnv_find_decl_name_index(optimize_env, PiclStr_newByConst("main"));
    struct PiclObject *func_obj = PiclVm_get_decl(vm, main_index);

    fprintf(stdout, "program start %d\n", func_obj->func_obj.start_index);

    PiclVmProgram_dump(program);

    PiclVm_start(vm, func_obj, program);

    printf("all_free_object_size %d\n", vm->object_heap.all_free_object_size);
    printf("all_pool_object_size %d\n", vm->object_heap.all_pool_object_size);

}








