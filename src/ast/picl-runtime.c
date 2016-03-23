#include "picl-runtime.h"

struct PiclObject **PiclFramePool_alloc_ObjectPointerArray(struct PiclFramePool *frame_pool, int size);
void PiclFramePool_release_ObjectPointerArray(struct PiclFramePool *frame_pool, int size);
struct PiclFrame *PiclFramePool_alloc_Frame(struct PiclFramePool *frame_pool, int args_size, int variables_size);


/*
 * PiclFrame
 */

struct PiclFrame *PiclRuntime_new_Frame(struct PiclRuntime *runtime, struct PiclObject *this_obj, int args_size, int variables_size)
{
    debug_print("PiclRuntime_new_Frame: args size %d, var size %d", args_size, variables_size);
    debug_obj(this_obj);

    struct PiclFrame *new_frame = PiclFramePool_alloc_Frame(&runtime->frame_pool, args_size, variables_size);
    new_frame->this_obj = this_obj;
    return new_frame;
}
struct PiclFrame *PiclRuntime_new_ObjectFrame(struct PiclRuntime *runtime, int args_size, int variables_size)
{
    debug_print("PiclRuntime_new_Frame: args size %d, var size %d", args_size, variables_size);
    debug_obj(runtime->current_frame->this_obj);
    struct PiclFrame *new_frame = PiclFramePool_alloc_Frame(&runtime->frame_pool, args_size, variables_size);
    new_frame->this_obj = runtime->current_frame->this_obj;
    return new_frame;
}

void PiclFrame_init(struct PiclFramePool *frame_pool, struct PiclFrame *frame, int args_size, int variables_size)
{
    frame->objects = PiclFramePool_alloc_ObjectPointerArray(frame_pool, args_size + variables_size);

    frame->args_size = args_size;
    frame->variables_size = variables_size;

    frame->args_index = 0;

    frame->frame_created_object_stack_index = 0;
}

struct PiclFrame *PiclFrame_new(struct PiclFramePool *frame_pool, int args_size, int variables_size)
{
    struct PiclFrame *frame = malloc(sizeof(struct PiclFrame));
    debug_print("call malloc PiclFrame\n");

    PiclFrame_init(frame_pool, frame, args_size, variables_size);

    return frame;
}

void PiclFrame_release(struct PiclObjectHeap *object_heap, struct PiclFramePool *frame_pool, struct PiclFrame *frame)
{
    for (int i = 0; i < frame->args_size + frame->variables_size; ++i)
    {
        --frame->objects[i]->ref_count;
        PiclObjectHeap_release(object_heap, frame->objects[i]);
    }
    for (int i = object_heap->frame_created_object_stack_size -1; i >= frame->frame_created_object_stack_index; --i)
    {
        if(object_heap->frame_created_object_stack[i] != NULL) --object_heap->frame_created_object_stack[i]->ref_count;
        PiclObjectHeap_release(object_heap, object_heap->frame_created_object_stack[i]);
    }

    debug_print("frame_created_object_stack_size down %d to %d\n", object_heap->frame_created_object_stack_size, frame->frame_created_object_stack_index);
    object_heap->frame_created_object_stack_size = frame->frame_created_object_stack_index;

    PiclFramePool_release_ObjectPointerArray(frame_pool, frame->args_size + frame->variables_size);
}

void PiclFrame_delete(struct PiclObjectHeap *object_heap, struct PiclFramePool *frame_pool, struct PiclFrame *frame)
{
    PiclFrame_release(object_heap, frame_pool, frame);
    free(frame->objects);
    free(frame);
}

void PiclFrame_set_variable(struct PiclFrame *frame, int index, struct PiclObject *value)
{
    frame->objects[frame->args_size + index] = value;
}

struct PiclObject *PiclFrame_get_variable(struct PiclFrame *frame, int index)
{
    return frame->objects[frame->args_size + index];
}

void PiclFrame_add_argument(struct PiclFrame *frame, struct PiclObject *value)
{
    debug_print("PiclFrame_add_argument: index %d", frame->args_index);
    debug_obj(value);
    debug_print("PiclFrame_add_argument: before this obj");
    debug_obj(frame->this_obj);
    frame->objects[frame->args_index++] = value;
    ++value->ref_count;
    debug_print("PiclFrame_add_argument: before this obj");
    debug_obj(frame->this_obj);
}

