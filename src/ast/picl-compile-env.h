#ifndef PICL_COMPILE_ENV_H
# define PICL_COMPILE_ENV_H
# include "picl-node.h"
# include "picl-object.h"


struct PiclFrameOperands
{
    int current_operand;
    int max_operand;
    struct PiclFrameOperands *prev;
    struct PiclFrameOperands *next;
};

struct PiclCompileEnv
{
    struct PiclFrameOperands *frame_operands;
};


struct PiclCompileEnv *PiclCompileEnv_new();
void PiclCompileEnv_delete(struct PiclCompileEnv *optimize_env);

int PiclCompileEnv_current_operand(struct PiclCompileEnv *compile_env);
int PiclCompileEnv_use_operand(struct PiclCompileEnv *optimize_env);
void PiclCompileEnv_release_operand(struct PiclCompileEnv *optimize_env, int size);


void PiclCompileEnv_push(struct PiclCompileEnv *optimize_env, int args_size, int local_variables_size);
int PiclCompileEnv_pop(struct PiclCompileEnv *compile_env);

#endif /* PICL_COMPILE_ENV_H */
