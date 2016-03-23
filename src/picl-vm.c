#include "picl-vm.h"

struct PiclVmProgram *PiclVmProgram_new()
{
    struct PiclVmProgram *program = malloc(sizeof(struct PiclVmProgram));
    program->current = malloc(sizeof(struct PiclVmCodes));
    program->current->prev = NULL;
    program->current->next = NULL;

    return program;
}

struct PiclVmCode *PiclVmProgram_append(struct PiclVmProgram *program, PiclOpCode opcode, uintptr_t src1, int src2, int dst1)
{
    program->current->data[program->current->size].opcode = opcode;
    program->current->data[program->current->size].src1 = src1;
    program->current->data[program->current->size].src2 = src2;
    program->current->data[program->current->size].dst1 = dst1;

    return &program->current->data[program->current->size++];
}

int PiclVmProgram_get_next_index(struct PiclVmProgram *program)
{
    return program->current->size;
}

#define dump_vm_code(code) fprintf(stdout, "%d %s %lu %d %d\n", index, code, vm_code->src1, vm_code->src2, vm_code->dst1); break

void PiclVmCode_dump(int index, struct PiclVmCode *vm_code)
{
    switch (vm_code->opcode) {
        case PiclOpCode_nop: dump_vm_code("PiclOpCode_nop");
        case PiclOpCode_jump: dump_vm_code("PiclOpCode_jump");

        case PiclOpCode_set_arg: dump_vm_code("PiclOpCode_set_arg");
        case PiclOpCode_call_func: dump_vm_code("PiclOpCode_call_func");
        case PiclOpCode_call_method: dump_vm_code("PiclOpCode_call_method");
        case PiclOpCode_call_method_new: dump_vm_code("PiclOpCode_call_method_new");
        case PiclOpCode_end_frame: dump_vm_code("PiclOpCode_end_frame");
        case PiclOpCode_get_return: dump_vm_code("PiclOpCode_get_return");
        case PiclOpCode_get_new_instance: dump_vm_code("PiclOpCode_get_new_instance");

        case PiclOpCode_add: dump_vm_code("PiclOpCode_add");
        case PiclOpCode_sub: dump_vm_code("PiclOpCode_sub");
        case PiclOpCode_mul: dump_vm_code("PiclOpCode_mul");
        case PiclOpCode_div: dump_vm_code("PiclOpCode_div");
        case PiclOpCode_mod: dump_vm_code("PiclOpCode_mod");
        case PiclOpCode_str_join: dump_vm_code("PiclOpCode_str_join");

        case PiclOpCode_gt_equal: dump_vm_code("PiclOpCode_gt_equal");
        case PiclOpCode_lt_equal: dump_vm_code("PiclOpCode_lt_equal");
        case PiclOpCode_gt: dump_vm_code("PiclOpCode_gt");
        case PiclOpCode_lt: dump_vm_code("PiclOpCode_lt");

        case PiclOpCode_if_else: dump_vm_code("PiclOpCode_if_else");
        case PiclOpCode_if: dump_vm_code("PiclOpCode_if");

        case PiclOpCode_assign_variable: dump_vm_code("PiclOpCode_assign_variable");
        case PiclOpCode_assign_argument: dump_vm_code("PiclOpCode_assign_argument");
        case PiclOpCode_assign_this_field: dump_vm_code("PiclOpCode_assign_this_field");
        case PiclOpCode_assign_instance_field: dump_vm_code("PiclOpCode_assign_instance_field");

        case PiclOpCode_return_var: dump_vm_code("PiclOpCode_return_var");
        case PiclOpCode_echo_var: dump_vm_code("PiclOpCode_echo_var");

        case PiclOpCode_ref_global: dump_vm_code("PiclOpCode_ref_global");
        case PiclOpCode_ref_this_field: dump_vm_code("PiclOpCode_ref_this_field");
        case PiclOpCode_ref_this_method: dump_vm_code("PiclOpCode_ref_this_method");
        case PiclOpCode_ref_arg: dump_vm_code("PiclOpCode_ref_arg");
        case PiclOpCode_ref_variable: dump_vm_code("PiclOpCode_ref_variable");

        case PiclOpCode_int: dump_vm_code("PiclOpCode_int");
        case PiclOpCode_str: dump_vm_code("PiclOpCode_str");
    }
}
void PiclVmCodes_dump(struct PiclVmCodes *vm_codes)
{
    for(int i = 0; i < vm_codes->size; i++){
        PiclVmCode_dump(i, &vm_codes->data[i]);
    }
    if(vm_codes->next != NULL){
        PiclVmCodes_dump(vm_codes->next);
    }
}
void PiclVmProgram_dump(struct PiclVmProgram *program)
{
    PiclVmCodes_dump(program->current);
}


