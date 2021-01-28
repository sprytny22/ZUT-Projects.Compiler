%{
#include <stdlib.h>
#include <string.h>
#include "def.tab.hh"

#define INFILE_ERROR 1
#define OUTFILE_ERROR 2

extern int yylineno;
int yyerror(char *,...);
void sendOutput(char *);
%}

%%
integer					{ return INT; } 
double					{ return DOUBLE; }
string					{ return STRING; }
boolean					{ return BOOLEAN; }
\+						{ return '+'; }
\-						{ return '-'; }
\=						{ return '='; }
\/						{ return '/'; }
\*						{ return '*'; }
"end"					{ return ';'; }
"if"					{ return IF;      } 
"else"					{ return ELSE;    }
"while"					{ return WHILE;   }  
"print"					{ return PRINT;   }
"read"					{ return READ;    }  
"return"				{ return RETURN;  }  
"true"					{ return TRUE;    } 
"false"					{ return FALSE;   }  
\/\/					{ return COMMENT; }
\(						{ return '(';     }
\)						{ return ')';     }
\[						{ return '[';     }
\{						{ return '{';     }
\}						{ return '}';     }
\"						{ return '"';     }
\]						{ return ']';     }
\/\/					{ return COMMENT;}
\=\=					{ return EQ;}
\>\=					{ return GEQ;}
\<\=					{ return LEQ;}
\!\=					{ return NEQ;}
\>						{ return LARGER;}
\<						{ return SMALLER;}

[A-Za-z_][A-Za-z0-9_]*	{ 
							yylval.textValue = strdup(yytext);
							return TEXT;
						}
[1-9][0-9]*|0			{
							yylval.integerValue = atoi(yytext);
							return VALUE_INTEGER;
						}
([1-9][0-9]*|0)\.[0-9]+ {
							yylval.decimalValue = atof(yytext);
							return VALUE_DECIMAL;
						}		
[ \t]					{;}
[\r][\n]					{  yylineno++; }
.						{ return yytext[0];}
%%

void sendOutput(char *value)
{
	fprintf(yyout, "%s\n", value);
}

int yyerror(char *msg,...)
{
	printf("%d: %s", yylineno, msg);
	exit(1);
}