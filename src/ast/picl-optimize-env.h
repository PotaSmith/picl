#ifndef PICL_OPTIMIZE_ENV_H
# define PICL_OPTIMIZE_ENV_H
# include "picl-node.h"
# include "picl-object.h"

/*
 *   変数名 
 */

# define VARIABLE_NAMES_DATA_SIZE 100


struct PiclVariableNames
{
    struct PiclStr *data[VARIABLE_NAMES_DATA_SIZE];
    int size;
};

struct PiclFrameVariableNames
{
    struct PiclVariableNames *args;
    struct PiclVariableNames *locals;

    struct PiclFrameVariableNames *prev;
    struct PiclFrameVariableNames *next;
};

struct PiclOptimizeEnv
{
    struct PiclNode *this_node;
    struct PiclFrameVariableNames *frame_var_names;
    struct PiclVariableNames *decl_names;
    struct PiclVariableNames *class_names;
    struct PiclVariableNames *sequence_names;
    struct PiclVariableNames *field_names;
    struct PiclVariableNames *method_names;
    struct PiclVariableNames *catch_names;
    int method_size;
};

struct PiclOptimizeEnv *PiclOptimizeEnv_new();
void PiclOptimizeEnv_delete(struct PiclOptimizeEnv *optimize_env);

void PiclOptimizeEnv_push(struct PiclOptimizeEnv *optimize_env);
void PiclOptimizeEnv_pop(struct PiclOptimizeEnv *optimize_env, struct PiclNode *node, int *args_size, int *variables_size);

void PiclOptimizeEnv_set_object(struct PiclNode *node, struct PiclOptimizeEnv *optimize_env);
void PiclOptimizeEnv_unset_object(struct PiclOptimizeEnv *optimize_env);


void set_class_name_index(struct PiclNode *node, int class_name_index);
int PiclOptimizeEnv_set_decl_name_index(struct PiclOptimizeEnv *optimize_env, struct PiclNode *node, struct PiclStr *name, int *name_index);
int PiclOptimizeEnv_find_decl_name_index(struct PiclOptimizeEnv *optimize_env, struct PiclStr *name);
int PiclOptimizeEnv_set_class_name_index(struct PiclOptimizeEnv *optimize_env, struct PiclNode *node, struct PiclStr *name, int *name_index);
int PiclOptimizeEnv_set_sequence_name_index(struct PiclOptimizeEnv *optimize_env, struct PiclNode *node, struct PiclStr *name, int *name_index);
int PiclOptimizeEnv_set_field_name_index(struct PiclOptimizeEnv *optimize_env, struct PiclNode *node, struct PiclStr *name, int *name_index);
int PiclOptimizeEnv_set_method_name_index(struct PiclOptimizeEnv *optimize_env, struct PiclNode *node, struct PiclStr *name, int *name_index);
int PiclOptimizeEnv_set_catch_name_index(struct PiclOptimizeEnv *optimize_env, struct PiclNode *node, struct PiclStr *name, int *name_index);
int PiclOptimizeEnv_set_arg_index(struct PiclOptimizeEnv *optimize_env, struct PiclStr *name);
int PiclOptimizeEnv_find_name_index(struct PiclOptimizeEnv *optimize_env, struct PiclNode *node, struct PiclStr *name, int *name_index);

int PiclOptimizeEnv_find_field_name_index(struct PiclOptimizeEnv *optimize_env, struct PiclStr *name, int *name_index);
int PiclOptimizeEnv_find_method_name_index(struct PiclOptimizeEnv *optimize_env, struct PiclStr *name, int *name_index);
int PiclOptimizeEnv_find_catch_name_index(struct PiclOptimizeEnv *optimize_env, struct PiclStr *name, int *name_index);


#endif /* PICL_OPTIMIZE_ENV_H */
