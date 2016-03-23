#include "picl-object.h"

struct PiclStrBuf *PiclStrBuf_new()
{
    struct PiclStrBuf *picl_str_buf = malloc(sizeof(struct PiclStrBuf));
//    debug_print("call malloc PiclStrBuf\n");

    picl_str_buf->index = 0;
    picl_str_buf->length = 0;
    picl_str_buf->buf = NULL;
    
    return picl_str_buf;
}

void PiclStrBuf_init(struct PiclStrBuf *strbuf)
{
    if(strbuf->length == 0){
        strbuf->length = 40;
        strbuf->buf = malloc(sizeof(char) * (strbuf->length + 1));
//        debug_print("call malloc PiclStrBuf\n");
    }
}
void PiclStrBuf_append(struct PiclStrBuf *strbuf, char c)
{
    if (strbuf->index == strbuf->length){
        strbuf->length *= 2;
        strbuf->buf = realloc(strbuf->buf, sizeof(char) * (strbuf->length + 1));
    }
    strbuf->buf[strbuf->index++] = c;
}
void PiclStrBuf_toStr(struct PiclStrBuf *strbuf, struct PiclStr **str_result)
{
    strbuf->buf[strbuf->index] = '\0';
    char *result = malloc(sizeof(char) * (strbuf->index + 1));
//        debug_print("call malloc PiclStrBuf\n");
    strncpy(result, strbuf->buf, strbuf->index);
    result[strbuf->index] = '\0';
    *str_result = PiclStr_newByChars(result, strbuf->index);
    strbuf->index = 0;
}
void PiclStrBuf_toInt(struct PiclStrBuf *strbuf, struct PiclStr **str_result, PiclInt *int_result)
{
    strbuf->buf[strbuf->index] = '\0';
    *int_result = strtoll(strbuf->buf, NULL, 10);
    char *result = malloc(sizeof(char) * (strbuf->index + 1));
//        debug_print("call malloc PiclStrBuf\n");
    strncpy(result, strbuf->buf, strbuf->index);
    result[strbuf->index] = '\0';
    *str_result = PiclStr_newByChars(result, strbuf->index);
    strbuf->index = 0;
}
bool PiclStrBuf_isEmpty(struct PiclStrBuf *strbuf)
{
    return strbuf->index == 0;
}

struct PiclStr *PiclStr_new()
{
    struct PiclStr *picl_str = malloc(sizeof(struct PiclStr));
//    debug_print("call malloc PiclStr_new init\n");
    picl_str->length = 0;
    picl_str->value = NULL;
    return picl_str;
}
void PiclStr_delete(struct PiclStr *picl_str)
{
    free(picl_str->value);
    free(picl_str);
}
struct PiclStr *PiclStr_newByInt(int value)
{
    struct PiclStr *picl_str = PiclStr_new();
    picl_str->length = 1;
    picl_str->value = malloc(sizeof(char) * 2);
//    debug_print("call malloc PiclStr_newByInt init\n");
    picl_str->value[0] = (char)value;
    picl_str->value[1] = '\0';
    return picl_str;
}
struct PiclStr *PiclStr_newByChars(char *value, int length)
{
    struct PiclStr *picl_str = PiclStr_new();
    picl_str->length = length;
    picl_str->value = value;
    return picl_str;
}
struct PiclStr *PiclStr_newByConst(const char *value)
{
    struct PiclStr *picl_str = PiclStr_new();
    picl_str->length = strlen(value);
    picl_str->value = (char *)value;
    return picl_str;
}
struct PiclStr *PiclStr_substr(struct PiclStr *value, int limit)
{
    int limit_value = limit;
    if(value->length < limit){
        limit_value = value->length;
    }
    char *result = malloc(sizeof(char) * (limit_value + 1));
//    debug_print("call malloc PiclStr_substr init\n");
    strncpy(result, value->value, limit_value);
    result[limit_value] = '\0';

    return PiclStr_newByChars(result, limit_value);
    
}
bool PiclStr_equals(struct PiclStr *value1, struct PiclStr *value2)
{
    if(value1->length != value2->length){
        return false;
    }

    return strncmp(value1->value, value2->value, value1->length) == 0;
}
bool PiclStr_equalsConst(struct PiclStr *value1, const char *value2)
{
    if(value1->length != (int)strlen(value2)){
        return false;
    }

    return strncmp(value1->value, value2, value1->length) == 0;
}