struct PiclVm *PiclVm_new(
    int decl_names_size,
    int class_names_size,
    int field_names_size,
    int method_names_size,
    int all_methods_size)
{
    trueObject = PiclObject_new_bool(true);
    falseObject = PiclObject_new_bool(false);

    struct PiclVm *vm = malloc(sizeof(struct PiclVm));
    debug_print("call malloc PiclRuntime\n");

    vm->echo_stream = stdout;

    PiclObjectHeap_init(&vm->object_heap);

    vm->decl_objs_size = decl_names_size;
    vm->decl_objs = malloc(sizeof(struct PiclObject*) * decl_names_size);
    debug_print("call malloc PiclObject*\n");


    vm->class_size = class_names_size;
    vm->field_size = field_names_size;
    vm->method_size = method_names_size;


    vm->method_objs_size = all_methods_size;
    vm->method_objs = malloc(sizeof(struct PiclObject*) * vm->method_objs_size);
    debug_print("call malloc PiclObject*\n");

    vm->class_field_table = malloc(sizeof(int*) * vm->class_size);
    vm->class_field_addresses = calloc(vm->class_size * vm->field_size, sizeof(int));
    for (int i=0; i < vm->class_size; i++) {
        vm->class_field_table[i] = vm->class_field_addresses + i * vm->field_size;
    }
    vm->class_method_table = malloc(sizeof(struct PiclObject**) * vm->class_size);
    vm->class_method_addresses = calloc(vm->class_size * vm->method_size, sizeof(struct PiclObject*));
    for (int i=0; i < vm->class_size; i++) {
        vm->class_method_table[i] = vm->class_method_addresses + i * vm->method_size;
    }

    return vm;
}

void PiclVm_set_decl(struct PiclVm *vm, int index, struct PiclObject *value)
{
    debug_print("PiclVm_set_decl: index %d", index);
    debug_obj(value);

    ++value->ref_count;
    vm->decl_objs[index] = value;
}

struct PiclObject *PiclVm_get_decl(struct PiclVm *vm, int index)
{
    if(index == -1){ return NULL; }

    debug_print("PiclVm_get_decl: index %d", index);
    debug_obj(vm->decl_objs[index]);

    return vm->decl_objs[index];
}

void PiclVm_set_field(struct PiclVm *vm, int class_index, int field_index, int member_offset)
{
    debug_print("PiclVm_set_field: class_index %d, field_index %d, member_offset %d\n", class_index, field_index, member_offset);
    vm->class_field_table[class_index][field_index] = member_offset;
}

void PiclVm_set_method(struct PiclVm *vm, int class_index, int method_index, struct PiclObject *value)
{
    debug_print("PiclVm_set_method: name %s, class_index %d, method_index %d", value->method_obj.name->value, class_index, method_index);
    debug_obj(value);

    ++value->ref_count;
    vm->method_objs[method_index] = value;
    vm->class_method_table[class_index][method_index] = value;
}

struct PiclObject *PiclVm_get_method(struct PiclVm *vm, int class_index, int method_index)
{
    debug_print("PiclVm_get_method: class_index %d, method_index %d", class_index, method_index);
    debug_obj(vm->class_method_table[class_index][method_index]);
    return vm->class_method_table[class_index][method_index];
}



/*
 * vm proc program
 */



void PiclVm_object_to_stream(struct PiclObject *picl_obj, FILE *stream)
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

void PiclVm_object_to_str(struct PiclObject *picl_obj, struct PiclStrBuf *strbuf)
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

