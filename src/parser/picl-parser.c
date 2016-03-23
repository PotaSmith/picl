/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */

#line 67 "src/parser/picl-parser.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "picl-parser.h".  */
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
#line 1 "src/parser/picl-parser.y" /* yacc.c:355  */

#include <stdio.h>
#include <stdlib.h>
#include "picl-driver.h"
#include "picl-lex.h"
#include "picl-node-build.h"

#line 105 "src/parser/picl-parser.c" /* yacc.c:355  */

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
#line 13 "src/parser/picl-parser.y" /* yacc.c:355  */

    PiclInt  ival;
    struct PiclStr *sval;
    struct PiclNode *node;
    struct PiclNodeArray *nodes;
    struct PiclNode_FuncBody *func_body;
    struct PiclNode_FuncHead *func_head;

#line 184 "src/parser/picl-parser.c" /* yacc.c:355  */
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

/* Copy the second part of user declarations.  */

#line 214 "src/parser/picl-parser.c" /* yacc.c:358  */
/* Unqualified %code blocks.  */
#line 21 "src/parser/picl-parser.y" /* yacc.c:359  */

extern int yylex(YYSTYPE *lvalp, YYLTYPE *llocp, struct PiclDriver *picl_driver);
extern void yyerror(YYLTYPE *llocp, struct PiclDriver *picl_driver, char const *msg);

#line 221 "src/parser/picl-parser.c" /* yacc.c:359  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  33
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1110

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  79
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  68
/* YYNRULES -- Number of rules.  */
#define YYNRULES  186
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  347

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   311

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,    63,    69,    58,     2,
      73,    78,    68,    65,    61,    66,    72,    67,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    64,     2,
      60,    56,    59,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    76,     2,    77,    62,     2,    70,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    74,    57,    75,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    71
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   143,   143,   144,   145,   148,   151,   152,   155,   156,
     157,   158,   159,   162,   163,   166,   169,   172,   175,   176,
     179,   180,   181,   184,   185,   188,   189,   192,   195,   196,
     199,   200,   203,   204,   207,   210,   211,   214,   215,   218,
     221,   222,   225,   226,   227,   228,   229,   233,   236,   240,
     243,   246,   247,   250,   251,   252,   255,   256,   259,   262,
     263,   266,   269,   270,   273,   274,   277,   280,   281,   282,
     285,   286,   289,   290,   293,   296,   299,   300,   303,   304,
     310,   311,   314,   315,   318,   319,   320,   321,   322,   323,
     324,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     338,   341,   342,   345,   346,   349,   351,   352,   353,   354,
     355,   357,   359,   360,   362,   363,   364,   365,   366,   368,
     369,   370,   372,   373,   375,   376,   377,   378,   379,   380,
     382,   384,   386,   387,   389,   390,   391,   394,   395,   398,
     399,   400,   401,   402,   403,   406,   407,   410,   411,   414,
     415,   418,   419,   420,   423,   424,   427,   428,   429,   433,
     434,   435,   438,   439,   442,   443,   446,   447,   450,   451,
     454,   455,   458,   459,   462,   463,   466,   467,   468,   469,
     470,   471,   472,   473,   474,   475,   476
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "$undefined", "T_SEQ", "T_FUN", "T_DEF",
  "T_CLA", "T_BEH", "T_PUB", "T_PRI", "T_DYN", "T_ALI", "T_CATCH",
  "T_REDEF", "T_AFT", "T_BEF", "T_LET", "T_FIN", "T_RETURN", "T_THROW",
  "T_IF", "T_THEN", "T_ELSE", "T_WHILE", "T_DO", "T_THAT", "T_CASE",
  "T_WHEN", "T_EACH", "T_MAP", "T_REDUCE", "T_FILTER", "T_END", "T_BREAK",
  "T_CONTINUE", "T_ECHO", "T_MINUS", "T_ASSIGN", "T_MOVE", "T_ARROW",
  "T_NEWLINE", "DOUBLE_EQUAL", "NOT_EQUAL", "GT_EQUAL", "LT_EQUAL",
  "T_AND", "T_OR", "T_NOT", "DOUBLE_ANB", "DOUBLE_PIPE", "COMPARE",
  "STRING_LITERAL", "IDENT", "DICT_IDENT", "LONG_LITERAL", "T_FOR", "'='",
  "'|'", "'&'", "'>'", "'<'", "','", "'^'", "'$'", "':'", "'+'", "'-'",
  "'/'", "'*'", "'%'", "'`'", "NEG", "'.'", "'('", "'{'", "'}'", "'['",
  "']'", "')'", "$accept", "top_level", "new_node_stack", "decls", "decl",
  "def_newline", "func_decl", "seq_decl", "seq_members_nodes",
  "seq_members", "seq_member", "redef_decls", "redef_decl", "def_decl",
  "decl_body", "decl_value", "decl_primary", "cla_decl", "extentions",
  "indent_values", "cla_members_nodes", "cla_members", "cla_member",
  "field_value", "alias_value", "beh_decl", "beh_members_nodes",
  "beh_members", "beh_member", "func_body", "let_decls_nodes", "let_decls",
  "let_decl", "stmt_newline", "then_newline", "stmts_nodes", "stmts",
  "stmt_line", "guard_stmts", "guard_stmt", "without_guard_stmts_nodes",
  "without_guard_stmts", "without_guard_stmt_line", "do_newline",
  "list_stmt_chain", "list_stmt", "stmt", "when_stmts_nodes", "when_stmts",
  "when_stmt", "expr", "indent_value", "primary", "call_func_args",
  "call_func_stmts", "args", "arg", "dict_values", "dict_value",
  "func_head", "catch_head", "func_def_args", "func_def_keyword_args",
  "args_def", "arg_def", "arg_pattern", "primary_value",
  "keyword_and_ident", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,    61,   124,    38,    62,
      60,    44,    94,    36,    58,    43,    45,    47,    42,    37,
      96,   311,    46,    40,   123,   125,    91,    93,    41
};
# endif

#define YYPACT_NINF -226

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-226)))

