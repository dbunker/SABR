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

#[^\n]*[\n]				curLineNum++;

[ \t\r]+				;

[\n]					curLineNum++;

.						{ printf("Error: Unknown Character On Line %i\n",curLineNum); exit(0); }

%%

