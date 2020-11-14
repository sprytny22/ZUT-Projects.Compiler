%{
#include <stdlib.h>
#include <string.h>
#include "def.tab.h"
#define INFILE_ERROR 1
#define OUTFILE_ERROR 2
extern int yylineno;
int yyerror(char *,...);
%}
%%
\+			{return '+';} 
\*			{return '*';}
\(			{return '(';}
\)			{return ')';}
\/			{return '/';}
\-			{return '-';}
\^			{return '^';}
\=			{return '=';}
\:\=        {return ASSIGN;}
\<\=        {return LEQUAL;}    
0|[1-9][0-9]*		    { yylval.ival = atoi(yytext);   return LC;}	
[1-9][0-9]*\.[0-9]*     { yylval.fval = atof(yytext);   return LF;}
[A-Za-z_][A-Za-z0-9_]*	{ yylval.text = strdup(yytext); return ID;}
\ |\t			{;}
\n			{yylineno++;}
.			{yyerror("Blad leksykalny\n");}
%%
int yyerror(char *msg,...)
{
	printf("%d: %s", yylineno, msg);
	exit(1);
}