void PiclFrame_set_argument(struct PiclFrame *frame, int index, struct PiclObject *value)
{
    frame->objects[index] = value;
}

struct PiclObject *PiclFrame_get_argument(struct PiclFrame *frame, int index)
{
    return frame->objects[index];
}

/*
 * PiclFrameBlock
 */

struct PiclFrameBlock *PiclFrameBlock_new()
{
    struct PiclFrameBlock *frame_blocks = malloc(sizeof(struct PiclFrameBlock));
    debug_print("call malloc PiclFrameBlock\n");

    frame_blocks->size = 0;
    frame_blocks->prev = NULL;
    frame_blocks->next = NULL;

    return frame_blocks;
}

void PiclFrameBlock_delete(struct PiclFrameBlock *frame_blocks)
{
    free(frame_blocks);
}

struct PiclFrame *PiclFrameBlock_alloc(struct PiclFramePool *frame_pool, int args_size, int variables_size)
{
    struct PiclFrame *new_frame = &frame_pool->frame_blocks->data[frame_pool->frame_blocks->size++];

    PiclFrame_init(frame_pool, new_frame, args_size, variables_size);

    return new_frame;
}
void PiclFrameBlock_release(struct PiclObjectHeap *object_heap, struct PiclFramePool *frame_pool, struct PiclFrameBlock *frame_blocks, struct PiclFrame *frame)
{
    --frame_blocks->size;

    PiclFrame_release(object_heap, frame_pool, frame);
}

/*
 * PiclObjectPointerArray
 */

struct PiclObjectPointerArray *PiclObjectPointerArray_new()
{
    struct PiclObjectPointerArray *frame_objects_stack = malloc(sizeof(struct PiclObjectPointerArray));
    debug_print("call malloc PiclObjectPointerArray\n");

    frame_objects_stack->size = 0;

    frame_objects_stack->prev = NULL;
    frame_objects_stack->next = NULL;

    return frame_objects_stack;
}

void PiclObjectPointerArray_delete(struct PiclObjectPointerArray *frame_objects_stack)
{
    free(frame_objects_stack);
}

struct PiclObject **PiclObjectPointerArray_alloc(struct PiclObjectPointerArray *frame_objects_stack, int size)
{
    struct PiclObject **start = &frame_objects_stack->data[frame_objects_stack->size];
    frame_objects_stack->size += size;
    return start;
}
void PiclObjectPointerArray_release(struct PiclObjectPointerArray *frame_objects_stack, int size)
{
    frame_objects_stack->size -= size;
}


/*
 * PiclFramePool
 */

void PiclFramePool_init(struct PiclFramePool *frame_pool)
{
    frame_pool->all_frames_size = 1;

    frame_pool->frame_blocks = PiclFrameBlock_new();

    frame_pool->frame_blocks_size = 0;

    frame_pool->frame_objects_stack = PiclObjectPointerArray_new();
}

struct PiclFrame *PiclFramePool_alloc_Frame(struct PiclFramePool *frame_pool, int args_size, int variables_size)
{
    if(frame_pool->frame_blocks->size >= FRAME_BLOCK_DATA_SIZE){
        if(frame_pool->frame_blocks->next != NULL){
            frame_pool->frame_blocks = frame_pool->frame_blocks->next;
        }
        else{
            struct PiclFrameBlock *new_frame_blocks = PiclFrameBlock_new();
            new_frame_blocks->prev = frame_pool->frame_blocks;
            frame_pool->frame_blocks->next = new_frame_blocks;
            frame_pool->frame_blocks = new_frame_blocks;
        }
    }

    return PiclFrameBlock_alloc(frame_pool, args_size, variables_size);
}
struct PiclFrame *PiclFramePool_release_Frame(struct PiclObjectHeap *object_heap, struct PiclFramePool *frame_pool, struct PiclFrame *frame)
{
    PiclFrameBlock_release(object_heap, frame_pool, frame_pool->frame_blocks, frame);

