#ifndef PICL_VM_H
# define PICL_VM_H
# include "picl-object.h"

# define VM_CODES_DATA_SIZE 100000
# define VM_STACK_FRAME_SIZE 100000

# define VM_STACK_FRAME_RESERVED_SIZE 8

typedef enum _PiclOpCode {
    PiclOpCode_nop, // 0
    PiclOpCode_jump, // 1

    PiclOpCode_get_return,          // 1
    PiclOpCode_get_new_instance,    // 2

    PiclOpCode_set_arg,             // 3
    PiclOpCode_call_func,           // 4
    PiclOpCode_call_method,         // 5
    PiclOpCode_call_method_new,     // 6
    PiclOpCode_return_var,          // 7
    PiclOpCode_end_frame,           // 8

    PiclOpCode_add,                 // 9
    PiclOpCode_sub,                 // 10
    PiclOpCode_mul,                 // 11
    PiclOpCode_div,                 // 2
    PiclOpCode_mod,                 // 3
    PiclOpCode_str_join,            // 4

    PiclOpCode_gt_equal,            // 5
    PiclOpCode_lt_equal,            // 6
    PiclOpCode_gt,                  // 7
    PiclOpCode_lt,                  // 8

    PiclOpCode_if_else,             // 9
    PiclOpCode_if,                  // 0

    PiclOpCode_assign_variable,         // 2
    PiclOpCode_assign_argument,         // 3
    PiclOpCode_assign_this_field,       // 4
    PiclOpCode_assign_instance_field,   // 5

    PiclOpCode_echo_var,            // 6

    PiclOpCode_ref_global,          // 7
    PiclOpCode_ref_this_field,      // 8
    PiclOpCode_ref_this_method,     // 9
    PiclOpCode_ref_arg,             // 30
    PiclOpCode_ref_variable,        // 1

    PiclOpCode_int,             // 2
    PiclOpCode_str,             // 3
} PiclOpCode;


struct PiclVmCode
{
    PiclOpCode opcode;
    uintptr_t src1; // allow literal value pointer
    int src2;
    int dst1;
};


struct PiclVmCodes
{
    struct PiclVmCode data[VM_CODES_DATA_SIZE];
    int size;
    struct PiclVmCodes *prev;
    struct PiclVmCodes *next;
};

struct PiclVmProgram
{
    struct PiclVmCodes *current;
};

struct PiclVmProgram *PiclVmProgram_new();
struct PiclVmCode *PiclVmProgram_append(struct PiclVmProgram *program, PiclOpCode opcode, uintptr_t src1, int src2, int dst1);
int PiclVmProgram_get_next_index(struct PiclVmProgram *program);

void PiclVmProgram_dump(struct PiclVmProgram *program);

struct PiclVm
{
    FILE *echo_stream;

    struct PiclObject **decl_objs;
    int decl_objs_size;

    int class_size;
    int field_size;
    int method_size;

    struct PiclObject **method_objs;
    int method_objs_size;

    int **class_field_table;
    int *class_field_addresses;
    struct PiclObject ***class_method_table;
    struct PiclObject **class_method_addresses;

    struct PiclObject *frame_stack[VM_STACK_FRAME_SIZE];

    struct PiclObjectHeap object_heap;
};

struct PiclVm *PiclVm_new(int decl_names_size, int class_names_size, int field_names_size, int method_names_size, int all_methods_size);

void PiclVm_set_decl(struct PiclVm *vm, int index, struct PiclObject *value);
struct PiclObject *PiclVm_get_decl(struct PiclVm *vm, int index);

struct PiclObject *PiclVm_get_this_field(struct PiclVm *vm, int index);

struct PiclObject *PiclVm_get_this_method(struct PiclVm *vm, int index);

void PiclVm_set_field(struct PiclVm *vm, int class_index, int field_index, int member_offset);

void PiclVm_set_method(struct PiclVm *vm, int class_index, int method_index, struct PiclObject *value);
struct PiclObject *PiclVm_get_method(struct PiclVm *vm, int class_index, int method_index);


void PiclVm_start(struct PiclVm *vm, struct PiclObject *func_obj, struct PiclVmProgram *program);

#endif // ! PICL_VM_H

