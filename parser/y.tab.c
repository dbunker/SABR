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
#line 19 "parser/tbl.y"

#define YYMAXDEPTH 100000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../core/arch.h"

int yylex(void);


/* Line 268 of yacc.c  */
#line 83 "y.tab.c"

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
     ALLDIF = 265,
     TRANSFORM = 266,
     TRANSFORMSIM = 267,
     REQUIRE = 268,
     OPTION = 269,
     ARROW = 270,
     SEMI = 271,
     CHARVAR = 272,
     BOARDVAR = 273,
     SPACEVAR = 274,
     MANYVAR = 275,
     MANYBRACK = 276,
     ELABTEMP = 277,
     ELABQUEST = 278,
     ELABVAR = 279,
     ELABNEG = 280,
     ELABPAREN = 281,
     ELABCOL = 282
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
#define ALLDIF 265
#define TRANSFORM 266
#define TRANSFORMSIM 267
#define REQUIRE 268
#define OPTION 269
#define ARROW 270
#define SEMI 271
#define CHARVAR 272
#define BOARDVAR 273
#define SPACEVAR 274
#define MANYVAR 275
#define MANYBRACK 276
#define ELABTEMP 277
#define ELABQUEST 278
#define ELABVAR 279
#define ELABNEG 280
#define ELABPAREN 281
#define ELABCOL 282




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 30 "parser/tbl.y"

    int val;
    treeNode *node;