#define YYTABLE_NINF -6

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-6)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     178,  1034,  1034,  1034,  1034,  1034,   236,    43,   236,  -226,
    -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,
    -226,  -226,  -226,  -226,  -226,  -226,   -16,    37,   -28,    37,
     -16,   -16,   236,  -226,  -226,  -226,    37,  -226,  -226,  -226,
     -25,   895,    37,    37,   514,  -226,   267,  -226,    73,  -226,
     895,    36,  -226,  -226,  -226,   -10,  -226,  -226,  -226,  -226,
    -226,   444,  -226,     3,    51,    46,  -226,  -226,  -226,   158,
    -226,   444,   444,   457,   444,   444,  -226,  -226,   444,   444,
     444,   444,   444,  -226,    84,    89,  -226,   361,  -226,   692,
    -226,   125,  -226,   -17,  -226,  -226,  -226,   895,    76,  -226,
     895,    94,  -226,    62,  -226,   654,    78,    90,   444,  -226,
     -19,  -226,    93,   514,  1034,  1034,  1034,  1034,   348,    81,
     158,  -226,  -226,   803,   803,   533,   570,   803,   803,   617,
     729,    59,    59,   330,  -226,  1034,  1034,  1034,  1034,  -226,
    -226,   444,   444,   444,   444,   444,   444,   444,   444,   444,
     444,   444,   444,   444,   444,   444,   444,   444,   444,   444,
     444,   444,   444,  1034,    80,    85,  1034,   125,  -226,   895,
    -226,  -226,  -226,  -226,   895,  -226,  -226,    94,  -226,  1034,
    1034,    62,  -226,  -226,  -226,   444,   803,  1015,  -226,   444,
      46,  -226,    37,   -21,    37,    -8,   105,  -226,    37,    99,
      91,  -226,  -226,  -226,  -226,  -226,  -226,  -226,    24,   131,
    -226,  -226,  -226,  -226,  -226,    54,    54,   103,    54,   803,
     892,   926,   926,   926,   926,    59,    59,    59,  1006,   960,
     926,   926,   382,   382,  1036,   203,   203,   258,   258,   258,
     840,  -226,  -226,   387,  -226,  -226,   100,  -226,    37,  -226,
    -226,    29,  -226,   139,   121,     2,  -226,   803,  -226,   803,
    -226,   444,  -226,   444,   514,   895,  -226,  -226,     8,  -226,
    -226,  -226,    79,   148,  -226,   444,    24,  -226,  -226,   330,
    -226,  -226,  -226,  -226,  -226,  1034,  -226,  -226,   444,   444,
     444,   803,     6,  -226,  -226,  -226,  -226,   444,  -226,   444,
    -226,  -226,   766,  -226,  -226,  -226,   -13,     7,  -226,   895,
    -226,  -226,  -226,  -226,  -226,  -226,   729,  -226,  -226,   147,
    -226,  -226,  -226,    54,  -226,   185,   803,   387,  -226,  -226,
     803,  -226,   803,  -226,  -226,  -226,    13,   156,  -226,   330,
    -226,  -226,  -226,  -226,  -226,  -226,  -226
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     0,     0,     0,     0,     0,     3,     6,
       8,     9,    10,    11,    12,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   176,    35,     0,   159,     0,
      35,    35,     4,     1,     7,     5,     0,    13,    14,     5,
       5,     0,     0,     0,     0,     5,     0,    15,    56,   164,
       0,   160,   175,   174,    27,    28,    30,    33,    32,     5,
       5,     0,     5,     0,    36,    37,   137,   139,   140,     0,
      16,    93,    95,   177,   180,     0,    96,    97,   186,     0,
       0,     0,     0,    66,    68,    69,    72,     0,    71,    91,
     105,     0,    57,     0,   168,   170,   173,   172,     5,    29,
       0,     0,    34,     0,    49,     0,     0,     0,     0,   141,
       0,   154,     0,     0,     0,     0,     0,     0,     0,     0,
      17,    18,    20,    92,    94,     0,     0,     5,    98,     0,
       0,   136,   135,    67,    73,     0,     0,     0,     0,   106,
      83,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     5,     5,     0,    58,    59,     0,
     165,   171,   172,   166,     0,   161,    31,    39,    40,     0,
       0,    50,    51,   143,   144,     0,   156,     0,   142,     0,
      38,   138,     0,   159,     0,   159,     0,     5,     0,     0,
       0,    19,    65,    64,     5,    81,    80,     5,     0,     0,
      82,    63,    62,     5,    70,     5,     5,     0,     5,    99,
     132,   124,   125,   126,   127,   119,   120,   121,   131,   130,
     128,   129,   122,   123,   133,   114,   115,   117,   116,   118,
       0,   111,   145,     0,   112,   147,     0,   113,     0,    60,
     169,     0,    41,     0,     0,   159,    52,   158,   155,   157,
       5,     0,     5,     0,     0,     0,     5,     5,     0,    23,
      25,    26,     0,     0,     5,     0,   100,   101,   110,     0,
      74,     5,    85,     5,    87,     0,     5,    89,     0,     0,
     152,   151,     0,   149,   148,     5,   167,     0,     5,     0,
      44,    42,     0,    45,    43,    46,     0,     0,    21,     0,
      22,    24,     5,   107,   109,   104,     0,   102,    75,    77,
      79,    84,    86,     0,    88,   134,   153,     0,   146,    61,
      53,    55,    54,    47,    48,   162,     0,     0,     5,    76,
       5,   150,   163,   108,   103,    78,    90
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -226,  -226,    47,   208,    28,    21,  -226,  -226,  -226,  -226,
      96,  -226,   -48,  -226,  -226,   122,  -226,  -189,   118,  -226,
    -226,  -226,   -89,   -42,  -226,  -187,  -226,  -226,    42,  -225,
    -226,  -226,    58,   -88,  -226,   -57,  -226,  -226,  -226,   150,
    -226,  -226,  -226,  -198,  -226,   107,  -127,   -76,  -226,   -30,
      48,  -105,   -37,  -226,  -226,  -226,   -82,  -226,    60,   -94,
    -226,  -226,  -226,  -165,    82,   155,   -31,    -1
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     7,    46,     8,     9,    39,    10,    11,    70,   120,
     121,   268,   269,    12,    54,    55,    56,    13,    36,    64,
     102,   177,   122,   301,   305,    14,   104,   181,   182,    47,
      92,   167,   168,   213,   204,    48,    83,    84,    85,    86,
     280,   318,   319,   207,    87,   140,    88,   209,   276,   277,
      89,    65,    90,   244,   247,   292,   293,   110,   111,    27,
     198,    51,   175,    93,    94,    95,    67,    68
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      26,    28,    29,    30,    31,   106,   214,    66,   190,   251,
      57,   270,   178,   271,     4,     5,   261,   281,   283,    96,
     286,   192,   194,    15,    16,    17,    18,   334,    19,   263,
      99,    20,    21,    22,    23,   300,    34,   303,    24,   299,
      58,   308,   187,    33,   169,    40,   274,   100,    35,    97,
      41,   275,    40,    49,   107,    25,   108,    45,   188,   114,
      34,   170,   112,    59,    60,    40,    96,   327,   169,    57,
     179,   180,   248,   331,   169,    40,    66,    37,   205,   270,
     109,   271,    44,   310,   328,   335,   254,    50,   252,    -5,
     169,   342,    69,    38,   206,    91,   172,     4,     5,    58,
     307,   312,   115,   116,   296,   117,   101,   103,   246,   105,
      98,   313,   113,   191,   193,   195,   196,   199,   114,   123,
     124,   125,   126,   127,   133,   340,   128,   129,   130,   131,
     132,   163,   164,   165,   215,   216,   217,   218,    96,   282,
     284,   166,   287,    96,   336,   174,    80,   272,    42,    43,
     273,   173,   320,   184,   185,   200,   186,   189,   242,   306,
     245,   264,   241,   278,   285,    28,   115,   116,    97,   117,
     118,   119,   267,    97,   208,   294,   297,   298,   253,   255,
     314,     1,     2,     3,     4,     5,   112,   339,   343,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   243,   345,   260,    32,   262,   201,   315,     6,   266,
     311,   304,   176,   256,   321,   249,   322,    66,   338,   324,
     147,   148,   149,   257,    96,   134,   210,   259,   329,     1,
       2,     3,     4,     5,   265,   341,   317,   258,   147,   148,
     149,   250,   171,     0,     0,   337,     0,   163,   164,   165,
     279,     0,   208,   208,    97,   208,     0,     0,     0,   295,
     159,   160,   161,   162,     0,   163,   164,   165,    96,     0,
       0,   344,     0,   346,   323,    71,    72,    73,    16,    17,
      74,   291,    19,    75,     0,    20,    21,    22,    23,     0,
      76,    77,    78,   147,   148,   149,     0,     0,    97,   302,
       0,   302,     0,     0,   309,     0,     0,     0,    52,    25,
       0,    53,    79,   316,    80,    81,     0,     0,   162,     0,
     163,   164,   165,    82,     0,     0,   325,   326,   132,     0,
      61,    62,     0,    63,     0,   330,     0,   332,    71,    72,
      73,    16,    17,    74,     0,    19,    75,     0,    20,    21,
      22,    23,     0,    76,    77,    78,     0,     0,    15,    16,
      17,    18,     0,    19,     0,   291,    20,    21,    22,    23,
       0,    52,    25,    24,    53,    79,     0,     0,    81,   135,
     136,   137,   138,   139,     0,     0,    82,     0,     0,     0,
      25,     0,     0,    61,    62,     0,    63,    73,    16,    17,
      74,     0,    19,    75,     0,    20,    21,    22,    23,     0,
       0,   197,    24,     0,     0,     0,     0,   147,   148,   149,
       0,     0,   150,     0,     0,     0,     0,     0,    52,    25,
     289,    53,    79,     0,     0,    81,   156,   157,   158,   159,
     160,   161,   162,   290,   163,   164,   165,     0,     0,     0,
      61,    62,     0,    63,    73,    16,    17,    74,     0,    19,
      75,     0,    20,    21,    22,    23,     0,    73,     0,    24,
      74,     0,    19,    75,     0,    20,    21,    22,    23,     0,
       0,     0,    24,     0,     0,    52,    25,     0,    53,    79,
       0,     0,    81,     0,     0,     0,     0,     0,    52,    25,
      82,    53,    79,     0,     0,    81,     0,    61,    62,     0,
      63,     0,     0,    82,     0,     0,     0,     0,     0,     0,
      61,    62,     0,    63,    15,    16,    17,    18,     0,    19,
       0,     0,    20,    21,    22,    23,     0,     0,     0,    24,
       0,     0,     0,     0,   202,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    52,    25,     0,    53,     0,
       0,   142,     0,   203,   143,   144,   145,   146,   147,   148,
     149,     0,     0,   150,     0,     0,     0,    61,    62,     0,
      63,   151,   152,   153,   205,   154,   155,   156,   157,   158,
     159,   160,   161,   162,     0,   163,   164,   165,   142,     0,
     206,   143,   144,   145,   146,   147,   148,   149,     0,     0,
     150,     0,     0,     0,     0,     0,     0,     0,   151,   152,
     153,     0,   154,   155,   156,   157,   158,   159,   160,   161,
     162,     0,   163,   164,   165,   135,   136,   137,   138,     0,
       0,     0,     0,     0,     0,   142,     0,     0,   143,   144,
     145,   146,   147,   148,   149,     0,     0,   150,     0,     0,
       0,     0,     0,     0,     0,   151,   152,   153,     0,   154,
     155,   156,   157,   158,   159,   160,   161,   162,     0,   163,
     164,   165,   142,     0,     0,   143,   144,   145,   146,   147,
     148,   149,     0,     0,   150,     0,     0,     0,     0,     0,
       0,     0,   151,   152,   153,     0,   154,   155,   156,   157,
     158,   159,   160,   161,   162,     0,   163,   164,   165,   141,
     142,     0,   183,   143,   144,   145,   146,   147,   148,   149,
       0,     0,   150,     0,     0,     0,     0,     0,     0,     0,
     151,   152,   153,     0,   154,   155,   156,   157,   158,   159,
     160,   161,   162,     0,   163,   164,   165,   142,   211,   212,
     143,   144,   145,   146,   147,   148,   149,     0,     0,   150,
       0,     0,     0,     0,     0,     0,     0,   151,   152,   153,
       0,   154,   155,   156,   157,   158,   159,   160,   161,   162,
       0,   163,   164,   165,   142,     0,   333,   143,   144,   145,
     146,   147,   148,   149,     0,     0,   150,     0,     0,     0,
       0,     0,     0,     0,   151,   152,   153,     0,   154,   155,
     156,   157,   158,   159,   160,   161,   162,     0,   163,   164,
     165,   142,     0,     0,   143,   144,   145,   146,   147,   148,
     149,     0,     0,   150,     0,     0,     0,     0,     0,     0,
       0,   151,   152,   153,     0,   154,   155,   156,   157,   158,
     159,   160,   161,   162,     0,   163,   164,   165,   142,     0,
       0,   143,   144,   145,   146,   147,   148,   149,     0,     0,
     150,     0,     0,     0,     0,     0,     0,     0,   151,   152,
     153,     0,   154,   155,   156,   157,   158,   159,   160,   161,
     288,     0,   163,   164,   165,    15,    16,    17,    18,     0,
      19,     0,     0,    20,    21,    22,    23,     0,     0,     0,
      24,     0,     0,   143,   144,   145,   146,   147,   148,   149,
       0,     0,   150,     0,     0,     0,    52,    25,     0,    53,
     151,   152,   153,     0,   154,   155,   156,   157,   158,   159,
     160,   161,   162,     0,   163,   164,   165,    -6,    -6,    -6,
      -6,   147,   148,   149,     0,     0,   150,     0,     0,     0,
       0,     0,     0,     0,     0,    -6,    -6,     0,   154,   155,
     156,   157,   158,   159,   160,   161,   162,     0,   163,   164,
     165,   143,   144,   145,   146,   147,   148,   149,     0,     0,
     150,     0,     0,     0,     0,     0,     0,     0,     0,   152,
     153,     0,   154,   155,   156,   157,   158,   159,   160,   161,
     162,     0,   163,   164,   165,    15,    16,    17,    18,     0,
      19,     0,     0,    20,    21,    22,    23,     0,     0,     0,
      24,   147,   148,   149,    15,    16,    17,    18,     0,    19,
       0,     0,    20,    21,    22,    23,   107,    25,   108,    24,
     156,   157,   158,   159,   160,   161,   162,     0,   163,   164,
     165,   147,   148,   149,     0,     0,    25,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   157,   158,   159,   160,   161,   162,     0,   163,   164,
     165
};

