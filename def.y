%{
#include <string.h>
#include <stdio.h>
#define INFILE_ERROR 1
#define OUTFILE_ERROR 2
FILE *rpn, *threes;
%}
%union 
{
    char *text;
    int	ival;
    float fval;
};
%token EQ NEQ GEQ 
%token LEQUAL ASSIGN
%token <text> ID
%token <ival> LC
%token <fval> LF
%%
wyr
	:wyr '+' skladnik	{fprintf(rpn," + ");}
	|wyr '-' skladnik	{fprintf(rpn," - ");}
	|skladnik		{fprintf(rpn," skladnik ");}
	;
skladnik
	:skladnik '*' czynnik	{fprintf(rpn," * ");}
	|skladnik '/' czynnik	{fprintf(rpn," / ");}
	|czynnik		{fprintf(rpn," czynnik ");}
	;
czynnik
	:ID			{fprintf(rpn,"%s ", $1);} 
	|LC			{fprintf(rpn,"%d ", $1);}
	|'(' wyr ')'		{fprintf(rpn,"wyrazenie w nawiasach");}
	;
%%
int main(int argc, char *argv[])
{
    rpn = fopen("rpn.txt", "wt");
    threes = fopen("threes.txt", "wt");

	yyparse();

    fclose(rpn);
    fclose(threes);
	return 0;
}