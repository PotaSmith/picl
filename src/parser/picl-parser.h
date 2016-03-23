/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_SRC_PARSER_PICL_PARSER_H_INCLUDED
# define YY_YY_SRC_PARSER_PICL_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "src/parser/picl-parser.y" /* yacc.c:1909  */

#include <stdio.h>
#include <stdlib.h>
#include "picl-driver.h"
#include "picl-lex.h"
#include "picl-node-build.h"

#line 52 "src/parser/picl-parser.h" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    END = 0,
    T_SEQ = 258,
    T_FUN = 259,
    T_DEF = 260,
    T_CLA = 261,
    T_BEH = 262,
    T_PUB = 263,
    T_PRI = 264,
    T_DYN = 265,
    T_ALI = 266,
    T_CATCH = 267,
    T_REDEF = 268,
    T_AFT = 269,
    T_BEF = 270,
    T_LET = 271,
    T_FIN = 272,
    T_RETURN = 273,
    T_THROW = 274,
    T_IF = 275,
    T_THEN = 276,
    T_ELSE = 277,
    T_WHILE = 278,
    T_DO = 279,
    T_THAT = 280,
    T_CASE = 281,
    T_WHEN = 282,
    T_EACH = 283,
    T_MAP = 284,
    T_REDUCE = 285,
    T_FILTER = 286,
    T_END = 287,
    T_BREAK = 288,
    T_CONTINUE = 289,
    T_ECHO = 290,
    T_MINUS = 291,
    T_ASSIGN = 292,
    T_MOVE = 293,
    T_ARROW = 294,
    T_NEWLINE = 295,
    DOUBLE_EQUAL = 296,
    NOT_EQUAL = 297,
    GT_EQUAL = 298,
    LT_EQUAL = 299,
    T_AND = 300,
    T_OR = 301,
    T_NOT = 302,
    DOUBLE_ANB = 303,
    DOUBLE_PIPE = 304,
    COMPARE = 305,
    STRING_LITERAL = 306,
    IDENT = 307,
    DICT_IDENT = 308,
    LONG_LITERAL = 309,
    T_FOR = 310,
    NEG = 311
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 13 "src/parser/picl-parser.y" /* yacc.c:1909  */

    PiclInt  ival;
    struct PiclStr *sval;
    struct PiclNode *node;
    struct PiclNodeArray *nodes;
    struct PiclNode_FuncBody *func_body;
    struct PiclNode_FuncHead *func_head;

#line 131 "src/parser/picl-parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



int yyparse (struct PiclDriver *picl_driver);

#endif /* !YY_YY_SRC_PARSER_PICL_PARSER_H_INCLUDED  */
