#ifndef PICL_OBJECT_H
# define PICL_OBJECT_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <stdint.h>
# include <inttypes.h>
# include "picl-debug.h"

# define OBJECT_POOL_DATA_SIZE 1000
# define FREE_LIST_DATA_SIZE 1000
# define OBJECT_HEAP_OBJECT_STACK_SIZE 1000


/*
 * string
 */

struct PiclStr
{
    int length;
    char *value;
};

typedef int64_t PiclInt;

struct PiclStrBuf
{
    int index;
    int length;
    char *buf;
};

struct PiclStr *PiclStr_new();
struct PiclStr *PiclStr_newByInt(int value);
struct PiclStr *PiclStr_newByChars(char *value, int length);
struct PiclStr *PiclStr_newByConst(const char *value);
struct PiclStr *PiclStr_substr(struct PiclStr *value, int limit);
void PiclStr_delete(struct PiclStr *picl_str);

bool PiclStr_equals(struct PiclStr *value1, struct PiclStr *value2);
bool PiclStr_equalsConst(struct PiclStr *value1, const char *value2);

struct PiclStrBuf *PiclStrBuf_new();

void PiclStrBuf_init(struct PiclStrBuf *strbuf);
void PiclStrBuf_append(struct PiclStrBuf *strbuf, char c);
void PiclStrBuf_toStr(struct PiclStrBuf *strbuf, struct PiclStr **str_result);
void PiclStrBuf_toInt(struct PiclStrBuf *strbuf, struct PiclStr **str_result, PiclInt *int_result);
bool PiclStrBuf_isEmpty(struct PiclStrBuf *strbuf);


/*
 * object
 */


struct PiclObject;
struct PiclVmCodes;

struct PiclObject *trueObject;
struct PiclObject *falseObject;

struct PiclFunction
{
    struct PiclStr *name;
    int name_index;
    struct PiclNodeArray *args;
    struct PiclNodeArray *body;
    struct PiclNodeArray *lets;
    int args_size;
    int variables_size;
    int lets_size;

    int all_operand_size;
    int start_index;
};
struct PiclSequence
{
    struct PiclStr *name;
    int decl_name_index;
    struct PiclNodeArray *members;
    struct PiclNodeArray *options;
};
struct PiclClass
{
    struct PiclStr *name;
    int decl_name_index;
    int class_name_index;
    struct PiclObject **fields;
    int fields_size;
    struct PiclObject **methods;
    int methods_size;
};
struct PiclMethod
{
    struct PiclObject *class_obj;
    struct PiclStr *name;
    struct PiclNodeArray *args;
    struct PiclNodeArray *body;
    struct PiclNodeArray *lets;
    int args_size;
    int variables_size;
    int lets_size;

    int all_operand_size;
    int start_index;
};
struct PiclField
{
    struct PiclObject *class_obj;
    struct PiclStr *name;
    struct PiclNode *value;
};
struct PiclInstance
{
    struct PiclObject *class_obj;
    struct PiclObject **fields;
    int fields_size;
};

struct PiclBehavior
{
    struct PiclStr *name;
    int decl_name_index;
    int class_name_index;
    struct PiclNodeArray *members;
    struct PiclNodeArray *options;
};

typedef enum _ObjectType {
    ObjectType_int,
    ObjectType_bool,
    ObjectType_str,
    ObjectType_func,
    ObjectType_class,
    ObjectType_field,
    ObjectType_method,
    ObjectType_instance,
} ObjectType;

struct PiclObject
{
    int id;
    ObjectType type;
    int ref_count;
    union {
        struct 
        {
            PiclInt value;
        }
        int_obj;
        struct 
        {
            bool value;
        }
        bool_obj;
        struct 
        {
            struct PiclStr *value;
        }
        str_obj;
        struct PiclFunction func_obj;
        struct PiclClass class_obj;
        struct PiclField field_obj;
        struct PiclMethod method_obj;
        struct PiclInstance instance;
    };
};

/*
 * object pool
 */

struct PiclObjectPool
{
    struct PiclObject data[OBJECT_POOL_DATA_SIZE];
    int size;
    struct PiclObjectPool *prev;
};

/*
 * free list
 */

struct PiclFreeList
{
    struct PiclObject *data[FREE_LIST_DATA_SIZE];
    int size;
    struct PiclFreeList *prev;
};

struct PiclObjectHeap
{
    int index;
    struct PiclObjectPool *object_pool;
    struct PiclFreeList *free_list;

    int all_pool_object_size;
    int all_free_object_size;

    struct PiclObject *frame_created_object_stack[OBJECT_HEAP_OBJECT_STACK_SIZE];
    int frame_created_object_stack_size;
};


struct PiclObject *PiclObject_new_int(struct PiclObjectHeap *object_heap, PiclInt ival);
struct PiclObject *PiclObject_new_literal_int(PiclInt ival);
struct PiclObject *PiclObject_new_bool(bool bval);
struct PiclObject *PiclObject_new_str(struct PiclObjectHeap *object_heap, struct PiclStr *sval);
struct PiclObject *PiclObject_new_literal_str(struct PiclStr *sval);
struct PiclObject *PiclObject_new_function(struct PiclObjectHeap *object_heap,
    struct PiclStr *name,
    int name_index,
    struct PiclNodeArray *args,
    struct PiclNodeArray *body,
    int args_size,
    int variables_size,
    int all_operand_size,
    int start_index
);
struct PiclObject *PiclObject_new_class(struct PiclObjectHeap *object_heap,
    struct PiclStr *name,
    int decl_name_index,
    int class_name_index,
    int fields_size,
    int methods_size
);
struct PiclObject *PiclObject_new_field(struct PiclObjectHeap *object_heap,
    struct PiclObject *class_obj,
    struct PiclStr *name,
    struct PiclNode *value
);
struct PiclObject *PiclObject_new_method(struct PiclObjectHeap *object_heap,
    struct PiclObject *class_obj,
    struct PiclStr *name,
    struct PiclNodeArray *args,
    struct PiclNodeArray *body,
    int args_size,
    int variables_size,
    int all_operand_size,
    int start_index
);

struct PiclObject *PiclObject_new_instance(struct PiclObjectHeap *object_heap, struct PiclObject *class_obj);


void PiclObjectHeap_init(struct PiclObjectHeap *object_heap);
struct PiclObject *PiclObjectHeap_alloc(struct PiclObjectHeap *object_heap);
void PiclObjectHeap_release(struct PiclObjectHeap *object_heap, struct PiclObject *object);

void PiclObject_dump(struct PiclObject *class_obj);



#endif // ! PICL_OBJECT_H