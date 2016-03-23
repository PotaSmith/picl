#ifndef PICL_RUNTIME_H
# define PICL_RUNTIME_H
# include "picl-node.h"
# include "picl-object.h"
# include "picl-optimize-env.h"

# define FRAME_BLOCK_DATA_SIZE 100
# define OBJECT_POINTER_ARRAY_DATA_SIZE 1000

/*
 * PiclFrame フレーム
 *
 * 関数Callのたびに作られる
 * オブジェクトの配列はPiclObjectPointerArrayで確保
 */

struct PiclFrame
{
    struct PiclObject *this_obj;
    struct PiclObject **objects; // arg と variable

    int args_size;
    int variables_size;

    int args_index;

    int frame_created_object_stack_index;
};

/*
 * PiclFrameBlock フレームブロック
 * 何故かprev_frameとframes_sizeで2重管理してる、作りかけか？
 *
 */

struct PiclFrameBlock
{
    struct PiclFrame data[FRAME_BLOCK_DATA_SIZE];
    int size;

    struct PiclFrameBlock *prev;
    struct PiclFrameBlock *next;
};


/*
 * PiclObjectPointerArray
 *
 * オブジェクトのポインタを置くだけのもの
 * frameだけなく、list object などでも使うので object poolに移動
 * サイズ毎に用意 1 - 10 まで
 */

struct PiclObjectPointerArray
{
    struct PiclObject *data[OBJECT_POINTER_ARRAY_DATA_SIZE];
    int size;

    struct PiclObjectPointerArray *prev;
    struct PiclObjectPointerArray *next;
};

/*
 * PiclFramePool フレームプール
 *
 * フレームの数
 * 最初のフレームのポインタ
 * 最後のフレームのポインタ
 * フレームブロックの数
 * 最初のフレームブロックのポインタ
 * 最後のフレームブロックポインタ
 */

struct PiclFramePool
{
    int all_frames_size; // 未使用 stack over flow 用

    struct PiclFrameBlock *frame_blocks;
    int frame_blocks_size;

    struct PiclObjectPointerArray *frame_objects_stack;
};

/*
 * PiclRuntime ランタイム
 *
 * ダンプ先
 * エコー先
 * グローバル関数
 * グローバル変数
 * 最初のフレーム
 * 現在のフレーム
 */

struct PiclRuntime
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

    struct PiclFrame *start_frame;
    struct PiclFrame *current_frame;
    struct PiclObject *return_obj;

    struct PiclFramePool frame_pool;
    struct PiclObjectHeap object_heap;
};

void PiclFrame_add_argument(struct PiclFrame *frame, struct PiclObject *value);

struct PiclFrame *PiclRuntime_new_Frame(struct PiclRuntime *runtime, struct PiclObject *this_obj, int args_size, int variables_size);
struct PiclFrame *PiclRuntime_new_ObjectFrame(struct PiclRuntime *runtime, int args_size, int variables_size);

struct PiclRuntime *PiclRuntime_new(struct PiclOptimizeEnv *optimize_env);
void PiclRuntime_delete(struct PiclRuntime *runtime);
void PiclRuntime_push_Stack(struct PiclRuntime *runtime, struct PiclObject *object);
void PiclRuntime_pop_Frame(struct PiclRuntime *runtime);
void PiclRuntime_push_Frame(struct PiclRuntime *runtime, struct PiclFrame *frame);

void PiclRuntime_set_result(struct PiclRuntime *runtime, struct PiclObject *value);
struct PiclObject *PiclRuntime_get_result(struct PiclRuntime *runtime);

void PiclRuntime_set_variable(struct PiclRuntime *runtime, int index, struct PiclObject *value);
struct PiclObject *PiclRuntime_get_variable(struct PiclRuntime *runtime, int index);

void PiclRuntime_set_argument(struct PiclRuntime *runtime, int index, struct PiclObject *value);
struct PiclObject *PiclRuntime_get_argument(struct PiclRuntime *runtime, int index);

void PiclRuntime_set_decl(struct PiclRuntime *runtime, int index, struct PiclObject *value);
struct PiclObject *PiclRuntime_get_decl(struct PiclRuntime *runtime, int index);

void PiclRuntime_set_current_field(struct PiclRuntime *runtime, int index, struct PiclObject *value);
struct PiclObject *PiclRuntime_get_current_field(struct PiclRuntime *runtime, int index);

struct PiclObject *PiclRuntime_get_current_method(struct PiclRuntime *runtime, int index);

void PiclRuntime_set_member_field(struct PiclRuntime *runtime, struct PiclObject *obj, int index, struct PiclObject *value);
void PiclRuntime_set_field(struct PiclRuntime *runtime, int class_index, int field_index, int member_offset);

void PiclRuntime_set_method(struct PiclRuntime *runtime, int class_index, int method_index, struct PiclObject *value);
struct PiclObject *PiclRuntime_get_method(struct PiclRuntime *runtime, int class_index, int method_index);


#endif /* PICL_RUNTIME_H */
