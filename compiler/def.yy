%{
    #include <iostream>
    #include <stdbool.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string>
    #include <vector>
    #include <stack>
    extern "C" int yylex();
    extern "C" int yyerror(const char *msg, ...);

	#define INFILE_ERROR 1
	#define OUTFILE_ERROR 2

    extern FILE *yyin;
    extern FILE *yyout;

%}

%union 
{
	char *textValue;
	int	integerValue;
    double decimalValue;
};

%token INT DOUBLE STRING BOOLEAN;
%token IF ELSE WHILE RETURN;
%token READ PRINT;
%token TRUE FALSE COMMENT;
%token EQ NEQ GEQ LEQ;

%token<textValue> TEXT;
%token<integerValue> VALUE_INTEGER;
%token<decimalValue> VALUE_DECIMAL;

%%

lines:
       line
     | lines line   { printf("Syntax: wiele linii\n"); }
     ;

line:
       	declaration { printf("Syntax: linia deklaracji\n");}
     | 	assignment  { printf("Syntax: linia przypisania\n");}
     ;
     
assignment:
		typeName elementCmp '=' elementCmp ';' { printf("Syntax: przypisanie proste.\n");  }
	|	typeName elementCmp '=' expression ';' { printf("Syntax: przypisanie zlozone.\n");  }
	;

declaration:
     	typeName elementCmp ';' { printf("Syntax: deklaracja\n"); }
     ;

typeName:
       INT     {  printf("Syntax: typ int\n"); }
     | DOUBLE  {  printf("Syntax: typ double\n"); }
     | STRING  {  printf("Syntax: typ string\n"); }
     | BOOLEAN {  printf("Syntax: typ bool\n"); }
      ;

expression:
	  components '+' expression {  printf("Syntax: dodawanie\n"); }
	| components '-' expression {  printf("Syntax: odejmowanie\n"); }
	| components
	;

components:
	  components '*' elementCmp {  printf("Syntax: mnozenie\n"); }
	| components '/' elementCmp {  printf("Syntax: dzielenie\n"); }
	| elementCmp                 {  printf("(konkretnaWartosc)\n"); }
	;

elementCmp:
	   VALUE_INTEGER			{  printf("Syntax: wartosc calkowita\n"); }
	 | VALUE_DECIMAL			{  printf("Syntax: wartosc zmiennoprzecinkowa\n"); }
     | TEXT                     {  printf("Syntax: text-zmn\n"); }
	;

%%


int main(int argc, char *argv[])
{
	yyparse();
	return 0;
}