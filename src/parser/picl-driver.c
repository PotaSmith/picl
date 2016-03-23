#include "picl-parser.h"

extern int yyparse(struct PiclDriver *picl_driver);

struct PiclDriver *PiclDriver_new()
{
    struct PiclDriver *picl_driver = malloc(sizeof(struct PiclDriver));
    picl_driver->file_name = NULL;
    picl_driver->strbuf = PiclStrBuf_new();

    picl_driver->nodes = NULL;

    picl_driver->yyin = NULL;
    picl_driver->yyout = NULL;

    picl_driver->trace_scanning = false;
    picl_driver->trace_parsing = false;

    picl_driver->line = 1;
    picl_driver->column = 1;
    picl_driver->in_round_bracket_count = 0;
    picl_driver->in_list_bracket_count = 0;
    picl_driver->in_str_join = false;
    picl_driver->token_cache = PiclTokenStack_new();

    picl_driver->node_buff_stack = PiclNodeBuffStack_new();

    return picl_driver;
}
                   
void error(char const *msg1, char const *msg2)
{
    printf("%s%s", msg1, msg2);
}

void scan_begin(struct PiclDriver *picl_driver)
{
    picl_driver->yyin = fopen(picl_driver->file_name, "r");
    if(picl_driver->yyin == NULL){
        error ("cannot open ", picl_driver->file_name);
        exit (1);
    }
}

void scan_end(struct PiclDriver *picl_driver)
{
    fclose(picl_driver->yyin);
}

int Picl_parse(struct PiclDriver *picl_driver, const char *file_name)
{
    picl_driver->file_name = file_name;
    scan_begin(picl_driver);
    int res = yyparse(picl_driver);
    scan_end(picl_driver);
    return res;
}
