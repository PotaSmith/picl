#include "picl-compile-env.h"
#include "picl-vm.h"

struct PiclCompileEnv *PiclCompileEnv_new()
{
    struct PiclCompileEnv *compile_env = malloc(sizeof(struct PiclCompileEnv));
    debug_print("call malloc PiclCompileEnv\n");

    compile_env->frame_operands = malloc(sizeof(struct PiclFrameOperands));
    compile_env->frame_operands->next = NULL;
    compile_env->frame_operands->prev = NULL;

    return compile_env;
}
void PiclCompileEnv_delete(struct PiclCompileEnv *compile_env)
{
    free(compile_env);
}

int PiclCompileEnv_current_operand(struct PiclCompileEnv *compile_env)
{
    return compile_env->frame_operands->current_operand;
}
void PiclCompileEnv_release_operand(struct PiclCompileEnv *compile_env, int size)
{
    compile_env->frame_operands->current_operand -= size;
}
int PiclCompileEnv_use_operand(struct PiclCompileEnv *compile_env)
{
    ++compile_env->frame_operands->max_operand;
    return ++compile_env->frame_operands->current_operand + VM_STACK_FRAME_RESERVED_SIZE;
}

void PiclCompileEnv_push(struct PiclCompileEnv *compile_env, int args_size, int local_variables_size)
{
    struct PiclFrameOperands *next = malloc(sizeof(struct PiclFrameOperands));
    next->current_operand = args_size + local_variables_size;
    next->max_operand = next->current_operand;

    compile_env->frame_operands->next = next;
    next->prev = compile_env->frame_operands;

    compile_env->frame_operands = next;
}

int PiclCompileEnv_pop(struct PiclCompileEnv *compile_env)
{
    int all_operand_size = compile_env->frame_operands->max_operand;

    struct PiclFrameOperands *prev = compile_env->frame_operands->prev;
    free(compile_env->frame_operands);
    compile_env->frame_operands = prev;

    return all_operand_size;
}
