#include "picl-object.h"

struct PiclObject *PiclObject_init(struct PiclObjectHeap *object_heap, struct PiclObject *picl_object)
{
    picl_object->type = 0;
    picl_object->ref_count = 0;

    return picl_object;
}
struct PiclObject *PiclObject_new_literal_int(PiclInt ival)
{
    struct PiclObject *picl_object = malloc(sizeof(struct PiclObject));

    picl_object->id = 0;
    picl_object->type = ObjectType_int;
    picl_object->ref_count = 1;
    picl_object->int_obj.value = ival;

    debug_print("new obj");
    debug_obj(picl_object);
    return picl_object;
}
struct PiclObject *PiclObject_new_int(struct PiclObjectHeap *object_heap, PiclInt ival)
{
    struct PiclObject *picl_object = PiclObjectHeap_alloc(object_heap);

    picl_object->id = object_heap->index++;
    picl_object->type = ObjectType_int;
    picl_object->int_obj.value = ival;

    debug_print("new obj");
    debug_obj(picl_object);
    return picl_object;
}
struct PiclObject *PiclObject_new_bool(bool bval)
{
    struct PiclObject *picl_object = malloc(sizeof(struct PiclObject));
    picl_object->id = 0;
    picl_object->type = ObjectType_bool;
    picl_object->ref_count = 1;
    picl_object->bool_obj.value = bval;
    return picl_object;
}
struct PiclObject *PiclObject_new_str(struct PiclObjectHeap *object_heap, struct PiclStr *sval)
{
    struct PiclObject *picl_object = PiclObjectHeap_alloc(object_heap);
    picl_object->id = object_heap->index++;
    picl_object->type = ObjectType_str;
    picl_object->str_obj.value = sval;
    return picl_object;
}
struct PiclObject *PiclObject_new_literal_str(struct PiclStr *sval)
{
    struct PiclObject *picl_object = malloc(sizeof(struct PiclObject));
    picl_object->id = 0;
    picl_object->type = ObjectType_str;
    picl_object->ref_count = 1;
    picl_object->str_obj.value = sval;
    return picl_object;
}
struct PiclObject *PiclObject_new_function(struct PiclObjectHeap *object_heap,
    struct PiclStr *name,
    int name_index,
    struct PiclNodeArray *args,
    struct PiclNodeArray *body,
    int args_size,
    int variables_size,
    int all_operand_size,
    int start_index
){
    struct PiclObject *picl_object = PiclObjectHeap_alloc(object_heap);
    picl_object->id = object_heap->index++;
    picl_object->type = ObjectType_func;
    picl_object->func_obj.name = name;
    picl_object->func_obj.name_index = name_index;
    picl_object->func_obj.args = args;
    picl_object->func_obj.body = body;
    picl_object->func_obj.args_size = args_size;
    picl_object->func_obj.variables_size = variables_size;
    picl_object->func_obj.all_operand_size = all_operand_size;
    picl_object->func_obj.start_index = start_index;
    return picl_object;
}
struct PiclObject *PiclObject_new_class(struct PiclObjectHeap *object_heap,
    struct PiclStr *name,
    int decl_name_index,
    int class_name_index,
    int fields_size,
    int methods_size
){
    struct PiclObject *picl_object = PiclObjectHeap_alloc(object_heap);
    picl_object->id = object_heap->index++;
    picl_object->type = ObjectType_class;
    picl_object->class_obj.name = name;
    picl_object->class_obj.decl_name_index = decl_name_index;
    picl_object->class_obj.class_name_index = class_name_index;
    picl_object->class_obj.fields = malloc(sizeof(struct PiclObject*) * fields_size);
    picl_object->class_obj.fields_size = fields_size;
    picl_object->class_obj.methods = malloc(sizeof(struct PiclObject*) * methods_size);
    picl_object->class_obj.methods_size = methods_size;

    return picl_object;
}

struct PiclObject *PiclObject_new_field(struct PiclObjectHeap *object_heap,
    struct PiclObject *class_obj,
    struct PiclStr *name,
    struct PiclNode *value
){
    struct PiclObject *picl_object = PiclObjectHeap_alloc(object_heap);
    picl_object->id = object_heap->index++;
    picl_object->type = ObjectType_field;
    picl_object->field_obj.class_obj = class_obj;
    picl_object->field_obj.name = name;
    picl_object->field_obj.value = value;
    return picl_object;
}

struct PiclObject *PiclObject_new_method(struct PiclObjectHeap *object_heap,
    struct PiclObject *class_obj,
    struct PiclStr *name,
    struct PiclNodeArray *args,
    struct PiclNodeArray *body,
    int args_size,
    int variables_size,
    int all_operand_size,
    int start_index
){
    struct PiclObject *picl_object = PiclObjectHeap_alloc(object_heap);
    picl_object->id = object_heap->index++;
    picl_object->type = ObjectType_method;
    picl_object->method_obj.name = name;
    picl_object->method_obj.args = args;
    picl_object->method_obj.body = body;
    picl_object->method_obj.args_size = args_size;
    picl_object->method_obj.variables_size = variables_size;
    picl_object->method_obj.all_operand_size = all_operand_size;
    picl_object->method_obj.start_index = start_index;
    return picl_object;
}

struct PiclObject *PiclObject_new_instance(struct PiclObjectHeap *object_heap, struct PiclObject *class_obj)
{
    struct PiclObject *picl_object = PiclObjectHeap_alloc(object_heap);
    picl_object->id = object_heap->index++;
    picl_object->type = ObjectType_instance;
    picl_object->field_obj.class_obj = class_obj;
    picl_object->instance.fields = malloc(sizeof(struct PiclObject*) * class_obj->class_obj.fields_size);
    picl_object->instance.fields_size = class_obj->class_obj.fields_size;

