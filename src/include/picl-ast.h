#ifndef PICL_AST_H
# define PICL_AST_H

/*
 * picl-ast-dump.c
 */

void Picl_dump_program(struct PiclNodeArray *nodes);

/*
 * picl-ast-eval.c
 */

void Picl_eval_program(struct PiclNodeArray *nodes);

/*
 * picl-ast-compile.c
 */

void Picl_compile_program(struct PiclNodeArray *nodes);


#endif // ! PICL_AST_H