/* Line 293 of yacc.c  */
#line 180 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 192 "y.tab.c"

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
#define YYLAST   162

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  69
/* YYNRULES -- Number of states.  */
#define YYNSTATES  159

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   282

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    36,     2,     2,     2,     2,     2,     2,
      28,    30,     2,     2,    37,     2,    34,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    29,    33,
       2,     2,     2,    35,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    31,     2,    32,     2,     2,     2,     2,
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
      25,    26,    27
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,    11,    15,    18,    21,    24,    27,
      30,    33,    34,    40,    44,    45,    47,    50,    55,    61,
      66,    71,    76,    87,    96,    98,   100,   102,   104,   110,
     118,   124,   130,   139,   146,   155,   162,   165,   169,   172,
     174,   177,   181,   184,   186,   189,   191,   195,   198,   202,
     205,   207,   209,   212,   216,   219,   221,   223,   226,   230,
     233,   235,   237,   239,   242,   246,   252,   254,   257,   261
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      39,     0,    -1,    40,    -1,    43,    45,    46,    47,    41,
      -1,    43,    45,    41,    -1,    51,    41,    -1,    52,    41,
      -1,    53,    41,    -1,    48,    41,    -1,    54,    41,    -1,
      55,    41,    -1,    -1,    28,     3,    29,     3,    30,    -1,
      28,     3,    30,    -1,    -1,    44,    -1,    44,    43,    -1,
       4,    31,    59,    32,    -1,     4,     3,    31,    59,    32,
      -1,     5,    31,    57,    32,    -1,     6,    31,    63,    32,
      -1,     7,    31,    63,    32,    -1,    49,    42,     3,    29,
      50,    31,    63,    15,    63,    32,    -1,    49,    42,    50,
      31,    63,    15,    63,    32,    -1,    11,    -1,    12,    -1,
       3,    -1,     5,    -1,     8,     3,    31,    56,    32,    -1,
       9,     3,    29,     3,    31,    61,    32,    -1,     9,     3,
      31,    61,    32,    -1,    10,    42,    31,    61,    32,    -1,
      13,    42,     3,    29,    50,    31,    63,    32,    -1,    13,
      42,    50,    31,    63,    32,    -1,    14,    42,     3,    29,
      50,    31,    63,    32,    -1,    14,    42,    50,    31,    63,
      32,    -1,    58,    56,    -1,    58,    33,    56,    -1,    58,
      33,    -1,    58,    -1,    58,    57,    -1,    58,    33,    57,
      -1,    58,    33,    -1,    58,    -1,    34,    57,    -1,     3,
      -1,     3,    29,     3,    -1,    60,    59,    -1,    60,    33,
      59,    -1,    60,    33,    -1,    60,    -1,     3,    -1,    62,
      61,    -1,    62,    33,    61,    -1,    62,    33,    -1,    62,
      -1,     3,    -1,    64,    63,    -1,    64,    33,    63,    -1,
      64,    33,    -1,    64,    -1,     3,    -1,    35,    -1,    36,
       3,    -1,    28,    65,    30,    -1,     3,    29,    28,    65,
      30,    -1,     3,    -1,    36,     3,    -1,     3,    37,    65,
      -1,    36,     3,    37,    65,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    70,    70,    74,    75,    79,    80,    81,    82,    83,
      84,    85,    89,    90,    91,    95,    96,   100,   101,   105,
     109,   113,   117,   120,   125,   126,   130,   131,   135,   139,
     142,   147,   152,   155,   160,   163,   168,   169,   170,   171,
     175,   176,   177,   178,   179,   183,   184,   188,   189,   190,
     191,   195,   199,   200,   201,   202,   206,   210,   211,   212,
     213,   217,   218,   219,   220,   221,   225,   226,   227,   228
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "VARIABLE", "SYMBOLS", "BOARD", "START",
  "END", "OBJECT", "DESOBJECT", "ALLDIF", "TRANSFORM", "TRANSFORMSIM",
  "REQUIRE", "OPTION", "ARROW", "SEMI", "CHARVAR", "BOARDVAR", "SPACEVAR",
  "MANYVAR", "MANYBRACK", "ELABTEMP", "ELABQUEST", "ELABVAR", "ELABNEG",
  "ELABPAREN", "ELABCOL", "'('", "':'", "')'", "'{'", "'}'", "';'", "'.'",
  "'?'", "'!'", "','", "$accept", "root", "statements", "choices",
  "setstages", "symbols", "symlist", "board", "start", "end", "transform",
  "transtype", "anyobject", "object", "desobject", "alldif", "require",
  "option", "objset", "boardset", "boardvar", "charset", "charvar",
  "manyset", "manyvar", "elabset", "elabvar", "elabcomma", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,    40,    58,
      41,   123,   125,    59,    46,    63,    33,    44
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    38,    39,    40,    40,    41,    41,    41,    41,    41,
      41,    41,    42,    42,    42,    43,    43,    44,    44,    45,
      46,    47,    48,    48,    49,    49,    50,    50,    51,    52,
      52,    53,    54,    54,    55,    55,    56,    56,    56,    56,
      57,    57,    57,    57,    57,    58,    58,    59,    59,    59,
      59,    60,    61,    61,    61,    61,    62,    63,    63,    63,
      63,    64,    64,    64,    64,    64,    65,    65,    65,    65
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     5,     3,     2,     2,     2,     2,     2,
       2,     0,     5,     3,     0,     1,     2,     4,     5,     4,
       4,     4,    10,     8,     1,     1,     1,     1,     5,     7,
       5,     5,     8,     6,     8,     6,     2,     3,     2,     1,
       2,     3,     2,     1,     2,     1,     3,     2,     3,     2,
       1,     1,     2,     3,     2,     1,     1,     2,     3,     2,
       1,     1,     1,     2,     3,     5,     1,     2,     3,     4
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     0,    15,     0,     0,     1,     0,
      11,    16,     0,    51,     0,    50,     0,     0,     0,     0,
      14,    24,    25,    14,    14,     4,     0,    11,    14,    11,
      11,    11,    11,    11,     0,    17,    49,    47,    45,     0,
       0,    43,     0,     0,     0,     0,     0,     0,     0,     0,
      11,     8,     0,     5,     6,     7,     9,    10,    18,    48,
       0,    44,    19,    42,    40,    61,     0,    62,     0,     0,
      60,     0,     0,     0,     0,     0,    26,    27,     0,    26,
       0,     0,     3,    26,     0,    46,    41,     0,    66,     0,
       0,    63,    20,    59,    57,     0,    39,     0,    56,     0,
      55,     0,    13,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    67,    64,    58,    28,    38,    36,     0,
      30,    54,    52,     0,    31,    26,     0,     0,     0,     0,
      21,     0,     0,     0,    68,     0,    37,     0,    53,    12,
       0,    33,     0,    35,     0,     0,    65,    69,    29,     0,
       0,     0,     0,    32,    34,     0,    23,     0,    22
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,    25,    46,     4,     5,    10,    26,    50,
      27,    28,    78,    29,    30,    31,    32,    33,    95,    40,
      41,    14,    15,    99,   100,    69,    70,    90
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -89
static const yytype_int16 yypact[] =
{
      15,     1,    25,   -89,     2,    15,   -16,    27,   -89,   -13,
      87,   -89,    27,   -89,    28,    17,    13,    42,    30,    73,
      52,   -89,   -89,    52,    52,   -89,    74,    94,    52,    94,
      94,    94,    94,    94,    78,   -89,    27,   -89,    54,    13,
      79,    11,     6,    53,    -5,    91,    81,    51,    62,    82,
      94,   -89,    63,   -89,   -89,   -89,   -89,   -89,   -89,   -89,
     111,   -89,   -89,    13,   -89,    86,     7,   -89,   113,    85,
       3,   115,   116,   117,    49,   117,    92,   -89,    93,    96,
      95,     6,   -89,    98,    97,   -89,   -89,   101,    99,   119,
     100,   -89,   -89,     6,   -89,   102,    18,   104,   -89,   105,
      19,   120,   -89,   106,    66,     6,    66,     6,   107,    66,
       6,     7,     7,   103,   -89,   -89,   -89,   115,   -89,   117,
     -89,   117,   -89,   112,   -89,   -89,   110,   114,   118,   121,
     -89,   123,   128,   122,   -89,     7,   -89,   124,   -89,   -89,
       6,   -89,     6,   -89,     6,     6,   -89,   -89,   -89,   125,
     126,   129,   127,   -89,   -89,     6,   -89,   130,   -89
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -89,   -89,   -89,    59,   -11,   140,   -89,   -89,   -89,   -89,
     -89,   -89,   -47,   -89,   -89,   -89,   -89,   -89,   -88,    14,
     -68,    46,   -89,   -73,   -89,   -70,   -89,   -48
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      94,    80,   103,    96,     6,    84,    65,     9,   118,    65,
      88,   108,    47,    48,    38,    12,    38,    52,    16,     1,
      13,    38,    98,   115,    72,     8,    73,   122,    96,   136,
      13,    66,     7,    43,    66,   127,    93,   129,    67,    68,
     132,    67,    68,    89,    63,    39,   137,    39,   138,    96,
      36,   117,   121,    61,    76,    64,    77,   126,    34,   128,
      35,    37,   131,   133,   134,    79,    83,    77,    77,   125,
     149,    77,   150,    42,   151,   152,    44,    86,   101,   102,
      45,    49,    59,    60,    71,   157,    51,   147,    53,    54,
      55,    56,    57,    17,    74,    18,    19,    20,    21,    22,
      23,    24,    18,    19,    20,    21,    22,    23,    24,    82,
      58,    62,    75,    81,    85,    87,    91,    92,    38,    97,
      98,   104,   113,   123,   105,   106,   107,   109,   110,   111,
     114,     0,     0,     0,   116,   119,   112,   120,   124,   130,
     135,   140,   139,   145,   155,    11,   141,     0,     0,   142,
       0,     0,   146,   143,   144,     0,   148,   153,   154,   156,
       0,     0,   158
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-89))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      70,    48,    75,    71,     3,    52,     3,     5,    96,     3,
       3,    81,    23,    24,     3,    31,     3,    28,    31,     4,
       3,     3,     3,    93,    29,     0,    31,   100,    96,   117,
       3,    28,    31,     3,    28,   105,    33,   107,    35,    36,
     110,    35,    36,    36,    33,    34,   119,    34,   121,   117,
      33,    33,    33,    39,     3,    41,     5,   104,    12,   106,
      32,    15,   109,   111,   112,     3,     3,     5,     5,     3,
     140,     5,   142,    31,   144,   145,     3,    63,    29,    30,
      28,     7,    36,    29,    31,   155,    27,   135,    29,    30,
      31,    32,    33,     6,     3,     8,     9,    10,    11,    12,
      13,    14,     8,     9,    10,    11,    12,    13,    14,    50,
      32,    32,    31,    31,     3,    29,     3,    32,     3,     3,
       3,    29,     3,     3,    31,    29,    31,    29,    31,    28,
      30,    -1,    -1,    -1,    32,    31,    37,    32,    32,    32,
      37,    31,    30,    15,    15,     5,    32,    -1,    -1,    31,
      -1,    -1,    30,    32,    31,    -1,    32,    32,    32,    32,
      -1,    -1,    32
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,    39,    40,    43,    44,     3,    31,     0,     5,
      45,    43,    31,     3,    59,    60,    31,     6,     8,     9,
      10,    11,    12,    13,    14,    41,    46,    48,    49,    51,
      52,    53,    54,    55,    59,    32,    33,    59,     3,    34,
      57,    58,    31,     3,     3,    28,    42,    42,    42,     7,
      47,    41,    42,    41,    41,    41,    41,    41,    32,    59,
      29,    57,    32,    33,    57,     3,    28,    35,    36,    63,
      64,    31,    29,    31,     3,    31,     3,     5,    50,     3,
      50,    31,    41,     3,    50,     3,    57,    29,     3,    36,
      65,     3,    32,    33,    63,    56,    58,     3,     3,    61,
      62,    29,    30,    61,    29,    31,    29,    31,    63,    29,
      31,    28,    37,     3,    30,    63,    32,    33,    56,    31,
      32,    33,    61,     3,    32,     3,    50,    63,    50,    63,
      32,    50,    63,    65,    65,    37,    56,    61,    61,    30,
      31,    32,    31,    32,    31,    15,    30,    65,    32,    63,
      63,    63,    63,    32,    32,    15,    32,    63,    32
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
#line 70 "parser/tbl.y"
    { if(endFileGlobal) execute((yyvsp[(1) - (1)].node)); }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 74 "parser/tbl.y"
    { (yyval.node) = statementNodes((yyvsp[(1) - (5)].node),(yyvsp[(2) - (5)].node),(yyvsp[(3) - (5)].node),(yyvsp[(4) - (5)].node),(yyvsp[(5) - (5)].node)); }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 75 "parser/tbl.y"
    { (yyval.node) = statementNodes((yyvsp[(1) - (3)].node),(yyvsp[(2) - (3)].node),NULL,NULL,(yyvsp[(3) - (3)].node)); }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 79 "parser/tbl.y"
    { (yyval.node) = choiceNode(OBJECT,(yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node)); }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 80 "parser/tbl.y"
    { (yyval.node) = choiceNode(DESOBJECT,(yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node)); }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 81 "parser/tbl.y"
    { (yyval.node) = choiceNode(ALLDIF,(yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node)); }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 82 "parser/tbl.y"
    { (yyval.node) = choiceNode(TRANSFORM,(yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node)); }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 83 "parser/tbl.y"
    { (yyval.node) = choiceNode(REQUIRE,(yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node)); }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 84 "parser/tbl.y"
    { (yyval.node) = choiceNode(OPTION,(yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node)); }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 85 "parser/tbl.y"
    { (yyval.node) = NULL; }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 89 "parser/tbl.y"
    { (yyval.node) = setStages((yyvsp[(2) - (5)].val),(yyvsp[(4) - (5)].val)); }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 90 "parser/tbl.y"
    { (yyval.node) = setStages((yyvsp[(2) - (3)].val),(yyvsp[(2) - (3)].val)); }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 91 "parser/tbl.y"
    { (yyval.node) = NULL; }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 95 "parser/tbl.y"
    { (yyval.node) = symNode((yyvsp[(1) - (1)].node),NULL); }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 96 "parser/tbl.y"
    { (yyval.node) = symNode((yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node)); }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 100 "parser/tbl.y"
    { (yyval.node) = nameNode(SYMBOLS,NULL,0,0,(yyvsp[(3) - (4)].node)); }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 101 "parser/tbl.y"
    { (yyval.node) = nameNode(SYMBOLS,NULL,(yyvsp[(2) - (5)].val),0,(yyvsp[(4) - (5)].node)); }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 105 "parser/tbl.y"
    { (yyval.node) = storeNode(BOARD,(yyvsp[(3) - (4)].node)); }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 109 "parser/tbl.y"
    { (yyval.node) = nameNode(START,NULL,0,0,(yyvsp[(3) - (4)].node)); }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 113 "parser/tbl.y"
    { (yyval.node) = nameNode(END,NULL,0,0,(yyvsp[(3) - (4)].node)); }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 118 "parser/tbl.y"
    { (yyval.node) = transNode((yyvsp[(1) - (10)].val),(yyvsp[(2) - (10)].node),(yyvsp[(3) - (10)].val),(yyvsp[(5) - (10)].val),(yyvsp[(7) - (10)].node),(yyvsp[(9) - (10)].node)); }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 121 "parser/tbl.y"
    { (yyval.node) = transNode((yyvsp[(1) - (8)].val),(yyvsp[(2) - (8)].node),0,(yyvsp[(3) - (8)].val),(yyvsp[(5) - (8)].node),(yyvsp[(7) - (8)].node)); }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 125 "parser/tbl.y"
    { (yyval.val) = TRANSFORM; }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 126 "parser/tbl.y"
    { (yyval.val) = TRANSFORMSIM; }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 130 "parser/tbl.y"
    { (yyval.val) = (yyvsp[(1) - (1)].val); }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 131 "parser/tbl.y"
    { (yyval.val) = addSymbol("Board"); }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 135 "parser/tbl.y"
    { (yyval.node) = nameNode(OBJECT,NULL,(yyvsp[(2) - (5)].val),(yyvsp[(2) - (5)].val),(yyvsp[(4) - (5)].node)); }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 140 "parser/tbl.y"
    { (yyval.node) = nameNode(DESOBJECT,NULL,(yyvsp[(2) - (7)].val),(yyvsp[(4) - (7)].val),(yyvsp[(6) - (7)].node)); }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 143 "parser/tbl.y"
    { (yyval.node) = nameNode(DESOBJECT,NULL,0,(yyvsp[(2) - (5)].val),(yyvsp[(4) - (5)].node)); }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 148 "parser/tbl.y"
    { (yyval.node) = nameNode(ALLDIF,(yyvsp[(2) - (5)].node),0,0,(yyvsp[(4) - (5)].node)); }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 153 "parser/tbl.y"
    { (yyval.node) = nameNode(REQUIRE,(yyvsp[(2) - (8)].node),(yyvsp[(3) - (8)].val),(yyvsp[(5) - (8)].val),(yyvsp[(7) - (8)].node)); }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 156 "parser/tbl.y"
    { (yyval.node) = nameNode(REQUIRE,(yyvsp[(2) - (6)].node),0,(yyvsp[(3) - (6)].val),(yyvsp[(5) - (6)].node)); }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 161 "parser/tbl.y"
    { (yyval.node) = nameNode(OPTION,(yyvsp[(2) - (8)].node),(yyvsp[(3) - (8)].val),(yyvsp[(5) - (8)].val),(yyvsp[(7) - (8)].node)); }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 164 "parser/tbl.y"
    { (yyval.node) = nameNode(OPTION,(yyvsp[(2) - (6)].node),0,(yyvsp[(3) - (6)].val),(yyvsp[(5) - (6)].node)); }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 168 "parser/tbl.y"
    { (yyval.node) = setNode(0,(yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node)); }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 169 "parser/tbl.y"
    { (yyval.node) = setNode(SEMI,(yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node)); }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 170 "parser/tbl.y"
    { (yyval.node) = setNode(0,(yyvsp[(1) - (2)].node),NULL); }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 171 "parser/tbl.y"
    { (yyval.node) = setNode(0,(yyvsp[(1) - (1)].node),NULL); }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 175 "parser/tbl.y"
    { (yyval.node) = setNode(0,(yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node)); }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 176 "parser/tbl.y"
    { (yyval.node) = setNode(SEMI,(yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node)); }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 177 "parser/tbl.y"
    { (yyval.node) = setNode(0,(yyvsp[(1) - (2)].node),NULL); }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 178 "parser/tbl.y"
    { (yyval.node) = setNode(0,(yyvsp[(1) - (1)].node),NULL); }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 179 "parser/tbl.y"
    { (yyval.node) = setNode(SPACEVAR,NULL,(yyvsp[(2) - (2)].node)); }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 183 "parser/tbl.y"
    { (yyval.node) = setBoardVarNode(BOARDVAR,(yyvsp[(1) - (1)].val),0); }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 184 "parser/tbl.y"
    { (yyval.node) = setBoardVarNode(BOARDVAR,(yyvsp[(1) - (3)].val),(yyvsp[(3) - (3)].val)); }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 188 "parser/tbl.y"
    { (yyval.node) = setNode(0,(yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node)); }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 189 "parser/tbl.y"
    { (yyval.node) = setNode(SEMI,(yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node)); }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 190 "parser/tbl.y"
    { (yyval.node) = setNode(0,(yyvsp[(1) - (2)].node),NULL); }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 191 "parser/tbl.y"
    { (yyval.node) = setNode(0,(yyvsp[(1) - (1)].node),NULL); }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 195 "parser/tbl.y"
    { (yyval.node) = setVarNode(CHARVAR,(yyvsp[(1) - (1)].val),NULL); }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 199 "parser/tbl.y"
    { (yyval.node) = setNode(0,(yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node)); }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 200 "parser/tbl.y"
    { (yyval.node) = setNode(SEMI,(yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node)); }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 201 "parser/tbl.y"
    { (yyval.node) = setNode(0,(yyvsp[(1) - (2)].node),NULL); }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 202 "parser/tbl.y"
    { (yyval.node) = setNode(0,(yyvsp[(1) - (1)].node),NULL); }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 206 "parser/tbl.y"
    { (yyval.node) = setVarNode(MANYVAR,(yyvsp[(1) - (1)].val),NULL); }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 210 "parser/tbl.y"
    { (yyval.node) = setNode(0,(yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node)); }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 211 "parser/tbl.y"
    { (yyval.node) = setNode(SEMI,(yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node)); }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 212 "parser/tbl.y"
    { (yyval.node) = setNode(0,(yyvsp[(1) - (2)].node),NULL); }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 213 "parser/tbl.y"
    { (yyval.node) = setNode(0,(yyvsp[(1) - (1)].node),NULL); }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 217 "parser/tbl.y"
    { (yyval.node) = setVarNode(ELABTEMP,(yyvsp[(1) - (1)].val),NULL); }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 218 "parser/tbl.y"
    { (yyval.node) = setVarNode(ELABQUEST,0,NULL); }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 219 "parser/tbl.y"
    { (yyval.node) = setVarNode(ELABNEG,(yyvsp[(2) - (2)].val),NULL); }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 220 "parser/tbl.y"
    { (yyval.node) = setVarNode(ELABPAREN,0,(yyvsp[(2) - (3)].node)); }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 221 "parser/tbl.y"
    { (yyval.node) = setVarNode(ELABCOL,(yyvsp[(1) - (5)].val),(yyvsp[(4) - (5)].node)); }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 225 "parser/tbl.y"
    { (yyval.node) = setCommaNode(ELABVAR,(yyvsp[(1) - (1)].val),NULL); }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 226 "parser/tbl.y"
    { (yyval.node) = setCommaNode(ELABNEG,(yyvsp[(2) - (2)].val),NULL); }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 227 "parser/tbl.y"
    { (yyval.node) = setCommaNode(ELABVAR,(yyvsp[(1) - (3)].val),(yyvsp[(3) - (3)].node)); }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 228 "parser/tbl.y"
    { (yyval.node) = setCommaNode(ELABNEG,(yyvsp[(2) - (4)].val),(yyvsp[(4) - (4)].node)); }
    break;



/* Line 1806 of yacc.c  */
#line 2022 "y.tab.c"
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
#line 230 "parser/tbl.y"




