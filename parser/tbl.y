/*************************************************************************
@copyright Copyright (c) 2011 David Bunker

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*************************************************************************/

/* yacc file */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../core/arch.h"

int yylex(void);
%}

%union {
    int val;
    treeNode *node;
};

%token <val> VARIABLE;
%token SYMBOLS;
%token BOARD;
%token START;
%token END;
%token OBJECT;
%token DESOBJECT;
%token TRANSFORM;
%token TRANSFORMSIM;
%token REQUIRE;
%token OPTION;
%token ARROW;
%token SEMI;
%token CHARVAR;
%token BOARDVAR;
%token <val> SPACEVAR;
%token MANYVAR;
%token MANYBRACK;
%token ELABTEMP;
%token ELABQUEST;
%token ELABVAR;
%token ELABNEG;
%token ELABPAREN;
%token ELABCOL;

%start root
%type <node> statements choices symbols symlist board start end transform setstages
	     object desobject require option objset boardset boardvar charset charvar
	     manyset manyvar elabset elabvar elabcomma;
%type <val>  transtype anyobject;

%%

root:
	  statements							{ if(endFile) execute($1); }
	;

statements:
	  symbols board start end choices		{ $$ = statementNodes($1,$2,$3,$4,$5); }
	| symbols board choices					{ $$ = statementNodes($1,$2,NULL,NULL,$3); }
	;

choices:
	  object choices			{ $$ = choiceNode(OBJECT,$1,$2); }
	| desobject choices			{ $$ = choiceNode(DESOBJECT,$1,$2); }
	| transform choices			{ $$ = choiceNode(TRANSFORM,$1,$2); }
	| require choices			{ $$ = choiceNode(REQUIRE,$1,$2); }
	| option choices			{ $$ = choiceNode(OPTION,$1,$2); }
	| /* empty */				{ $$ = NULL; }
	;

setstages:
	  '(' VARIABLE ':' VARIABLE ')'		{ $$ = setStages($2,$4); }
	| /* empty */						{ $$ = NULL; }
	;

symbols:
	  symlist							{ $$ = symNode($1,NULL); }
	| symlist symbols					{ $$ = symNode($1,$2); }
	;

symlist:
	  SYMBOLS '{' charset '}'			{ $$ = nameNode(SYMBOLS,NULL,0,0,$3); }
	| SYMBOLS VARIABLE '{' charset '}'	{ $$ = nameNode(SYMBOLS,NULL,$2,0,$4); }
	;

board:
	  BOARD '{' boardset '}'			{ $$ = storeNode(BOARD,$3); }
	;

start:
	  START '{' elabset '}'				{ $$ = nameNode(START,NULL,0,0,$3); }
	;

end:
	  END '{' elabset '}'				{ $$ = nameNode(END,NULL,0,0,$3); }
	;

transform:
	  transtype setstages VARIABLE ':' anyobject '{' elabset ARROW elabset '}'
	  		{ $$ = transNode($1,$2,$3,$5,$7,$9); }
	  		
	| transtype setstages anyobject '{' elabset ARROW elabset '}'				
			{ $$ = transNode($1,$2,0,$3,$5,$7); }
	;

transtype:
	  TRANSFORM							{ $$ = TRANSFORM; }
	| TRANSFORMSIM						{ $$ = TRANSFORMSIM; }
	;

anyobject:
	  VARIABLE							{ $$ = $1; }
	| BOARD								{ $$ = addSymbol("Board"); }
	;

object:
	  OBJECT VARIABLE '{' objset '}'	{ $$ = nameNode(OBJECT,NULL,$2,$2,$4); }
	;

desobject:
	  DESOBJECT VARIABLE ':' VARIABLE '{' manyset '}'		
			{ $$ = nameNode(DESOBJECT,NULL,$2,$4,$6); }
			
	| DESOBJECT VARIABLE '{' manyset '}'
			{ $$ = nameNode(DESOBJECT,NULL,0,$2,$4); }
	;

