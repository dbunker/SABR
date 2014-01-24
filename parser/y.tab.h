/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
     TRANSFORMLOCK = 268,
     REQUIRE = 269,
     OPTION = 270,
     ARROW = 271,
     SEMI = 272,
     CHARVAR = 273,
     BOARDVAR = 274,
     SPACEVAR = 275,
     MANYVAR = 276,
     MANYBRACK = 277,
     ELABTEMP = 278,
     ELABQUEST = 279,
     ELABVAR = 280,
     ELABNEG = 281,
     ELABPAREN = 282,
     ELABCOL = 283
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
#define TRANSFORMLOCK 268
#define REQUIRE 269
#define OPTION 270
#define ARROW 271
#define SEMI 272
#define CHARVAR 273
#define BOARDVAR 274
#define SPACEVAR 275
#define MANYVAR 276
#define MANYBRACK 277
#define ELABTEMP 278
#define ELABQUEST 279
#define ELABVAR 280
#define ELABNEG 281
#define ELABPAREN 282
#define ELABCOL 283




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 14 "parser/tbl.y"
{
    int val;
    treeNode *node;
}
/* Line 1529 of yacc.c.  */
#line 110 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