PiclInt PiclVm_object_to_int(struct PiclVm *vm, struct PiclObject *picl_obj)
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
struct PiclObject *PiclVm_str_object_join(struct PiclObject *left, struct PiclObject *right, struct PiclVm *vm)
{
    switch (left->type) {
        case ObjectType_int:{
            struct PiclStrBuf *strbuf = PiclStrBuf_new();
            PiclStrBuf_init(strbuf);


            PiclVm_object_to_str(left, strbuf);
            PiclVm_object_to_str(right, strbuf);

            struct PiclStr *new_str;
            PiclStrBuf_toStr(strbuf, &new_str);

            return PiclObject_new_str(&vm->object_heap, new_str);
        }
        case ObjectType_bool:{
            struct PiclStrBuf *strbuf = PiclStrBuf_new();
            PiclStrBuf_init(strbuf);

            PiclVm_object_to_str(left, strbuf);
            PiclVm_object_to_str(right, strbuf);

            struct PiclStr *new_str;
            PiclStrBuf_toStr(strbuf, &new_str);

            return PiclObject_new_str(&vm->object_heap, new_str);
        }
        case ObjectType_str:{
            struct PiclStrBuf *strbuf = PiclStrBuf_new();
            PiclStrBuf_init(strbuf);

            PiclVm_object_to_str(left, strbuf);
            PiclVm_object_to_str(right, strbuf);

            struct PiclStr *new_str;
            PiclStrBuf_toStr(strbuf, &new_str);

            return PiclObject_new_str(&vm->object_heap, new_str);
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


void PiclVm_push_stack(struct PiclVm *vm, struct PiclObject *object)
{
    if(vm->object_heap.frame_created_object_stack_size >= OBJECT_HEAP_OBJECT_STACK_SIZE){
        fprintf(stderr, "Exception : frame_created_object_stack over \n");
        exit(1);
    }
    vm->object_heap.frame_created_object_stack[vm->object_heap.frame_created_object_stack_size++] = object;
    if(object != NULL){
        ++object->ref_count;
        debug_print("PiclVm_push_stack");
        debug_obj(object);
    }
}

/*
 * frame 
 * | prev | size | start code | function or method object | this object | return object | objects |
 */
# define vm_code_src1           (int)vm_code->src1

# define src1_frame_value       frame[vm_code_src1]
# define src2_frame_value       frame[vm_code->src2]
# define dst1_frame_value       frame[vm_code->dst1]

# define current_prev_frame     frame[0]
# define current_frame_size     frame[1]
# define current_arg_var_size   frame[2]
# define current_start_code     frame[3]
# define current_func_obj       frame[4]
# define current_this_obj       frame[5]
# define current_return_obj     frame[6]
# define current_frame_created_object_stack_index  frame[7]

# define cast_current_prev_frame    (struct PiclObject **)frame[0]
# define cast_current_frame_size    (int)(uintptr_t)frame[1]
# define cast_current_arg_var_size  (int)(uintptr_t)frame[2]
# define cast_current_start_code    (struct PiclVmCode *)frame[3]
# define cast_current_frame_created_object_stack_index (int)(uintptr_t)frame[7]

# define next_frame_prev_frame    frame[cast_current_frame_size + 1]
# define next_frame_frame_size    frame[cast_current_frame_size + 2]
# define next_frame_arg_var_size  frame[cast_current_frame_size + 3]
# define next_frame_start_code    frame[cast_current_frame_size + 4]
# define next_frame_func_obj      frame[cast_current_frame_size + 5]
# define next_frame_this_obj      frame[cast_current_frame_size + 6]
# define next_frame_return_obj    frame[cast_current_frame_size + 7]
# define next_frame_created_object_stack_index frame[cast_current_frame_size + 8]


void PiclVm_start(struct PiclVm *vm, struct PiclObject *func_obj, struct PiclVmProgram *program)
{
    struct PiclVmCodes *current = program->current;
    struct PiclVmCode *vm_code = &current->data[func_obj->func_obj.start_index];
    struct PiclObject **frame = vm->frame_stack;
    struct PiclObject *object1 = NULL;
    struct PiclObject *object2 = NULL;

    debug_print("current_frame_size %d\n", func_obj->func_obj.all_operand_size + VM_STACK_FRAME_RESERVED_SIZE);

    current_prev_frame = NULL;
    current_frame_size = (struct PiclObject *)(uintptr_t)(func_obj->func_obj.all_operand_size + VM_STACK_FRAME_RESERVED_SIZE);
    current_arg_var_size = (struct PiclObject *)(uintptr_t)(func_obj->func_obj.args_size + func_obj->func_obj.variables_size);
    current_start_code = NULL;
    current_func_obj = func_obj;
    current_this_obj = NULL;
    current_return_obj = NULL;
    current_frame_created_object_stack_index = (struct PiclObject *)(uintptr_t)vm->object_heap.frame_created_object_stack_size;

    for(;;){
        switch (vm_code->opcode) {
            case PiclOpCode_nop: break;

            case PiclOpCode_jump:
                vm_code += vm_code_src1;
                break;
            /*
             * function end
             */

            case PiclOpCode_return_var: // 下とつながってるので注意
                debug_print("PiclOpCode_return_var");
                if(src1_frame_value != NULL) {
                    ++src1_frame_value->ref_count;
                }
                current_return_obj = src1_frame_value;
                debug_obj(src1_frame_value);
            case PiclOpCode_end_frame: // 上とつながってるので注意
                debug_print("PiclOpCode_end_frame\n");

                for (int i = VM_STACK_FRAME_RESERVED_SIZE; i < VM_STACK_FRAME_RESERVED_SIZE + cast_current_arg_var_size; ++i)
                {
                    if(frame[i] != NULL){
                        --frame[i]->ref_count;
                        debug_print("decl frame");
                        debug_obj(frame[i]);
                    }

                    PiclObjectHeap_release(&vm->object_heap, frame[i]);
                    frame[i] = NULL;
                }
                debug_print("object_heap frame_created_object_stack_size %d\n", vm->object_heap.frame_created_object_stack_size);
                debug_print("cast_current_frame_created_object_stack_index %d\n", cast_current_frame_created_object_stack_index);
                for (int i = vm->object_heap.frame_created_object_stack_size -1; i >= cast_current_frame_created_object_stack_index; --i)
                {
                    debug_print("i %d\n", i);
                    debug_print("cast_current_frame_created_object_stack_index %d\n", cast_current_frame_created_object_stack_index);

                    if(vm->object_heap.frame_created_object_stack[i] != NULL){
                        debug_print("decl created object %d", i);
                        --vm->object_heap.frame_created_object_stack[i]->ref_count;
                        debug_obj(vm->object_heap.frame_created_object_stack[i]);
                    }
                    PiclObjectHeap_release(&vm->object_heap, vm->object_heap.frame_created_object_stack[i]);
                }

                debug_print("frame_created_object_stack_size down %d to %d\n", vm->object_heap.frame_created_object_stack_size, cast_current_frame_created_object_stack_index);
                vm->object_heap.frame_created_object_stack_size = cast_current_frame_created_object_stack_index;

                if(current_prev_frame == NULL) return;
                frame = cast_current_prev_frame;
                vm_code = cast_current_start_code;

                break;

            /*
             * call
             */

            case PiclOpCode_set_arg:
                ++src1_frame_value->ref_count;
                frame[cast_current_frame_size + 1 + VM_STACK_FRAME_RESERVED_SIZE + vm_code->dst1] = src1_frame_value;
                debug_print("PiclOpCode_set_arg %d", VM_STACK_FRAME_RESERVED_SIZE + vm_code->dst1);
                debug_obj(src1_frame_value);
                break;

            case PiclOpCode_call_func:
                debug_print("PiclOpCode_call_func\n");
                current_start_code = (struct PiclObject *)vm_code;

                next_frame_prev_frame = (struct PiclObject *)frame;
                next_frame_frame_size = (struct PiclObject *)(uintptr_t)(src1_frame_value->func_obj.all_operand_size + VM_STACK_FRAME_RESERVED_SIZE);
                next_frame_arg_var_size = (struct PiclObject *)(uintptr_t)(src1_frame_value->func_obj.args_size + src1_frame_value->func_obj.variables_size);
                next_frame_func_obj = src1_frame_value;
                next_frame_this_obj = NULL;
                next_frame_return_obj = NULL;
                next_frame_created_object_stack_index = (struct PiclObject *)(uintptr_t)vm->object_heap.frame_created_object_stack_size;

                debug_print("frame_created_object_stack_index set %d\n", vm->object_heap.frame_created_object_stack_size);

                vm_code = &current->data[src1_frame_value->func_obj.start_index - 1];
                frame += cast_current_frame_size + 1;
                break;

            case PiclOpCode_call_method:
                debug_print("PiclOpCode_call_method\n");

                if (src1_frame_value->type != ObjectType_instance) {
                    printf("Exception : call not instance method\n");
                    debug_obj(src1_frame_value);
                    exit(1);
                }
                object1 = PiclVm_get_method(vm, src1_frame_value->instance.class_obj->class_obj.class_name_index, vm_code->src2);

                if(object1 == NULL){
                    printf("Exception : method not found\n");
                }

                debug_print("PiclOpCode_call_method this obj %d", vm_code_src1);
                debug_obj(src1_frame_value);
                debug_print("PiclOpCode_call_method method obj");
                debug_obj(object1);

                current_start_code = (struct PiclObject *)vm_code;

                next_frame_prev_frame = (struct PiclObject *)frame;
                next_frame_frame_size = (struct PiclObject *)(uintptr_t)(object1->method_obj.all_operand_size + VM_STACK_FRAME_RESERVED_SIZE);
                next_frame_arg_var_size = (struct PiclObject *)(uintptr_t)(object1->method_obj.args_size + object1->method_obj.variables_size);
                next_frame_func_obj = object1;
                next_frame_this_obj = src1_frame_value;
                next_frame_return_obj = NULL;
                next_frame_created_object_stack_index = (struct PiclObject *)(uintptr_t)vm->object_heap.frame_created_object_stack_size;

                debug_print("frame_created_object_stack_index set %d\n", vm->object_heap.frame_created_object_stack_size);

                vm_code = &current->data[object1->method_obj.start_index - 1];
                frame += cast_current_frame_size + 1;
                break;

            case PiclOpCode_call_method_new:
                debug_print("PiclOpCode_call_method\n");

                if (src1_frame_value->type != ObjectType_class) {
                    printf("Exception : call not class method\n");
                    debug_obj(src1_frame_value);
                    exit(1);
                }
                object1 = PiclVm_get_method(vm, src1_frame_value->class_obj.class_name_index, vm_code->src2);

                if(object1 == NULL){
                    printf("Exception : method not found\n");
                }

                object2 = PiclObject_new_instance(&vm->object_heap, src1_frame_value);
                PiclVm_push_stack(vm, object2);

                debug_print("PiclOpCode_call_method this obj");
                debug_obj(object2);
                debug_print("PiclOpCode_call_method method obj");
                debug_obj(object1);

                current_start_code = (struct PiclObject *)vm_code;

                next_frame_prev_frame = (struct PiclObject *)frame;
                next_frame_frame_size = (struct PiclObject *)(uintptr_t)(object1->method_obj.all_operand_size + VM_STACK_FRAME_RESERVED_SIZE);
                next_frame_arg_var_size = (struct PiclObject *)(uintptr_t)(object1->method_obj.args_size + object1->method_obj.variables_size);
                next_frame_func_obj = object1;
                next_frame_this_obj = object2;
                next_frame_return_obj = NULL;
                next_frame_created_object_stack_index = (struct PiclObject *)(uintptr_t)vm->object_heap.frame_created_object_stack_size;

                debug_print("frame_created_object_stack_index set %d\n", vm->object_heap.frame_created_object_stack_size);

                vm_code = &current->data[object1->method_obj.start_index - 1];
                frame += cast_current_frame_size + 1;
                break;


            case PiclOpCode_get_return:
                dst1_frame_value = next_frame_return_obj;
                if(dst1_frame_value != NULL) {
                    --dst1_frame_value->ref_count;
                }
                debug_print("PiclOpCode_get_return");
                debug_obj(dst1_frame_value);

                PiclVm_push_stack(vm, dst1_frame_value);
                break;

            case PiclOpCode_get_new_instance:
                dst1_frame_value = next_frame_this_obj;
                debug_print("PiclOpCode_get_new_instance");
                debug_obj(dst1_frame_value);
                break;

            /*
             * bin op
             */

            case PiclOpCode_add:
                debug_print("PiclOpCode_add\n");
                dst1_frame_value = PiclObject_new_int(&vm->object_heap,
                    PiclVm_object_to_int(vm, src1_frame_value) + PiclVm_object_to_int(vm, src2_frame_value));

                PiclVm_push_stack(vm, dst1_frame_value);
                break;
            case PiclOpCode_sub:
                debug_print("PiclOpCode_sub\n");
                dst1_frame_value = PiclObject_new_int(&vm->object_heap,
                    PiclVm_object_to_int(vm, src1_frame_value) - PiclVm_object_to_int(vm, src2_frame_value));

                PiclVm_push_stack(vm, dst1_frame_value);
                break;

            case PiclOpCode_mul:
                break;

            case PiclOpCode_div:
                break;

            case PiclOpCode_mod:
                break;

            case PiclOpCode_str_join:
                dst1_frame_value = PiclVm_str_object_join(src1_frame_value, src2_frame_value, vm);
                PiclVm_push_stack(vm, dst1_frame_value);
                break;

            /*
             * comp op
             */

            case PiclOpCode_gt_equal:
                break;

            case PiclOpCode_lt_equal:
                break;

            case PiclOpCode_gt:
                if(PiclVm_object_to_int(vm, src1_frame_value) > PiclVm_object_to_int(vm, src2_frame_value)){
                    dst1_frame_value = trueObject;
                }
                else{
                    dst1_frame_value = falseObject;
                }
                break;

            case PiclOpCode_lt:
                if(PiclVm_object_to_int(vm, src1_frame_value) < PiclVm_object_to_int(vm, src2_frame_value)){
                    dst1_frame_value = trueObject;
                }
                else{
                    dst1_frame_value = falseObject;
                }
                break;


            /*
             * assgin stmt
             */

            case PiclOpCode_assign_variable:
                dst1_frame_value = src1_frame_value;
                debug_print("PiclOpCode_assign_variable value");
                debug_obj(src1_frame_value);
                break;

            case PiclOpCode_assign_argument:
                dst1_frame_value = src1_frame_value;
                debug_print("PiclOpCode_assign_variable value");
                debug_obj(src1_frame_value);
                break;

            case PiclOpCode_assign_this_field:
                ++src1_frame_value->ref_count;
                current_this_obj->instance.fields[vm_code->dst1] = src1_frame_value;
                debug_print("PiclOpCode_assign_this_field current this");
                debug_obj(current_this_obj);
                debug_print("PiclOpCode_assign_this_field value");
                debug_obj(src1_frame_value);
                break;

            case PiclOpCode_assign_instance_field:
                ++src1_frame_value->ref_count;
                src2_frame_value->instance.fields[vm->class_field_table[src2_frame_value->instance.class_obj->class_obj.class_name_index][vm_code->dst1]] = src1_frame_value;
                debug_print("PiclOpCode_assign_instance_field instance");
                debug_obj(src2_frame_value);
                debug_print("PiclOpCode_assign_instance_field value");
                debug_obj(src1_frame_value);
                break;



            /*
             * cond stmt
             */

            case PiclOpCode_if_else:
                if(src1_frame_value == trueObject){
                    vm_code += vm_code->src2;
                }
                break;

            case PiclOpCode_if:
                if(src1_frame_value != trueObject){
                    vm_code += vm_code->src2;
                }
                break;

            /*
             * una stmt
             */

            case PiclOpCode_echo_var:
                PiclVm_object_to_stream(src1_frame_value, vm->echo_stream);
                break;

            /*
             * ref
             */

            case PiclOpCode_ref_global:
                dst1_frame_value = PiclVm_get_decl(vm, vm_code_src1);
                debug_print("PiclOpCode_ref_global");
                debug_obj(dst1_frame_value);
                break;

            case PiclOpCode_ref_this_field:
                dst1_frame_value = current_this_obj->instance.fields[vm_code_src1];
                debug_print("PiclOpCode_ref_this_field current this");
                debug_obj(current_this_obj);
                debug_print("PiclOpCode_ref_this_field field value");
                debug_obj(dst1_frame_value);
                break;

            case PiclOpCode_ref_this_method:
                dst1_frame_value = current_this_obj->instance.class_obj->class_obj.methods[vm_code_src1];
                debug_print("PiclOpCode_ref_this_method current this");
                debug_obj(current_this_obj);
                debug_print("PiclOpCode_ref_this_field method value");
                debug_obj(dst1_frame_value);
                break;

            case PiclOpCode_ref_arg:
                dst1_frame_value = src1_frame_value;
                debug_print("PiclOpCode_ref_arg");
                debug_obj(dst1_frame_value);
                break;

            case PiclOpCode_ref_variable:
                dst1_frame_value = src1_frame_value;
                debug_print("PiclOpCode_ref_variable");
                debug_obj(dst1_frame_value);
                break;

            /*
             * literal
             */

            case PiclOpCode_int:
                dst1_frame_value = (struct PiclObject *)vm_code->src1;
                break;

            case PiclOpCode_str:
                dst1_frame_value = (struct PiclObject *)vm_code->src1;
                break;
        }

        vm_code += 1;
    }
}