static const yytype_int16 yycheck[] =
{
       1,     2,     3,     4,     5,    62,   133,    44,   113,   174,
      41,   200,   101,   200,     6,     7,    37,   215,   216,    50,
     218,   115,   116,    20,    21,    22,    23,    40,    25,    37,
      40,    28,    29,    30,    31,   260,     8,   262,    35,    37,
      41,   266,    61,     0,    61,    73,    22,    57,    64,    50,
      29,    27,    73,    78,    51,    52,    53,    36,    77,    72,
      32,    78,    63,    42,    43,    73,    97,    61,    61,   100,
       8,     9,   166,   298,    61,    73,   113,    40,    24,   268,
      77,   268,    35,    75,    78,    78,   180,    40,   177,    16,
      61,    78,    45,    56,    40,    48,    97,     6,     7,   100,
     265,    22,     8,     9,    75,    11,    59,    60,   165,    61,
      74,    32,    61,   114,   115,   116,   117,   118,    72,    71,
      72,    73,    74,    75,    40,   323,    78,    79,    80,    81,
      82,    72,    73,    74,   135,   136,   137,   138,   169,   215,
     216,    16,   218,   174,   309,    98,    57,   204,    30,    31,
     207,    75,   279,    75,    64,    74,   108,    64,    78,   264,
      75,    56,   163,    32,    61,   166,     8,     9,   169,    11,
      12,    13,    73,   174,   127,    75,    37,    56,   179,   180,
      32,     3,     4,     5,     6,     7,   187,    40,    32,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   164,   339,   192,     6,   194,   120,   274,    40,   198,
     268,   263,   100,   181,   281,   167,   283,   264,   316,   286,
      45,    46,    47,   185,   265,    85,   129,   189,   295,     3,
       4,     5,     6,     7,   197,   327,   276,   187,    45,    46,
      47,   169,    97,    -1,    -1,   312,    -1,    72,    73,    74,
     213,    -1,   215,   216,   265,   218,    -1,    -1,    -1,   248,
      67,    68,    69,    70,    -1,    72,    73,    74,   309,    -1,
      -1,   338,    -1,   340,   285,    18,    19,    20,    21,    22,
      23,   243,    25,    26,    -1,    28,    29,    30,    31,    -1,
      33,    34,    35,    45,    46,    47,    -1,    -1,   309,   261,
      -1,   263,    -1,    -1,   267,    -1,    -1,    -1,    51,    52,
      -1,    54,    55,   275,    57,    58,    -1,    -1,    70,    -1,
      72,    73,    74,    66,    -1,    -1,   288,   289,   290,    -1,
      73,    74,    -1,    76,    -1,   297,    -1,   299,    18,    19,
      20,    21,    22,    23,    -1,    25,    26,    -1,    28,    29,
      30,    31,    -1,    33,    34,    35,    -1,    -1,    20,    21,
      22,    23,    -1,    25,    -1,   327,    28,    29,    30,    31,
      -1,    51,    52,    35,    54,    55,    -1,    -1,    58,    28,
      29,    30,    31,    32,    -1,    -1,    66,    -1,    -1,    -1,
      52,    -1,    -1,    73,    74,    -1,    76,    20,    21,    22,
      23,    -1,    25,    26,    -1,    28,    29,    30,    31,    -1,
      -1,    73,    35,    -1,    -1,    -1,    -1,    45,    46,    47,
      -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,    51,    52,
      53,    54,    55,    -1,    -1,    58,    64,    65,    66,    67,
      68,    69,    70,    66,    72,    73,    74,    -1,    -1,    -1,
      73,    74,    -1,    76,    20,    21,    22,    23,    -1,    25,
      26,    -1,    28,    29,    30,    31,    -1,    20,    -1,    35,
      23,    -1,    25,    26,    -1,    28,    29,    30,    31,    -1,
      -1,    -1,    35,    -1,    -1,    51,    52,    -1,    54,    55,
      -1,    -1,    58,    -1,    -1,    -1,    -1,    -1,    51,    52,
      66,    54,    55,    -1,    -1,    58,    -1,    73,    74,    -1,
      76,    -1,    -1,    66,    -1,    -1,    -1,    -1,    -1,    -1,
      73,    74,    -1,    76,    20,    21,    22,    23,    -1,    25,
      -1,    -1,    28,    29,    30,    31,    -1,    -1,    -1,    35,
      -1,    -1,    -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    51,    52,    -1,    54,    -1,
      -1,    38,    -1,    40,    41,    42,    43,    44,    45,    46,
      47,    -1,    -1,    50,    -1,    -1,    -1,    73,    74,    -1,
      76,    58,    59,    60,    24,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    -1,    72,    73,    74,    38,    -1,
      40,    41,    42,    43,    44,    45,    46,    47,    -1,    -1,
      50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,    59,
      60,    -1,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    -1,    72,    73,    74,    28,    29,    30,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    38,    -1,    -1,    41,    42,
      43,    44,    45,    46,    47,    -1,    -1,    50,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    58,    59,    60,    -1,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    -1,    72,
      73,    74,    38,    -1,    -1,    41,    42,    43,    44,    45,
      46,    47,    -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    58,    59,    60,    -1,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    -1,    72,    73,    74,    37,
      38,    -1,    78,    41,    42,    43,    44,    45,    46,    47,
      -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      58,    59,    60,    -1,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    -1,    72,    73,    74,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    -1,    -1,    50,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,    59,    60,
      -1,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      -1,    72,    73,    74,    38,    -1,    40,    41,    42,    43,
      44,    45,    46,    47,    -1,    -1,    50,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    58,    59,    60,    -1,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    -1,    72,    73,
      74,    38,    -1,    -1,    41,    42,    43,    44,    45,    46,
      47,    -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    58,    59,    60,    -1,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    -1,    72,    73,    74,    38,    -1,
      -1,    41,    42,    43,    44,    45,    46,    47,    -1,    -1,
      50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,    59,
      60,    -1,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    -1,    72,    73,    74,    20,    21,    22,    23,    -1,
      25,    -1,    -1,    28,    29,    30,    31,    -1,    -1,    -1,
      35,    -1,    -1,    41,    42,    43,    44,    45,    46,    47,
      -1,    -1,    50,    -1,    -1,    -1,    51,    52,    -1,    54,
      58,    59,    60,    -1,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    -1,    72,    73,    74,    41,    42,    43,
      44,    45,    46,    47,    -1,    -1,    50,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    59,    60,    -1,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    -1,    72,    73,
      74,    41,    42,    43,    44,    45,    46,    47,    -1,    -1,
      50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    59,
      60,    -1,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    -1,    72,    73,    74,    20,    21,    22,    23,    -1,
      25,    -1,    -1,    28,    29,    30,    31,    -1,    -1,    -1,
      35,    45,    46,    47,    20,    21,    22,    23,    -1,    25,
      -1,    -1,    28,    29,    30,    31,    51,    52,    53,    35,
      64,    65,    66,    67,    68,    69,    70,    -1,    72,    73,
      74,    45,    46,    47,    -1,    -1,    52,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    66,    67,    68,    69,    70,    -1,    72,    73,
      74
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,    40,    80,    82,    83,
      85,    86,    92,    96,   104,    20,    21,    22,    23,    25,
      28,    29,    30,    31,    35,    52,   146,   138,   146,   146,
     146,   146,    82,     0,    83,    64,    97,    40,    56,    84,
      73,    84,    97,    97,    81,    84,    81,   108,   114,    78,
      81,   140,    51,    54,    93,    94,    95,   145,   146,    84,
      84,    73,    74,    76,    98,   130,   131,   145,   146,    81,
      87,    18,    19,    20,    23,    26,    33,    34,    35,    55,
      57,    58,    66,   115,   116,   117,   118,   123,   125,   129,
     131,    81,   109,   142,   143,   144,   145,   146,    74,    40,
      57,    81,    99,    81,   105,   129,   114,    51,    53,    77,
     136,   137,   146,    61,    72,     8,     9,    11,    12,    13,
      88,    89,   101,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,    40,   118,    28,    29,    30,    31,    32,
     124,    37,    38,    41,    42,    43,    44,    45,    46,    47,
      50,    58,    59,    60,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    72,    73,    74,    16,   110,   111,    61,
      78,   144,   146,    75,    81,   141,    94,   100,   101,     8,
       9,   106,   107,    78,    75,    64,   129,    61,    77,    64,
     130,   146,   138,   146,   138,   146,   146,    73,   139,   146,
      74,    89,    21,    40,   113,    24,    40,   122,    81,   126,
     124,    39,    40,   112,   125,   146,   146,   146,   146,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   146,    78,    81,   132,    75,   114,   133,   138,   111,
     143,   142,   101,   146,   138,   146,   107,   129,   137,   129,
      84,    37,    84,    37,    56,    81,    84,    73,    90,    91,
      96,   104,   114,   114,    22,    27,   127,   128,    32,    81,
     119,   122,   126,   122,   126,    61,   122,   126,    70,    53,
      66,   129,   134,   135,    75,    84,    75,    37,    56,    37,
     108,   102,   129,   108,   102,   103,   130,   142,   108,    81,
      75,    91,    22,    32,    32,   114,   129,   128,   120,   121,
     125,   114,   114,   146,   114,   129,   129,    61,    78,   114,
     129,   108,   129,    40,    40,    78,   142,   114,   112,    40,
     122,   135,    78,    32,   114,   125,   114
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    79,    80,    80,    80,    81,    82,    82,    83,    83,
      83,    83,    83,    84,    84,    85,    86,    87,    88,    88,
      89,    89,    89,    90,    90,    91,    91,    92,    93,    93,
      94,    94,    95,    95,    96,    97,    97,    98,    98,    99,
     100,   100,   101,   101,   101,   101,   101,   102,   103,   104,
     105,   106,   106,   107,   107,   107,   108,   108,   109,   110,
     110,   111,   112,   112,   113,   113,   114,   115,   115,   115,
     116,   116,   117,   117,   118,   119,   120,   120,   121,   121,
     122,   122,   123,   123,   124,   124,   124,   124,   124,   124,
     124,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     126,   127,   127,   128,   128,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   130,   130,   131,
     131,   131,   131,   131,   131,   132,   132,   133,   133,   134,
     134,   135,   135,   135,   136,   136,   137,   137,   137,   138,
     138,   138,   139,   139,   140,   140,   141,   141,   142,   142,
     143,   143,   144,   144,   145,   145,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     1,     2,     0,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     4,     5,     2,     1,     2,
       1,     4,     4,     1,     2,     1,     1,     4,     1,     2,
       1,     3,     1,     1,     5,     0,     3,     1,     3,     2,
       1,     2,     4,     4,     4,     4,     4,     2,     2,     5,
       2,     1,     2,     4,     4,     4,     1,     2,     2,     1,
       2,     4,     1,     1,     1,     1,     2,     2,     1,     1,
       3,     1,     1,     2,     4,     2,     2,     1,     3,     1,
       1,     1,     3,     2,     4,     3,     4,     3,     4,     3,
       6,     1,     2,     1,     2,     1,     1,     1,     2,     3,
       2,     1,     2,     4,     2,     1,     2,     5,     7,     5,
       4,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     5,     2,     2,     1,     3,     1,
       1,     2,     3,     3,     3,     1,     3,     1,     2,     1,
       3,     1,     1,     2,     1,     3,     2,     3,     3,     1,
       3,     5,     4,     5,     1,     3,     1,     3,     1,     3,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (&yylloc, picl_driver, YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location, picl_driver); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, struct PiclDriver *picl_driver)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  YYUSE (picl_driver);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, struct PiclDriver *picl_driver)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, picl_driver);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, struct PiclDriver *picl_driver)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       , picl_driver);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, picl_driver); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, struct PiclDriver *picl_driver)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (picl_driver);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (struct PiclDriver *picl_driver)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval, &yylloc, picl_driver);
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 143 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { }
#line 1817 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 3:
#line 144 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { picl_driver->nodes = PiclNodeArray_pop(picl_driver->node_buff_stack); }
#line 1823 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 4:
#line 145 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { picl_driver->nodes = PiclNodeArray_pop(picl_driver->node_buff_stack); }
#line 1829 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 5:
#line 148 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { PiclNodeBuff_new(picl_driver->node_buff_stack); }
#line 1835 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 6:
#line 151 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { PiclNodeBuffStack_push(picl_driver->node_buff_stack, (yyvsp[0].node)); }
#line 1841 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 7:
#line 152 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { PiclNodeBuffStack_push(picl_driver->node_buff_stack, (yyvsp[0].node)); }
#line 1847 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 15:
#line 166 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newFunction((yyvsp[-2].func_head), (yyvsp[0].func_body)); }
#line 1853 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 16:
#line 169 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newClassKind(NodeType_Sequence, (yyvsp[-3].sval), (yyvsp[-2].nodes), (yyvsp[0].nodes)); }
#line 1859 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 17:
#line 172 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.nodes) = PiclNodeArray_pop(picl_driver->node_buff_stack); }
#line 1865 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 18:
#line 175 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { PiclNodeBuffStack_push(picl_driver->node_buff_stack, (yyvsp[0].node)); }
#line 1871 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 19:
#line 176 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { PiclNodeBuffStack_push(picl_driver->node_buff_stack, (yyvsp[0].node)); }
#line 1877 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 21:
#line 180 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newCatch((yyvsp[-2].func_head), (yyvsp[0].func_body)); }
#line 1883 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 22:
#line 181 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 1889 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 23:
#line 184 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { PiclNodeBuffStack_push(picl_driver->node_buff_stack, (yyvsp[0].node)); }
#line 1895 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 24:
#line 185 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { PiclNodeBuffStack_push(picl_driver->node_buff_stack, (yyvsp[0].node)); }
#line 1901 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 27:
#line 192 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newNaming(NodeType_Op_Dot, (yyvsp[-2].sval), (yyvsp[0].node)); }
#line 1907 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 28:
#line 195 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1913 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 29:
#line 196 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 1919 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 30:
#line 199 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1925 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 31:
#line 200 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newBinary(NodeType_Op_Def_Or, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1931 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 32:
#line 203 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newIdent(NodeType_Val_Ident, (yyvsp[0].sval)); }
#line 1937 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 33:
#line 204 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1943 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 34:
#line 207 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newClassKind(NodeType_Class, (yyvsp[-3].sval), (yyvsp[-2].nodes), (yyvsp[0].nodes)); }
#line 1949 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 35:
#line 210 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.nodes) = NULL; }
#line 1955 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 36:
#line 211 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.nodes) = PiclNodeArray_pop(picl_driver->node_buff_stack); }
#line 1961 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 37:
#line 214 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { PiclNodeBuffStack_push(picl_driver->node_buff_stack, (yyvsp[0].node)); }
#line 1967 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 38:
#line 215 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { PiclNodeBuffStack_push(picl_driver->node_buff_stack, (yyvsp[0].node)); }
#line 1973 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 39:
#line 218 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.nodes) = PiclNodeArray_pop(picl_driver->node_buff_stack); }
#line 1979 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 40:
#line 221 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { PiclNodeBuffStack_push(picl_driver->node_buff_stack, (yyvsp[0].node)); }
#line 1985 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 41:
#line 222 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { PiclNodeBuffStack_push(picl_driver->node_buff_stack, (yyvsp[0].node)); }
#line 1991 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 42:
#line 225 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newField(MemberScope_Public, (yyvsp[-2].sval), (yyvsp[0].node)); }
#line 1997 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 43:
#line 226 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newField(MemberScope_Private, (yyvsp[-2].sval), (yyvsp[0].node)); }
#line 2003 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 44:
#line 227 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newMethod(MemberScope_Public, (yyvsp[-2].func_head), (yyvsp[0].func_body)); }
#line 2009 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 45:
#line 228 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newMethod(MemberScope_Private, (yyvsp[-2].func_head), (yyvsp[0].func_body)); }
#line 2015 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 46:
#line 229 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newAlias((yyvsp[-2].sval), (yyvsp[0].node)); }
#line 2021 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 49:
#line 240 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newClassKind(NodeType_Behavior, (yyvsp[-3].sval), (yyvsp[-2].nodes), (yyvsp[0].nodes)); }
#line 2027 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 50:
#line 243 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.nodes) = PiclNodeArray_pop(picl_driver->node_buff_stack); }
#line 2033 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 51:
#line 246 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { PiclNodeBuffStack_push(picl_driver->node_buff_stack, (yyvsp[0].node)); }
#line 2039 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 52:
#line 247 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { PiclNodeBuffStack_push(picl_driver->node_buff_stack, (yyvsp[0].node)); }
#line 2045 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 53:
#line 250 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newField(MemberScope_Public, (yyvsp[-2].sval), (yyvsp[0].node)); }
#line 2051 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 54:
#line 251 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newField(MemberScope_Private, (yyvsp[-2].sval), (yyvsp[0].node)); }
#line 2057 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 55:
#line 252 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newMethod(MemberScope_Private, (yyvsp[-2].func_head), (yyvsp[0].func_body)); }
#line 2063 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 56:
#line 255 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.func_body) = PiclNode_FuncBody_new((yyvsp[0].nodes), NULL); }
#line 2069 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 57:
#line 256 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.func_body) = PiclNode_FuncBody_new((yyvsp[-1].nodes), (yyvsp[0].nodes)); }
#line 2075 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 58:
#line 259 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.nodes) = PiclNodeArray_pop(picl_driver->node_buff_stack); }
#line 2081 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 59:
#line 262 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { PiclNodeBuffStack_push(picl_driver->node_buff_stack, (yyvsp[0].node)); }
#line 2087 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 60:
#line 263 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { PiclNodeBuffStack_push(picl_driver->node_buff_stack, (yyvsp[0].node)); }
#line 2093 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 61:
#line 266 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newLet((yyvsp[-2].func_head), (yyvsp[0].nodes)); }
#line 2099 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 66:
#line 277 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.nodes) = PiclNodeArray_pop(picl_driver->node_buff_stack); }
#line 2105 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 70:
#line 285 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { PiclNodeBuffStack_push(picl_driver->node_buff_stack, (yyvsp[0].node)); }
#line 2111 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 71:
#line 286 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { PiclNodeBuffStack_push(picl_driver->node_buff_stack, (yyvsp[0].node)); }
#line 2117 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 73:
#line 290 "src/parser/picl-parser.y" /* yacc.c:1646  */
    {  }