    return picl_object;
}

void PiclObject_dump(struct PiclObject *picl_obj)
{
    if(picl_obj == NULL){
        fprintf(stderr, " -- NULL\n");
        return;
    }

    switch (picl_obj->type) {
        case ObjectType_int:
            fprintf(stderr, " -- int(id: %d, value: %lld, ref_count %d)\n", picl_obj->id, picl_obj->int_obj.value, picl_obj->ref_count);
            break;
        case ObjectType_bool:
            fprintf(stderr, " -- bool(id: %d, value: %d, ref_count %d)\n", picl_obj->id, picl_obj->bool_obj.value, picl_obj->ref_count);
            break;
        case ObjectType_str:
            fprintf(stderr, " -- str(id: %d, value: %s, ref_count %d)\n", picl_obj->id, picl_obj->str_obj.value->value, picl_obj->ref_count);
            break;
        case ObjectType_func:
            fprintf(stderr, " -- func(id: %d, name: %s, ref_count %d)\n", picl_obj->id, picl_obj->func_obj.name->value, picl_obj->ref_count);
            break;
        case ObjectType_class:
            fprintf(stderr, " -- class(id: %d, name: %s, ref_count %d)\n", picl_obj->id, picl_obj->class_obj.name->value, picl_obj->ref_count);
            break;
        case ObjectType_field:
            fprintf(stderr, " -- field(id: %d, name: %s, ref_count %d)\n", picl_obj->id, picl_obj->field_obj.name->value, picl_obj->ref_count);
            break;
        case ObjectType_method:
            fprintf(stderr, " -- method(id: %d, name: %s, ref_count %d)\n", picl_obj->id, picl_obj->method_obj.name->value, picl_obj->ref_count);
            break;
        case ObjectType_instance:
            fprintf(stderr, " -- instance(id: %d, name: %s, ref_count %d)\n", picl_obj->id, picl_obj->instance.class_obj->class_obj.name->value, picl_obj->ref_count);
            break;
    }
}

void PiclObject_delete(struct PiclObject *picl_obj)
{
    switch (picl_obj->type) {
        case ObjectType_int:
        case ObjectType_bool:
            break;
        case ObjectType_str:
            PiclStr_delete(picl_obj->str_obj.value);
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
    free(picl_obj);
}







struct PiclObjectPool *PiclObjectPool_new()
{
    struct PiclObjectPool *object_pool = malloc(sizeof(struct PiclObjectPool));
    debug_print("call malloc PiclObjectPool\n");
    object_pool->size = 0;
    object_pool->prev = NULL;

    return object_pool;
}
struct PiclFreeList *PiclFreeList_new()
{
    struct PiclFreeList *free_list = malloc(sizeof(struct PiclFreeList));
    debug_print("PiclFreeList_new\n");
    free_list->size = 0;
    free_list->prev = NULL;

    return free_list;
}

void PiclObjectHeap_init(struct PiclObjectHeap *object_heap)
{
    object_heap->index = 0;

    object_heap->object_pool = PiclObjectPool_new();
    object_heap->free_list = PiclFreeList_new();

    object_heap->all_pool_object_size = 0;
    object_heap->all_free_object_size = 0;

    object_heap->frame_created_object_stack_size = 0;
}

struct PiclObject *PiclObjectHeap_alloc(struct PiclObjectHeap *object_heap)
{
    if(object_heap->all_free_object_size > 0){
        if(object_heap->free_list->size <= 0){
            struct PiclFreeList *old_free_list = object_heap->free_list;
            object_heap->free_list = old_free_list->prev;
            free(old_free_list);
        }
        --object_heap->all_free_object_size;
        debug_print("????????? free_list");
        debug_obj(object_heap->free_list->data[object_heap->free_list->size - 1]);
        return PiclObject_init(object_heap, object_heap->free_list->data[--object_heap->free_list->size]);
    }

    if(object_heap->object_pool->size >= OBJECT_POOL_DATA_SIZE){
        struct PiclObjectPool *new_object_pool = PiclObjectPool_new();
        new_object_pool->prev = object_heap->object_pool;
        object_heap->object_pool = new_object_pool;
    }

    ++object_heap->all_pool_object_size;
    debug_print("?????????? pool");
    debug_obj(&object_heap->object_pool->data[object_heap->object_pool->size]);
    return PiclObject_init(object_heap, &object_heap->object_pool->data[object_heap->object_pool->size++]);
}
void PiclObjectHeap_release(struct PiclObjectHeap *object_heap, struct PiclObject *object)
{
    if(object == NULL || object->ref_count != 0) return;

    if(object->type == ObjectType_instance){
        for(int i = 0; i < object->instance.fields_size; i++){
            if(object->instance.fields[i] == NULL) continue;

            --object->instance.fields[i]->ref_count;
            PiclObjectHeap_release(object_heap, object->instance.fields[i]);
        }
    }

    debug_print("!!!!!!!!!!! release obj");
    debug_obj(object);

    if(object_heap->free_list->size >= FREE_LIST_DATA_SIZE){
        struct PiclFreeList *new_free_list = PiclFreeList_new();
        new_free_list->prev = object_heap->free_list;
        object_heap->free_list = new_free_list;
    }

    ++object_heap->all_free_object_size;
    object_heap->free_list->data[object_heap->free_list->size++] = object;
}