    if(frame_pool->frame_blocks->size <= 0){
        frame_pool->frame_blocks = frame_pool->frame_blocks->prev;

        if(frame_pool->frame_blocks->next != NULL && frame_pool->frame_blocks->next->next != NULL){
            PiclFrameBlock_delete(frame_pool->frame_blocks->next->next);
            frame_pool->frame_blocks->next->next = NULL;
        }

    }

    struct PiclFrame *prev_frame = &frame_pool->frame_blocks->data[frame_pool->frame_blocks->size - 1];

    if(prev_frame == NULL){
        printf("Exception : frame release when top frame\n");
        exit(1);
    }

    return prev_frame;
}
struct PiclObject **PiclFramePool_alloc_ObjectPointerArray(struct PiclFramePool *frame_pool, int size)
{
    if((OBJECT_POINTER_ARRAY_DATA_SIZE - frame_pool->frame_objects_stack->size) <= size){
        if(frame_pool->frame_objects_stack->next != NULL){
            frame_pool->frame_objects_stack = frame_pool->frame_objects_stack->next;
        }
        else{
            struct PiclObjectPointerArray *new_frame_objects_stack = PiclObjectPointerArray_new();
            new_frame_objects_stack->prev = frame_pool->frame_objects_stack;
            frame_pool->frame_objects_stack->next = new_frame_objects_stack;
            frame_pool->frame_objects_stack = new_frame_objects_stack;
        }
    } 

    return PiclObjectPointerArray_alloc(frame_pool->frame_objects_stack, size);
}

void PiclFramePool_release_ObjectPointerArray(struct PiclFramePool *frame_pool, int size)
{
    PiclObjectPointerArray_release(frame_pool->frame_objects_stack, size);

    if(frame_pool->frame_objects_stack == NULL){
        printf("Exception : frame object release when top frame\n");
        exit(1);
    }

    // 0になることもありうる
    if(frame_pool->frame_objects_stack->size <= 0 && frame_pool->frame_objects_stack->prev != NULL){
        frame_pool->frame_objects_stack = frame_pool->frame_objects_stack->prev;

        if(frame_pool->frame_objects_stack->next != NULL && frame_pool->frame_objects_stack->next->next != NULL){
            PiclObjectPointerArray_delete(frame_pool->frame_objects_stack->next->next);
            frame_pool->frame_objects_stack->next->next = NULL;
        }
    }
}

/*
 * PiclRuntime
 */

struct PiclRuntime *PiclRuntime_new(struct PiclOptimizeEnv *optimize_env)
{
    trueObject = PiclObject_new_bool(true);
    falseObject = PiclObject_new_bool(false);

    struct PiclRuntime *runtime = malloc(sizeof(struct PiclRuntime));
    debug_print("call malloc PiclRuntime\n");

    runtime->echo_stream = stdout;

    PiclFramePool_init(&runtime->frame_pool);
    PiclObjectHeap_init(&runtime->object_heap);

    runtime->current_frame = NULL;
    runtime->current_frame = PiclRuntime_new_Frame(runtime, NULL, 0, 0);
    runtime->start_frame = runtime->current_frame;
    runtime->return_obj = NULL;

    runtime->decl_objs_size = optimize_env->decl_names->size;
    runtime->decl_objs = malloc(sizeof(struct PiclObject*) * runtime->decl_objs_size);
    debug_print("call malloc PiclObject*\n");


    runtime->class_size = optimize_env->class_names->size;
    runtime->field_size = optimize_env->field_names->size;
    runtime->method_size = optimize_env->method_names->size;


    runtime->method_objs_size = optimize_env->method_size;
    runtime->method_objs = malloc(sizeof(struct PiclObject*) * runtime->method_objs_size);
    debug_print("call malloc PiclObject*\n");

    runtime->class_field_table = malloc(sizeof(int*) * runtime->class_size);
    runtime->class_field_addresses = calloc(runtime->class_size * runtime->field_size, sizeof(int));
    for (int i=0; i < runtime->class_size; i++) {
        runtime->class_field_table[i] = runtime->class_field_addresses + i * runtime->field_size;
    }
    runtime->class_method_table = malloc(sizeof(struct PiclObject**) * runtime->class_size);
    runtime->class_method_addresses = calloc(runtime->class_size * runtime->method_size, sizeof(struct PiclObject*));
    for (int i=0; i < runtime->class_size; i++) {
        runtime->class_method_table[i] = runtime->class_method_addresses + i * runtime->method_size;
    }