#line 2123 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 74:
#line 293 "src/parser/picl-parser.y" /* yacc.c:1646  */
    {  }
#line 2129 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 75:
#line 296 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.nodes) = PiclNodeArray_pop(picl_driver->node_buff_stack); }
#line 2135 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 78:
#line 303 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { PiclNodeBuffStack_push(picl_driver->node_buff_stack, (yyvsp[0].node)); }
#line 2141 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 79:
#line 304 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { PiclNodeBuffStack_push(picl_driver->node_buff_stack, (yyvsp[0].node)); }
#line 2147 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 82:
#line 314 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_setListStmtCond((yyvsp[0].node), (yyvsp[-1].node)); }
#line 2153 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 83:
#line 315 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_setListStmtCond((yyvsp[0].node), (yyvsp[-1].node)); }
#line 2159 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 84:
#line 318 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node)= PiclNode_newOneArgListStmt(NodeType_ListEach, (yyvsp[-2].sval), (yyvsp[0].nodes)); }
#line 2165 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 85:
#line 319 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node)= PiclNode_newOneArgListStmt(NodeType_ListEachWhen, (yyvsp[-1].sval), (yyvsp[0].nodes)); }
#line 2171 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 86:
#line 320 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node)= PiclNode_newOneArgListStmt(NodeType_ListMap, (yyvsp[-2].sval), (yyvsp[0].nodes)); }
#line 2177 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 87:
#line 321 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node)= PiclNode_newOneArgListStmt(NodeType_ListMapWhen, (yyvsp[-1].sval), (yyvsp[0].nodes)); }
#line 2183 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 88:
#line 322 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node)= PiclNode_newOneArgListStmt(NodeType_ListFilter, (yyvsp[-2].sval), (yyvsp[0].nodes)); }
#line 2189 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 89:
#line 323 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node)= PiclNode_newOneArgListStmt(NodeType_ListFilterWhen, (yyvsp[-1].sval), (yyvsp[0].nodes)); }
#line 2195 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 90:
#line 324 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node)= PiclNode_newTwoArgListStmt(NodeType_ListReduce, (yyvsp[-4].sval), (yyvsp[-2].sval), (yyvsp[0].nodes)); }
#line 2201 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 91:
#line 327 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2207 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 92:
#line 328 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newUnary(NodeType_Stmt_Return_Var, (yyvsp[0].node)); }
#line 2213 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 93:
#line 329 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newAtom(NodeType_Stmt_Return); }
#line 2219 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 94:
#line 330 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newUnary(NodeType_Stmt_Throw_Var, (yyvsp[0].node)); }
#line 2225 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 95:
#line 331 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newAtom(NodeType_Stmt_Throw); }
#line 2231 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 96:
#line 332 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newAtom(NodeType_Stmt_Break); }
#line 2237 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 97:
#line 333 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newAtom(NodeType_Stmt_Continue); }
#line 2243 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 98:
#line 334 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newUnary(NodeType_Stmt_Echo_Var, (yyvsp[0].node)); }
#line 2249 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 99:
#line 335 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newBinary(NodeType_Op_Assign, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2255 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 100:
#line 338 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.nodes) = PiclNodeArray_pop(picl_driver->node_buff_stack); }
#line 2261 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 101:
#line 341 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { PiclNodeBuffStack_push(picl_driver->node_buff_stack, (yyvsp[0].node)); }
#line 2267 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 102:
#line 342 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { PiclNodeBuffStack_push(picl_driver->node_buff_stack, (yyvsp[0].node)); }
#line 2273 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 103:
#line 345 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node)= PiclNode_newCondUnary(NodeType_When, (yyvsp[-2].node), (yyvsp[0].nodes)); }
#line 2279 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 104:
#line 346 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node)= PiclNode_newNodes(NodeType_WhenElse, (yyvsp[0].nodes)); }
#line 2285 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 105:
#line 349 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2291 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 106:
#line 351 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 2297 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 107:
#line 352 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node)= PiclNode_newCondUnary(NodeType_If, (yyvsp[-3].node), (yyvsp[-1].nodes)); }
#line 2303 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 108:
#line 353 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node)= PiclNode_newCondBinary(NodeType_IfElse, (yyvsp[-5].node), (yyvsp[-3].nodes), (yyvsp[-1].nodes)); }
#line 2309 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 109:
#line 354 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node)= PiclNode_newCondUnary(NodeType_While, (yyvsp[-3].node), (yyvsp[-1].nodes)); }
#line 2315 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 110:
#line 355 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node)= PiclNode_newCondUnary(NodeType_Case, (yyvsp[-2].node), (yyvsp[-1].nodes)); }
#line 2321 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 111:
#line 357 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newNaming(NodeType_Op_Dot, (yyvsp[0].sval), (yyvsp[-2].node)); }
#line 2327 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 112:
#line 359 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newCallFunc(NodeType_CallFuncArg, (yyvsp[-2].node), (yyvsp[0].nodes)); }
#line 2333 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 113:
#line 360 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newCallFunc(NodeType_CallFuncStmt, (yyvsp[-2].node), (yyvsp[0].nodes)); }
#line 2339 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 114:
#line 362 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newBinary(NodeType_Op_Add, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2345 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 115:
#line 363 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newBinary(NodeType_Op_Sub, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2351 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 116:
#line 364 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newBinary(NodeType_Op_Mul, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2357 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 117:
#line 365 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newBinary(NodeType_Op_Div, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2363 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 118:
#line 366 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newBinary(NodeType_Op_Mod, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2369 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 119:
#line 368 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newBinary(NodeType_Op_Mod, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2375 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 120:
#line 369 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newBinary(NodeType_Op_Mod, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2381 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 121:
#line 370 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newBinary(NodeType_Op_Mod, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2387 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 122:
#line 372 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newBinary(NodeType_Op_Mod, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2393 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 123:
#line 373 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newBinary(NodeType_Op_Mod, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2399 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 124:
#line 375 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newBinary(NodeType_Op_Equal,     (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2405 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 125:
#line 376 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newBinary(NodeType_Op_NotEqual, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2411 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 126:
#line 377 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newBinary(NodeType_Op_GtEqual,  (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2417 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 127:
#line 378 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newBinary(NodeType_Op_LtEqual,  (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2423 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 128:
#line 379 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newBinary(NodeType_Op_Gt,        (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2429 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 129:
#line 380 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newBinary(NodeType_Op_Lt,        (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2435 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 130:
#line 382 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newBinary(NodeType_Op_StrJoin,  (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2441 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 131:
#line 384 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newBinary(NodeType_Op_Compare,  (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2447 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 132:
#line 386 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newBinary(NodeType_Op_Colon,   (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2453 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 133:
#line 387 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newBinary(NodeType_Op_Colon,  (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2459 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 134:
#line 389 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newBinary(NodeType_Op_Method, (yyvsp[-4].node), (yyvsp[-2].node)); }
#line 2465 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 135:
#line 390 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newUnary(NodeType_Op_Minus,    (yyvsp[0].node)); }
#line 2471 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 136:
#line 391 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newUnary(NodeType_Op_Minus,    (yyvsp[0].node)); }
#line 2477 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 137:
#line 394 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2483 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 138:
#line 395 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newNaming(NodeType_Op_Dot, (yyvsp[0].sval), (yyvsp[-2].node)); }
#line 2489 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 139:
#line 398 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2495 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 140:
#line 399 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newIdent(NodeType_Val_Ident, (yyvsp[0].sval)); }
#line 2501 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 141:
#line 400 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newAtom(NodeType_Val_List); }
#line 2507 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 142:
#line 401 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newUnary(NodeType_Val_Dict_Var, (yyvsp[-1].node)); }
#line 2513 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 143:
#line 402 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 2519 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 144:
#line 403 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { PiclNode_newNodes(NodeType_Stmts, (yyvsp[-1].nodes)); }
#line 2525 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 145:
#line 406 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.nodes) = NULL; }
#line 2531 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 146:
#line 407 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.nodes) = PiclNodeArray_pop(picl_driver->node_buff_stack); }
#line 2537 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 147:
#line 410 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.nodes) = NULL; }
#line 2543 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 148:
#line 411 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.nodes) = (yyvsp[-1].nodes); }
#line 2549 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 149:
#line 414 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { PiclNodeBuffStack_push(picl_driver->node_buff_stack, (yyvsp[0].node)); }
#line 2555 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 150:
#line 415 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { PiclNodeBuffStack_push(picl_driver->node_buff_stack, (yyvsp[0].node)); }
#line 2561 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 151:
#line 418 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2567 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 152:
#line 419 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newAtom(NodeType_Stmt_Return); }
#line 2573 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 153:
#line 420 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newNaming(NodeType_Dict_Arg, (yyvsp[-1].sval), (yyvsp[0].node)); }
#line 2579 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 154:
#line 423 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { PiclNodeBuffStack_push(picl_driver->node_buff_stack, (yyvsp[0].node)); }
#line 2585 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 155:
#line 424 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { PiclNodeBuffStack_push(picl_driver->node_buff_stack, (yyvsp[0].node)); }
#line 2591 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 156:
#line 427 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newNaming(NodeType_Val_Var_Dict, (yyvsp[-1].sval), (yyvsp[0].node)); }
#line 2597 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 157:
#line 428 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newNaming(NodeType_Val_Var_Dict, (yyvsp[-2].sval), (yyvsp[0].node)); }
#line 2603 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 158:
#line 429 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newNaming(NodeType_Val_Str_Dict, (yyvsp[-2].sval), (yyvsp[0].node)); }
#line 2609 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 159:
#line 433 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.func_head) = PiclNode_FuncHead_new((yyvsp[0].sval), NULL, NULL); }
#line 2615 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 160:
#line 434 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.func_head) = PiclNode_FuncHead_new((yyvsp[-2].sval), (yyvsp[0].nodes), NULL); }
#line 2621 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 161:
#line 435 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.func_head) = PiclNode_FuncHead_new((yyvsp[-4].sval), (yyvsp[-2].nodes), (yyvsp[0].nodes)); }
#line 2627 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 162:
#line 438 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.func_head) = PiclNode_FuncHead_new(NULL, PiclNodeArray_pop(picl_driver->node_buff_stack), NULL); }
#line 2633 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 163:
#line 439 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.func_head) = PiclNode_FuncHead_new((yyvsp[-4].sval), PiclNodeArray_pop(picl_driver->node_buff_stack), NULL); }
#line 2639 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 164:
#line 442 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.nodes) = NULL; }
#line 2645 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 165:
#line 443 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.nodes) = PiclNodeArray_pop(picl_driver->node_buff_stack); }
#line 2651 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 166:
#line 446 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.nodes) = NULL; }
#line 2657 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 167:
#line 447 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.nodes) = PiclNodeArray_pop(picl_driver->node_buff_stack); }
#line 2663 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 168:
#line 450 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { PiclNodeBuffStack_push(picl_driver->node_buff_stack, (yyvsp[0].node)); }
#line 2669 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 169:
#line 451 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { PiclNodeBuffStack_push(picl_driver->node_buff_stack, (yyvsp[0].node)); }
#line 2675 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 170:
#line 454 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2681 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 171:
#line 455 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newNaming(NodeType_Decl_Type_Arg, (yyvsp[-1].sval), (yyvsp[0].node)); }
#line 2687 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 172:
#line 458 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newIdent(NodeType_Decl_ArgIdent, (yyvsp[0].sval)); }
#line 2693 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 173:
#line 459 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 2699 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 174:
#line 462 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newInt((yyvsp[0].ival)); }
#line 2705 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;

  case 175:
#line 463 "src/parser/picl-parser.y" /* yacc.c:1646  */
    { (yyval.node) = PiclNode_newStr((yyvsp[0].sval)); }
#line 2711 "src/parser/picl-parser.c" /* yacc.c:1646  */
    break;


#line 2715 "src/parser/picl-parser.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (&yylloc, picl_driver, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (&yylloc, picl_driver, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, picl_driver);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp, picl_driver);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, picl_driver, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, picl_driver);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp, picl_driver);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 478 "src/parser/picl-parser.y" /* yacc.c:1906  */

