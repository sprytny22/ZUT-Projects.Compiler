%{
#include <string>
#include <stdio.h>
#include <stack>
#include <iostream>

#define INFILE_ERROR 1
#define OUTFILE_ERROR 2

std::stack<int> *stos;

FILE *rpn, *threes;

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
%%
wyr
	:wyr '+' skladnik	{
		fprintf(threes, stackBump());
		fprintf(rpn," + ");
	}
	|wyr '-' skladnik	{
		fprintf(threes, stackBump());
		fprintf(rpn," - ");
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
		fprintf(rpn,"%s ", $1);
	} 
	|LC	{
		stos->push($1);
		fprintf(rpn,"%d ", $1);
	}
	|'(' wyr ')'		{fprintf(rpn,"wyrazenie w nawiasach");}
	;
%%
int main(int argc, char *argv[])
{
    rpn = fopen("rpn.txt", "wt");
    threes = fopen("threes.txt", "wt");
	stos = new std::stack();

	yyparse();

	if (!stos->empty()) { 
		std::cout << "Stack is not empty!" << std::endl;
		return 1;
	}

    fclose(rpn);
    fclose(threes);
	delete stos;
	return 0;
}

char* stackBump() {
	int result = stos->top;
	int arg1 = stos->pop;

	int newResult = "result";

	stos->push(newResult);

	return makeThree(result, arg1);
}

char* makeThree(int result, int arg1) {
	std::string s = ("result = " + arg1 + "result");

	int n = s.length();

	char* char_array = new char[n+1];
	strcpy(char_array, s.c_str());

	return char_array;
}