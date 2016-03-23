#ifndef PICL_LEX_H
# define PICL_LEX_H
# include "picl-object.h"

# define HERE_DOC_CHAR_LIMIT 100000
# define PICL_TOKEN_STACK_DATA_SIZE 100

struct PiclToken
{
    int line;
    int column;
    int token_type;
    PiclInt ival;
    struct PiclStr *sval;
    struct PiclStr *name;
};

struct PiclTokenStack
{
    int index;
    struct PiclToken *data[PICL_TOKEN_STACK_DATA_SIZE];
};

struct PiclTokenStack *PiclTokenStack_new();
bool PiclTokenStack_push(struct PiclTokenStack *stack, struct PiclToken *picl_token);
bool PiclTokenStack_pop(struct PiclTokenStack *stack, struct PiclToken **result);
bool PiclTokenStack_is_empty(struct PiclTokenStack *stack);


#endif // ! PICL_LEX_H
