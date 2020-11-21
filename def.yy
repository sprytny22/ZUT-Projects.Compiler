%{
#include <string>
#include <string.h>
#include <stack>

using namespace std;

#define INFILE_ERROR 1
#define OUTFILE_ERROR 2

FILE *rpn, *threes;

std::stack<std::string> stos;

int yylex();
int yyerror(const char *msg, ...);

char* stackBump();
char* makeThree(std::string, std::string);

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
%start wyr
%%
prog 
	:wyr ';' prog
	|wyr ';'
	;
wyr
	:wyr '+' skladnik	{
		fprintf(threes, stackBump());
		fprintf(rpn," + ");
	}
	|wyr '-' skladnik	{
		fprintf(threes, stackBump());
		fprintf(rpn," - ");
	}
	|wyr '=' skladnik	{
		fprintf(threes, stackBump());
		fprintf(rpn," = ");
	}
	|skladnik		{
		fprintf(rpn," skladnik ");
	}
	;
skladnik
	:skladnik '*' czynnik	{
		fprintf(threes, stackBump());
		fprintf(rpn," * ");
	}
	|skladnik '/' czynnik	{
		fprintf(threes, stackBump());
		fprintf(rpn," / ");
		
	}
	|czynnik		{
		fprintf(rpn," czynnik ");
	}
	;
czynnik
	:ID	{
		stos.push($1);
		fprintf(rpn,"%s ", $1);
	} 
	|LC	{
		stos.push(std::to_string($1));
		fprintf(rpn,"%d ", $1);
	}
	|'(' wyr ')'		{fprintf(rpn,"wyrazenie w nawiasach");}
	;
%%
int main(int argc, char *argv[])
{
    rpn = fopen("rpn.txt", "wt");
    threes = fopen("threes.txt", "wt");

	yyparse();

	if (!stos.empty()) { 
		return 1;
	}

    fclose(rpn);
    fclose(threes);
	return 0;
}

char* stackBump() {
	std::string result = stos.top();
	stos.pop();
	std::string arg1 = stos.top();
	stos.pop();


	stos.push("result");

	return makeThree(result, arg1);
}

char* makeThree(std::string result, std::string arg1) {
	std::string s = "result = " + arg1 + " " + result + "\n";

	int n = s.length();

	char* char_array = new char[n+1];
	strcpy(char_array, s.c_str());

	return char_array;
}