    return runtime;
}

void PiclRuntime_delete(struct PiclRuntime *runtime)
{
    free(runtime->decl_objs);
    free(runtime);
}

void PiclRuntime_push_Stack(struct PiclRuntime *runtime, struct PiclObject *object)
{
    if(runtime->object_heap.frame_created_object_stack_size >= OBJECT_HEAP_OBJECT_STACK_SIZE){
        printf("Exception : frame_created_object_stack over \n");
        exit(1);
    }
    runtime->object_heap.frame_created_object_stack[runtime->object_heap.frame_created_object_stack_size++] = object;
    if(object != NULL){
        ++object->ref_count;
    }

    debug_print("PiclRuntime_push_Stack");
    debug_obj(object);
    debug_print("frame_created_object_stack up to %d\n", runtime->object_heap.frame_created_object_stack_size);
    debug_print("dump PiclRuntime_push_Stack\n\n");

//    for (int i=0; i < runtime->object_heap.frame_created_object_stack_size; i++) {
//        debug_print("index %d: ", i);
//        debug_obj(runtime->object_heap.frame_created_object_stack[i]);
//    }
    debug_print("\n\n");
}

void PiclRuntime_pop_Frame(struct PiclRuntime *runtime)
{
    debug_print("PiclRuntime_pop_Frame: var size %d, arg size %d, this obj", runtime->current_frame->variables_size, runtime->current_frame->args_size);
    debug_obj(runtime->current_frame->this_obj);
    runtime->current_frame = PiclFramePool_release_Frame(&runtime->object_heap, &runtime->frame_pool, runtime->current_frame);
    debug_print("PiclRuntime_pop_Frame: var size %d, arg size %d, this obj", runtime->current_frame->variables_size, runtime->current_frame->args_size);
    debug_obj(runtime->current_frame->this_obj);
}

void PiclRuntime_push_Frame(struct PiclRuntime *runtime, struct PiclFrame *frame)
{
    frame->frame_created_object_stack_index = runtime->object_heap.frame_created_object_stack_size;
    debug_print("frame_created_object_stack_index set %d\n", runtime->object_heap.frame_created_object_stack_size);

    debug_print("PiclRuntime_push_Frame: var size %d, arg size %d, this obj", runtime->current_frame->variables_size, runtime->current_frame->args_size);
    debug_obj(runtime->current_frame->this_obj);
    runtime->current_frame = frame;
    debug_print("PiclRuntime_push_Frame: var size %d, arg size %d, this obj", runtime->current_frame->variables_size, runtime->current_frame->args_size);
    debug_obj(runtime->current_frame->this_obj);
}

void PiclRuntime_set_result(struct PiclRuntime *runtime, struct PiclObject *value)
{
    debug_print("PiclRuntime_set_result");
    debug_obj(value);
    ++value->ref_count;
    runtime->return_obj = value;
}

struct PiclObject *PiclRuntime_get_result(struct PiclRuntime *runtime)
{
    struct PiclObject *return_obj = runtime->return_obj;
    if(return_obj != NULL) {
        --return_obj->ref_count;
    }
    runtime->return_obj = NULL;

    debug_print("PiclRuntime_get_result");
    debug_obj(return_obj);
    return return_obj;
}

void PiclRuntime_set_variable(struct PiclRuntime *runtime, int index, struct PiclObject *value)
{
    debug_print("PiclRuntime_set_variable: index %d", index);
    debug_obj(value);
    ++value->ref_count;
    PiclFrame_set_variable(runtime->current_frame, index, value);
}

struct PiclObject *PiclRuntime_get_variable(struct PiclRuntime *runtime, int index)
{
    debug_print("PiclRuntime_get_variable: index %d", index);
    debug_obj(PiclFrame_get_variable(runtime->current_frame, index));
    return PiclFrame_get_variable(runtime->current_frame, index);
}