require:
	  REQUIRE setstages VARIABLE ':' anyobject '{' elabset '}'
	  		{ $$ = nameNode(REQUIRE,$2,$3,$5,$7); }
	  		
	| REQUIRE setstages anyobject '{' elabset '}'			
			{ $$ = nameNode(REQUIRE,$2,0,$3,$5); }
	;

option:
	  OPTION setstages VARIABLE ':' anyobject '{' elabset '}'	
			{ $$ = nameNode(OPTION,$2,$3,$5,$7); }
	  
	| OPTION setstages anyobject '{' elabset '}'
			{ $$ = nameNode(OPTION,$2,0,$3,$5); }
	;

objset:
	  boardvar objset 				{ $$ = setNode(0,$1,$2); }
	| boardvar ';' objset			{ $$ = setNode(SEMI,$1,$3); }
	| boardvar ';'					{ $$ = setNode(0,$1,NULL); }
	| boardvar						{ $$ = setNode(0,$1,NULL); }
	;

boardset:
	  boardvar boardset 			{ $$ = setNode(0,$1,$2); }
	| boardvar ';' boardset			{ $$ = setNode(SEMI,$1,$3); }
	| boardvar ';'					{ $$ = setNode(0,$1,NULL); }
	| boardvar						{ $$ = setNode(0,$1,NULL); }
	| '.' boardset					{ $$ = setNode(SPACEVAR,NULL,$2); }
	;

boardvar:
	  VARIABLE						{ $$ = setBoardVarNode(BOARDVAR,$1,0); }
	| VARIABLE ':' VARIABLE			{ $$ = setBoardVarNode(BOARDVAR,$1,$3); }
	;

charset:
	  charvar charset 				{ $$ = setNode(0,$1,$2); }
	| charvar ';' charset			{ $$ = setNode(SEMI,$1,$3); }
	| charvar ';'					{ $$ = setNode(0,$1,NULL); }
	| charvar						{ $$ = setNode(0,$1,NULL); }
	;

charvar:
	  VARIABLE						{ $$ = setVarNode(CHARVAR,$1,NULL); }
	;

manyset:
	  manyvar manyset 				{ $$ = setNode(0,$1,$2); }
	| manyvar ';' manyset			{ $$ = setNode(SEMI,$1,$3); }
	| manyvar ';'					{ $$ = setNode(0,$1,NULL); }
	| manyvar						{ $$ = setNode(0,$1,NULL); }
	;

manyvar:
	  VARIABLE						{ $$ = setVarNode(MANYVAR,$1,NULL); }
	;

elabset:
	  elabvar elabset 				{ $$ = setNode(0,$1,$2); }
	| elabvar ';' elabset			{ $$ = setNode(SEMI,$1,$3); }
	| elabvar ';'					{ $$ = setNode(0,$1,NULL); }
	| elabvar						{ $$ = setNode(0,$1,NULL); }
	;

elabvar:
	  VARIABLE							{ $$ = setVarNode(ELABTEMP,$1,NULL); }
	| '?'								{ $$ = setVarNode(ELABQUEST,0,NULL); }
	| '!' VARIABLE						{ $$ = setVarNode(ELABNEG,$2,NULL); }
	| '(' elabcomma ')'					{ $$ = setVarNode(ELABPAREN,0,$2); }
	| VARIABLE ':' '(' elabcomma ')'	{ $$ = setVarNode(ELABCOL,$1,$4); }
	;

elabcomma:
	  VARIABLE							{ $$ = setCommaNode(ELABVAR,$1,NULL); }
	| '!' VARIABLE						{ $$ = setCommaNode(ELABNEG,$2,NULL); }
	| VARIABLE ',' elabcomma			{ $$ = setCommaNode(ELABVAR,$1,$3); }
	| '!' VARIABLE ',' elabcomma		{ $$ = setCommaNode(ELABNEG,$2,$4); }

%%


