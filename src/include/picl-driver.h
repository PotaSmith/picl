#ifndef PICL_DRIVER_H
# define PICL_DRIVER_H
# include "picl-object.h"


struct PiclDriver
{
    const char *file_name;

    struct PiclNodeArray *nodes;

    FILE *yyin;
    FILE *yyout;

    bool trace_scanning;
    bool trace_parsing;

    struct PiclStrBuf *strbuf;

    int line;
    int column;
    int in_round_bracket_count;
    int in_list_bracket_count;
    bool in_str_join;
    struct PiclTokenStack *token_cache;

    struct PiclNodeBuffStack *node_buff_stack;

};

struct PiclDriver *PiclDriver_new();
int Picl_parse(struct PiclDriver *picl_driver, const char *file_name);

#endif /* PICL_DRIVER_H */