void PiclRuntime_set_argument(struct PiclRuntime *runtime, int index, struct PiclObject *value)
{
    debug_print("PiclRuntime_set_argument: index %d", index);
    debug_obj(value);
    ++value->ref_count;
    PiclFrame_set_argument(runtime->current_frame, index, value);
}

struct PiclObject *PiclRuntime_get_argument(struct PiclRuntime *runtime, int index)
{
    debug_print("PiclRuntime_get_argument: index %d", index);
    debug_obj(PiclFrame_get_argument(runtime->current_frame, index));
    return PiclFrame_get_argument(runtime->current_frame, index);
}

void PiclRuntime_set_decl(struct PiclRuntime *runtime, int index, struct PiclObject *value)
{
    debug_print("PiclRuntime_set_decl: index %d", index);
    debug_obj(value);

    ++value->ref_count;
    runtime->decl_objs[index] = value;
}

struct PiclObject *PiclRuntime_get_decl(struct PiclRuntime *runtime, int index)
{
    if(index == -1){ return NULL; }

    debug_print("PiclRuntime_get_decl: index %d", index);
    debug_obj(runtime->decl_objs[index]);

    return runtime->decl_objs[index];
}

void PiclRuntime_set_current_field(struct PiclRuntime *runtime, int index, struct PiclObject *value)
{
    debug_print("PiclRuntime_set_current_field: this obj");
    debug_obj(runtime->current_frame->this_obj);
    debug_print("PiclRuntime_set_current_field: member offset %d", index);
    debug_obj(value);

    ++value->ref_count;
    runtime->current_frame->this_obj->instance.fields[index] = value;
}

struct PiclObject *PiclRuntime_get_current_field(struct PiclRuntime *runtime, int index)
{
    if(index == -1){ return NULL; }

    debug_print("PiclRuntime_get_current_field: this obj");
    debug_obj(runtime->current_frame->this_obj);
    debug_print("PiclRuntime_get_current_field: member offset %d", index);
    debug_obj(runtime->current_frame->this_obj->instance.fields[index]);

    return runtime->current_frame->this_obj->instance.fields[index];
}
struct PiclObject *PiclRuntime_get_current_method(struct PiclRuntime *runtime, int index)
{
    if(index == -1){ return NULL; }

//    debug_print("PiclRuntime_get_current_method class_obj %d\n", runtime->current_frame->this_obj == NULL);

    return runtime->current_frame->this_obj->instance.class_obj->class_obj.methods[index];
}

void PiclRuntime_set_member_field(struct PiclRuntime *runtime, struct PiclObject *obj, int index, struct PiclObject *value)
{
    debug_print("PiclRuntime_set_member_field: class index %d, field index %d, member offset %d", obj->instance.class_obj->class_obj.class_name_index, index, runtime->class_field_table[obj->instance.class_obj->class_obj.class_name_index][index]);
    debug_obj(obj);
    ++value->ref_count;
    obj->instance.fields[runtime->class_field_table[obj->instance.class_obj->class_obj.class_name_index][index]] = value;
}

void PiclRuntime_set_field(struct PiclRuntime *runtime, int class_index, int field_index, int member_offset)
{
    debug_print("PiclRuntime_set_field: class_index %d, field_index %d, member_offset %d\n", class_index, field_index, member_offset);
    runtime->class_field_table[class_index][field_index] = member_offset;
}

void PiclRuntime_set_method(struct PiclRuntime *runtime, int class_index, int method_index, struct PiclObject *value)
{
    debug_print("PiclRuntime_set_method: name %s, class_index %d, method_index %d", value->method_obj.name->value, class_index, method_index);
    debug_obj(value);

    ++value->ref_count;
    runtime->method_objs[method_index] = value;
    runtime->class_method_table[class_index][method_index] = value;
}

struct PiclObject *PiclRuntime_get_method(struct PiclRuntime *runtime, int class_index, int method_index)
{
    debug_print("PiclRuntime_get_method: class_index %d, method_index %d", class_index, method_index);
    debug_obj(runtime->class_method_table[class_index][method_index]);
    return runtime->class_method_table[class_index][method_index];
}


