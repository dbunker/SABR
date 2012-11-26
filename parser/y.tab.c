/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 26 "parser/tbl.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../core/arch.h"

int yylex(void);


/* Line 268 of yacc.c  */
#line 81 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     VARIABLE = 258,
     SYMBOLS = 259,
     BOARD = 260,
     START = 261,
     END = 262,
     OBJECT = 263,
     DESOBJECT = 264,
     TRANSFORM = 265,
     TRANSFORMSIM = 266,
     REQUIRE = 267,
     OPTION = 268,
     ARROW = 269,
     SEMI = 270,
     CHARVAR = 271,
     BOARDVAR = 272,
     SPACEVAR = 273,
     MANYVAR = 274,
     MANYBRACK = 275,
     ELABTEMP = 276,
     ELABQUEST = 277,
     ELABVAR = 278,
     ELABNEG = 279,
     ELABPAREN = 280,
     ELABCOL = 281
   };
#endif
/* Tokens.  */
#define VARIABLE 258
#define SYMBOLS 259
#define BOARD 260
#define START 261
#define END 262
#define OBJECT 263
#define DESOBJECT 264
#define TRANSFORM 265
#define TRANSFORMSIM 266
#define REQUIRE 267
#define OPTION 268
#define ARROW 269
#define SEMI 270
#define CHARVAR 271
#define BOARDVAR 272
#define SPACEVAR 273
#define MANYVAR 274
#define MANYBRACK 275
#define ELABTEMP 276
#define ELABQUEST 277
#define ELABVAR 278
#define ELABNEG 279
#define ELABPAREN 280
#define ELABCOL 281




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 35 "parser/tbl.y"

    int val;
    treeNode *node;



