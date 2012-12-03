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

/* Line 2068 of yacc.c  */
#line 28 "parser/tbl.y"

    int val;
    treeNode *node;



/* Line 2068 of yacc.c  */
#line 109 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


