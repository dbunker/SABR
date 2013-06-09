/* lex file */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../core/arch.h"
#include "y.tab.h"
%}

%option nounput
%option noinput

%%

"Sym"					{ return SYMBOLS; 	}
"Board"					{ return BOARD; 	}
"Start"					{ return START;		}
"End"					{ return END;		}
"Obj"					{ return OBJECT;	}
"DesObj"				{ return DESOBJECT;	}
"AllDif"				{ return ALLDIF;	}
"Trans"					{ return TRANSFORM;	}
"TransSim"				{ return TRANSFORMSIM;	}
"Req"					{ return REQUIRE;	}
"Opt"					{ return OPTION;	}
"=>"					{ return ARROW;		}

[0-9a-zA-Z\-\_]+		{
							int symVal = addSymbol(yytext);
							yylval.val = symVal;
							return VARIABLE;
						}

[\(\)\{\}\,\.\;\:\!\?] 	{
							return *yytext;
						}

#\([^(\)#)]*\)#			;

#[^\n]*[\n]				curLineNumGlobal++;

[ \t\r]+				;

[\n]					curLineNumGlobal++;

.						{ printf("Error: Unknown Character On Line %i\n",curLineNumGlobal); endError(); }

%%

