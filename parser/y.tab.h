/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
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

/* Line 2068 of yacc.c  */
#line 30 "parser/tbl.y"

    int val;
    treeNode *node;



/* Line 2068 of yacc.c  */
#line 111 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