/* Line 293 of yacc.c  */
#line 176 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 188 "y.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   154

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  66
/* YYNRULES -- Number of states.  */
#define YYNSTATES  151

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   281

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    35,     2,     2,     2,     2,     2,     2,
      27,    29,     2,     2,    36,     2,    33,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    28,    32,
       2,     2,     2,    34,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    30,     2,    31,     2,     2,     2,     2,
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
      25,    26
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,    11,    15,    18,    21,    24,    27,
      30,    31,    37,    38,    40,    43,    48,    54,    59,    64,
      69,    80,    89,    91,    93,    95,    97,   103,   111,   117,
     126,   133,   142,   149,   152,   156,   159,   161,   164,   168,
     171,   173,   176,   178,   182,   185,   189,   192,   194,   196,
     199,   203,   206,   208,   210,   213,   217,   220,   222,   224,
     226,   229,   233,   239,   241,   244,   248
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      38,     0,    -1,    39,    -1,    42,    44,    45,    46,    40,
      -1,    42,    44,    40,    -1,    50,    40,    -1,    51,    40,
      -1,    47,    40,    -1,    52,    40,    -1,    53,    40,    -1,
      -1,    27,     3,    28,     3,    29,    -1,    -1,    43,    -1,
      43,    42,    -1,     4,    30,    57,    31,    -1,     4,     3,
      30,    57,    31,    -1,     5,    30,    55,    31,    -1,     6,
      30,    61,    31,    -1,     7,    30,    61,    31,    -1,    48,
      41,     3,    28,    49,    30,    61,    14,    61,    31,    -1,
      48,    41,    49,    30,    61,    14,    61,    31,    -1,    10,
      -1,    11,    -1,     3,    -1,     5,    -1,     8,     3,    30,
      54,    31,    -1,     9,     3,    28,     3,    30,    59,    31,
      -1,     9,     3,    30,    59,    31,    -1,    12,    41,     3,
      28,    49,    30,    61,    31,    -1,    12,    41,    49,    30,
      61,    31,    -1,    13,    41,     3,    28,    49,    30,    61,
      31,    -1,    13,    41,    49,    30,    61,    31,    -1,    56,
      54,    -1,    56,    32,    54,    -1,    56,    32,    -1,    56,
      -1,    56,    55,    -1,    56,    32,    55,    -1,    56,    32,
      -1,    56,    -1,    33,    55,    -1,     3,    -1,     3,    28,
       3,    -1,    58,    57,    -1,    58,    32,    57,    -1,    58,
      32,    -1,    58,    -1,     3,    -1,    60,    59,    -1,    60,
      32,    59,    -1,    60,    32,    -1,    60,    -1,     3,    -1,
      62,    61,    -1,    62,    32,    61,    -1,    62,    32,    -1,
      62,    -1,     3,    -1,    34,    -1,    35,     3,    -1,    27,
      63,    29,    -1,     3,    28,    27,    63,    29,    -1,     3,
      -1,    35,     3,    -1,     3,    36,    63,    -1,    35,     3,
      36,    63,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    74,    74,    78,    79,    83,    84,    85,    86,    87,
      88,    92,    93,    97,    98,   102,   103,   107,   111,   115,
     119,   122,   127,   128,   132,   133,   137,   141,   144,   149,
     152,   157,   160,   165,   166,   167,   168,   172,   173,   174,
     175,   176,   180,   181,   185,   186,   187,   188,   192,   196,
     197,   198,   199,   203,   207,   208,   209,   210,   214,   215,
     216,   217,   218,   222,   223,   224,   225
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "VARIABLE", "SYMBOLS", "BOARD", "START",
  "END", "OBJECT", "DESOBJECT", "TRANSFORM", "TRANSFORMSIM", "REQUIRE",
  "OPTION", "ARROW", "SEMI", "CHARVAR", "BOARDVAR", "SPACEVAR", "MANYVAR",
  "MANYBRACK", "ELABTEMP", "ELABQUEST", "ELABVAR", "ELABNEG", "ELABPAREN",
  "ELABCOL", "'('", "':'", "')'", "'{'", "'}'", "';'", "'.'", "'?'", "'!'",
  "','", "$accept", "root", "statements", "choices", "setstages",
  "symbols", "symlist", "board", "start", "end", "transform", "transtype",
  "anyobject", "object", "desobject", "require", "option", "objset",
  "boardset", "boardvar", "charset", "charvar", "manyset", "manyvar",
  "elabset", "elabvar", "elabcomma", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,    40,    58,    41,
     123,   125,    59,    46,    63,    33,    44
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    37,    38,    39,    39,    40,    40,    40,    40,    40,
      40,    41,    41,    42,    42,    43,    43,    44,    45,    46,
      47,    47,    48,    48,    49,    49,    50,    51,    51,    52,
      52,    53,    53,    54,    54,    54,    54,    55,    55,    55,
      55,    55,    56,    56,    57,    57,    57,    57,    58,    59,
      59,    59,    59,    60,    61,    61,    61,    61,    62,    62,
      62,    62,    62,    63,    63,    63,    63
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     5,     3,     2,     2,     2,     2,     2,
       0,     5,     0,     1,     2,     4,     5,     4,     4,     4,
      10,     8,     1,     1,     1,     1,     5,     7,     5,     8,
       6,     8,     6,     2,     3,     2,     1,     2,     3,     2,
       1,     2,     1,     3,     2,     3,     2,     1,     1,     2,
       3,     2,     1,     1,     2,     3,     2,     1,     1,     1,
       2,     3,     5,     1,     2,     3,     4
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     0,    13,     0,     0,     1,     0,
      10,    14,     0,    48,     0,    47,     0,     0,     0,     0,
      22,    23,    12,    12,     4,     0,    10,    12,    10,    10,
      10,    10,     0,    15,    46,    44,    42,     0,     0,    40,
       0,     0,     0,     0,     0,     0,     0,    10,     7,     0,
       5,     6,     8,     9,    16,    45,     0,    41,    17,    39,
      37,    58,     0,    59,     0,     0,    57,     0,     0,     0,
       0,    24,    25,     0,    24,     0,     0,     3,    24,     0,
      43,    38,     0,    63,     0,     0,    60,    18,    56,    54,
       0,    36,     0,    53,     0,    52,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    64,    61,    55,    26,
      35,    33,     0,    28,    51,    49,     0,    24,     0,     0,
       0,     0,    19,     0,     0,     0,    65,     0,    34,     0,
      50,    11,     0,    30,     0,    32,     0,     0,    62,    66,
      27,     0,     0,     0,     0,    29,    31,     0,    21,     0,
      20
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,    24,    44,     4,     5,    10,    25,    47,
      26,    27,    73,    28,    29,    30,    31,    90,    38,    39,
      14,    15,    94,    95,    65,    66,    85
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -90
static const yytype_int8 yypact[] =
{
      20,     0,    27,   -90,    46,    20,   -16,    49,   -90,    39,
      76,   -90,    49,   -90,    43,    12,    10,    47,    75,    80,
     -90,   -90,    72,    72,   -90,    90,    82,    72,    82,    82,
      82,    82,    69,   -90,    49,   -90,    73,    10,    71,     9,
       4,    74,   -19,   100,    16,    62,    77,    82,   -90,    70,
     -90,   -90,   -90,   -90,   -90,   -90,   102,   -90,   -90,    10,
     -90,    78,     5,   -90,   105,    79,     1,   106,   108,   109,
      85,    86,   -90,    87,    88,    89,     4,   -90,    92,    91,
     -90,   -90,    95,    94,   112,    96,   -90,   -90,     4,   -90,
      97,    14,    99,   -90,   101,    15,   115,    93,     4,    93,
       4,   103,    93,     4,     5,     5,   104,   -90,   -90,   -90,
     106,   -90,   109,   -90,   109,   -90,    98,   -90,   107,   110,
     113,   111,   -90,   114,   117,   116,   -90,     5,   -90,   118,
     -90,   -90,     4,   -90,     4,   -90,     4,     4,   -90,   -90,
     -90,   119,   120,   121,   122,   -90,   -90,     4,   -90,   123,
     -90
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -90,   -90,   -90,    33,    -7,   128,   -90,   -90,   -90,   -90,
     -90,   -90,   -44,   -90,   -90,   -90,   -90,   -62,    17,   -65,
      45,   -90,   -89,   -90,   -66,   -90,   -55
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      89,    75,    91,     6,    61,    79,   115,    61,    83,    68,
     101,    69,    36,    36,    12,    13,    45,    36,    93,    71,
      49,    72,   108,   129,     1,   130,    91,     8,    62,   111,
       7,    62,   119,    88,   121,    63,    64,   124,    63,    64,
      84,    59,    37,    37,    34,    91,   110,   114,   128,   125,
     126,     9,    13,   118,    57,   120,    60,    32,   123,    48,
      35,    50,    51,    52,    53,    74,   141,    72,   142,    16,
     143,   144,   139,    78,    33,    72,    81,    40,    41,    55,
      77,   149,    17,    42,    18,    19,    20,    21,    22,    23,
      18,    19,    20,    21,    22,    23,   117,    46,    72,    43,
      54,    56,    58,    70,    67,    80,    82,    76,    86,    36,
      87,    92,    93,    96,    97,   106,    99,    98,   116,   100,
     102,   103,   104,     0,     0,   107,     0,   131,   109,   112,
     105,   137,   113,    11,   122,   147,     0,   132,     0,     0,
     127,   133,   135,   134,   136,   138,     0,     0,     0,   140,
     145,   146,     0,   148,   150
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-90))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      66,    45,    67,     3,     3,    49,    95,     3,     3,    28,
      76,    30,     3,     3,    30,     3,    23,     3,     3,     3,
      27,     5,    88,   112,     4,   114,    91,     0,    27,    91,
      30,    27,    98,    32,   100,    34,    35,   103,    34,    35,
      35,    32,    33,    33,    32,   110,    32,    32,   110,   104,
     105,     5,     3,    97,    37,    99,    39,    12,   102,    26,
      15,    28,    29,    30,    31,     3,   132,     5,   134,    30,
     136,   137,   127,     3,    31,     5,    59,    30,     3,    34,
      47,   147,     6,     3,     8,     9,    10,    11,    12,    13,
       8,     9,    10,    11,    12,    13,     3,     7,     5,    27,
      31,    28,    31,     3,    30,     3,    28,    30,     3,     3,
      31,     3,     3,    28,    28,     3,    28,    30,     3,    30,
      28,    30,    27,    -1,    -1,    29,    -1,    29,    31,    30,
      36,    14,    31,     5,    31,    14,    -1,    30,    -1,    -1,
      36,    31,    31,    30,    30,    29,    -1,    -1,    -1,    31,
      31,    31,    -1,    31,    31
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,    38,    39,    42,    43,     3,    30,     0,     5,
      44,    42,    30,     3,    57,    58,    30,     6,     8,     9,
      10,    11,    12,    13,    40,    45,    47,    48,    50,    51,
      52,    53,    57,    31,    32,    57,     3,    33,    55,    56,
      30,     3,     3,    27,    41,    41,     7,    46,    40,    41,
      40,    40,    40,    40,    31,    57,    28,    55,    31,    32,
      55,     3,    27,    34,    35,    61,    62,    30,    28,    30,
       3,     3,     5,    49,     3,    49,    30,    40,     3,    49,
       3,    55,    28,     3,    35,    63,     3,    31,    32,    61,
      54,    56,     3,     3,    59,    60,    28,    28,    30,    28,
      30,    61,    28,    30,    27,    36,     3,    29,    61,    31,
      32,    54,    30,    31,    32,    59,     3,     3,    49,    61,
      49,    61,    31,    49,    61,    63,    63,    36,    54,    59,
      59,    29,    30,    31,    30,    31,    30,    14,    29,    63,
      31,    61,    61,    61,    61,    31,    31,    14,    31,    61,
      31
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
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

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

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

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

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
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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
      yychar = YYLEX;
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
  *++yyvsp = yylval;

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
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1806 of yacc.c  */
#line 74 "parser/tbl.y"
    { if(endFile) execute((yyvsp[(1) - (1)].node)); }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 78 "parser/tbl.y"
    { (yyval.node) = statementNodes((yyvsp[(1) - (5)].node),(yyvsp[(2) - (5)].node),(yyvsp[(3) - (5)].node),(yyvsp[(4) - (5)].node),(yyvsp[(5) - (5)].node)); }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 79 "parser/tbl.y"
    { (yyval.node) = statementNodes((yyvsp[(1) - (3)].node),(yyvsp[(2) - (3)].node),NULL,NULL,(yyvsp[(3) - (3)].node)); }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 83 "parser/tbl.y"
    { (yyval.node) = choiceNode(OBJECT,(yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node)); }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 84 "parser/tbl.y"
    { (yyval.node) = choiceNode(DESOBJECT,(yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node)); }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 85 "parser/tbl.y"
    { (yyval.node) = choiceNode(TRANSFORM,(yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node)); }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 86 "parser/tbl.y"
    { (yyval.node) = choiceNode(REQUIRE,(yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node)); }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 87 "parser/tbl.y"
    { (yyval.node) = choiceNode(OPTION,(yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node)); }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 88 "parser/tbl.y"
    { (yyval.node) = NULL; }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 92 "parser/tbl.y"
    { (yyval.node) = setStages((yyvsp[(2) - (5)].val),(yyvsp[(4) - (5)].val)); }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 93 "parser/tbl.y"
    { (yyval.node) = NULL; }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 97 "parser/tbl.y"
    { (yyval.node) = symNode((yyvsp[(1) - (1)].node),NULL); }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 98 "parser/tbl.y"
    { (yyval.node) = symNode((yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node)); }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 102 "parser/tbl.y"
    { (yyval.node) = nameNode(SYMBOLS,NULL,0,0,(yyvsp[(3) - (4)].node)); }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 103 "parser/tbl.y"
    { (yyval.node) = nameNode(SYMBOLS,NULL,(yyvsp[(2) - (5)].val),0,(yyvsp[(4) - (5)].node)); }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 107 "parser/tbl.y"
    { (yyval.node) = storeNode(BOARD,(yyvsp[(3) - (4)].node)); }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 111 "parser/tbl.y"
    { (yyval.node) = nameNode(START,NULL,0,0,(yyvsp[(3) - (4)].node)); }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 115 "parser/tbl.y"
    { (yyval.node) = nameNode(END,NULL,0,0,(yyvsp[(3) - (4)].node)); }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 120 "parser/tbl.y"
    { (yyval.node) = transNode((yyvsp[(1) - (10)].val),(yyvsp[(2) - (10)].node),(yyvsp[(3) - (10)].val),(yyvsp[(5) - (10)].val),(yyvsp[(7) - (10)].node),(yyvsp[(9) - (10)].node)); }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 123 "parser/tbl.y"
    { (yyval.node) = transNode((yyvsp[(1) - (8)].val),(yyvsp[(2) - (8)].node),0,(yyvsp[(3) - (8)].val),(yyvsp[(5) - (8)].node),(yyvsp[(7) - (8)].node)); }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 127 "parser/tbl.y"
    { (yyval.val) = TRANSFORM; }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 128 "parser/tbl.y"
    { (yyval.val) = TRANSFORMSIM; }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 132 "parser/tbl.y"
    { (yyval.val) = (yyvsp[(1) - (1)].val); }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 133 "parser/tbl.y"
    { (yyval.val) = addSymbol("Board"); }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 137 "parser/tbl.y"
    { (yyval.node) = nameNode(OBJECT,NULL,(yyvsp[(2) - (5)].val),(yyvsp[(2) - (5)].val),(yyvsp[(4) - (5)].node)); }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 142 "parser/tbl.y"
    { (yyval.node) = nameNode(DESOBJECT,NULL,(yyvsp[(2) - (7)].val),(yyvsp[(4) - (7)].val),(yyvsp[(6) - (7)].node)); }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 145 "parser/tbl.y"
    { (yyval.node) = nameNode(DESOBJECT,NULL,0,(yyvsp[(2) - (5)].val),(yyvsp[(4) - (5)].node)); }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 150 "parser/tbl.y"
    { (yyval.node) = nameNode(REQUIRE,(yyvsp[(2) - (8)].node),(yyvsp[(3) - (8)].val),(yyvsp[(5) - (8)].val),(yyvsp[(7) - (8)].node)); }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 153 "parser/tbl.y"
    { (yyval.node) = nameNode(REQUIRE,(yyvsp[(2) - (6)].node),0,(yyvsp[(3) - (6)].val),(yyvsp[(5) - (6)].node)); }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 158 "parser/tbl.y"
    { (yyval.node) = nameNode(OPTION,(yyvsp[(2) - (8)].node),(yyvsp[(3) - (8)].val),(yyvsp[(5) - (8)].val),(yyvsp[(7) - (8)].node)); }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 161 "parser/tbl.y"
    { (yyval.node) = nameNode(OPTION,(yyvsp[(2) - (6)].node),0,(yyvsp[(3) - (6)].val),(yyvsp[(5) - (6)].node)); }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 165 "parser/tbl.y"
    { (yyval.node) = setNode(0,(yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node)); }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 166 "parser/tbl.y"
    { (yyval.node) = setNode(SEMI,(yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node)); }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 167 "parser/tbl.y"
    { (yyval.node) = setNode(0,(yyvsp[(1) - (2)].node),NULL); }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 168 "parser/tbl.y"
    { (yyval.node) = setNode(0,(yyvsp[(1) - (1)].node),NULL); }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 172 "parser/tbl.y"
    { (yyval.node) = setNode(0,(yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node)); }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 173 "parser/tbl.y"
    { (yyval.node) = setNode(SEMI,(yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node)); }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 174 "parser/tbl.y"
    { (yyval.node) = setNode(0,(yyvsp[(1) - (2)].node),NULL); }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 175 "parser/tbl.y"
    { (yyval.node) = setNode(0,(yyvsp[(1) - (1)].node),NULL); }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 176 "parser/tbl.y"
    { (yyval.node) = setNode(SPACEVAR,NULL,(yyvsp[(2) - (2)].node)); }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 180 "parser/tbl.y"
    { (yyval.node) = setBoardVarNode(BOARDVAR,(yyvsp[(1) - (1)].val),0); }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 181 "parser/tbl.y"
    { (yyval.node) = setBoardVarNode(BOARDVAR,(yyvsp[(1) - (3)].val),(yyvsp[(3) - (3)].val)); }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 185 "parser/tbl.y"
    { (yyval.node) = setNode(0,(yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node)); }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 186 "parser/tbl.y"
    { (yyval.node) = setNode(SEMI,(yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node)); }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 187 "parser/tbl.y"
    { (yyval.node) = setNode(0,(yyvsp[(1) - (2)].node),NULL); }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 188 "parser/tbl.y"
    { (yyval.node) = setNode(0,(yyvsp[(1) - (1)].node),NULL); }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 192 "parser/tbl.y"
    { (yyval.node) = setVarNode(CHARVAR,(yyvsp[(1) - (1)].val),NULL); }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 196 "parser/tbl.y"
    { (yyval.node) = setNode(0,(yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node)); }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 197 "parser/tbl.y"
    { (yyval.node) = setNode(SEMI,(yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node)); }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 198 "parser/tbl.y"
    { (yyval.node) = setNode(0,(yyvsp[(1) - (2)].node),NULL); }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 199 "parser/tbl.y"
    { (yyval.node) = setNode(0,(yyvsp[(1) - (1)].node),NULL); }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 203 "parser/tbl.y"
    { (yyval.node) = setVarNode(MANYVAR,(yyvsp[(1) - (1)].val),NULL); }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 207 "parser/tbl.y"
    { (yyval.node) = setNode(0,(yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node)); }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 208 "parser/tbl.y"
    { (yyval.node) = setNode(SEMI,(yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node)); }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 209 "parser/tbl.y"
    { (yyval.node) = setNode(0,(yyvsp[(1) - (2)].node),NULL); }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 210 "parser/tbl.y"
    { (yyval.node) = setNode(0,(yyvsp[(1) - (1)].node),NULL); }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 214 "parser/tbl.y"
    { (yyval.node) = setVarNode(ELABTEMP,(yyvsp[(1) - (1)].val),NULL); }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 215 "parser/tbl.y"
    { (yyval.node) = setVarNode(ELABQUEST,0,NULL); }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 216 "parser/tbl.y"
    { (yyval.node) = setVarNode(ELABNEG,(yyvsp[(2) - (2)].val),NULL); }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 217 "parser/tbl.y"
    { (yyval.node) = setVarNode(ELABPAREN,0,(yyvsp[(2) - (3)].node)); }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 218 "parser/tbl.y"
    { (yyval.node) = setVarNode(ELABCOL,(yyvsp[(1) - (5)].val),(yyvsp[(4) - (5)].node)); }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 222 "parser/tbl.y"
    { (yyval.node) = setCommaNode(ELABVAR,(yyvsp[(1) - (1)].val),NULL); }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 223 "parser/tbl.y"
    { (yyval.node) = setCommaNode(ELABNEG,(yyvsp[(2) - (2)].val),NULL); }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 224 "parser/tbl.y"
    { (yyval.node) = setCommaNode(ELABVAR,(yyvsp[(1) - (3)].val),(yyvsp[(3) - (3)].node)); }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 225 "parser/tbl.y"
    { (yyval.node) = setCommaNode(ELABNEG,(yyvsp[(2) - (4)].val),(yyvsp[(4) - (4)].node)); }
    break;



/* Line 1806 of yacc.c  */
#line 1994 "y.tab.c"
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

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
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
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



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
		      yytoken, &yylval);
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 227 "parser/tbl.y"




