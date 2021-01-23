%{
  #include <iostream>
  #include "headers/Compiler.h"

  extern "C" int yylex();
  extern "C" int yyerror(const char *msg, ...);

	#define INFILE_ERROR 1
	#define OUTFILE_ERROR 2

  extern FILE *yyin;
  extern FILE *yyout;

  Compiler *compiler = new Compiler();

%}

%union 
{
  char *textValue;
  int	integerValue;
  double decimalValue;
};

%start lines;
%right '='
%left '+' '-'
%left '*'

%token INT DOUBLE STRING BOOLEAN;
%token IF ELSE WHILE RETURN;
%token READ PRINT;
%token TRUE FALSE COMMENT;
%token EQ NEQ GEQ LEQ LARGER SMALLER;

%token<textValue> TEXT;
%token<integerValue> VALUE_INTEGER;
%token<decimalValue> VALUE_DECIMAL;


%%

lines:
    line
  | lines line { 
      printf("Syntax-Recognized: wiele linii\n"); 
    }
;

line:
    declaration { 
      printf("Syntax-Recognized: linia deklaracji\n");
    }
  | assignment { 
      printf("Syntax-Recognized: linia przypisania\n");
    }
  | if_expression ';'
;

expressionInBrackets:
  '(' expression ')' {
    printf("Syntax-Recognized: wyrazenie w nawiasie \n");
  }
;

if_start:
  IF '(' expression compOperator expression ')'  {
    printf("Syntax-Recognized: poczatek instrukcji warunkowej \n");  
  }
;

if_expression:
    if_start '{' lines '}' {
      printf("Syntax-Recognized: wnetrze instrukcji warunkowej \n"); 
    }
  | if_start '{'  '}' { 
      printf("Syntax-Recognized: pustrze wnetrze instrukcji warunkowej \n");  
    }
;

compOperator: 
    EQ {
      printf("Syntax-Recognized: operator rowna sie \n");  
    }
	| NEQ {
      printf("Syntax-Recognized: operator rozna sie \n"); 
    }
	| GEQ { 
      printf("Syntax-Recognized: operator wiekszy rowny \n"); 
    }
	| LEQ {
      printf("Syntax-Recognized: operator mniejszy rowny \n"); 
    }
;

assignment:
    typeName elementCmp '=' elementCmp ';' { 
      printf("Syntax-Recognized: przypisanie proste.\n");  
    }
  | typeName elementCmp '=' expression ';' { 
      printf("Syntax-Recognized: przypisanie zlozone.\n");  
    }
  | TEXT '=' expression ';'     { 
      printf("Syntax-Recognized: przypisanie identyfikatora \n");  
    }
  | INT TEXT '=' expression ';' { 
      printf("Syntax-Recognized: przypisanie identyfikatora dla inta \n");  
    }
  | DOUBLE TEXT '=' expression ';' { 
      printf(" Syntax-Recognized: przypisanie identyfikatora dla double \n");   
    }
;

declaration:
    INT TEXT ';' { 
      printf("Syntax-Recognized: deklaracja inta\n");
    }
  | DOUBLE TEXT ';' { 
      printf("Syntax-Recognized: deklaracja double\n");
    }
  | STRING TEXT ';' { 
      printf("Syntax-Recognized: deklaracja stringa\n");
    }
  | BOOLEAN TEXT ';' { 
      printf("Syntax-Recognized: deklaracja boola \n");
    }
;

typeName:
    INT {  
      printf("Syntax-Recognized: typ int\n"); 
    }
  | DOUBLE {  
      printf("Syntax-Recognized: typ double\n"); 
    }
  | STRING { 
      printf("Syntax-Recognized: typ string\n"); 
    }
  | BOOLEAN {  
      printf("Syntax-Recognized: typ bool\n"); 
    }
;

expression:
    components '+' expression {  
      printf("Syntax-Recognized: dodawanie\n");  
    }
	| components '-' expression { 
      printf("Syntax-Recognized: odejmowanie\n");  
    }
	| components
;

components:
	  components '*' elementCmp {  
      printf("Syntax-Recognized: mnozenie\n");  
    }
	| components '/' elementCmp { 
      printf("Syntax-Recognized: dzielenie\n"); 
    }
	| elementCmp { 
       printf("(skladnik)\n"); 
    }
;

elementCmp:
	  VALUE_INTEGER	{  
      printf("Syntax-Recognized: wartosc calkowita\n");           
    }
	| VALUE_DECIMAL	{  
      printf("Syntax-Recognized: wartosc zmiennoprzecinkowa\n");  
  }
  | TEXT {  
      printf("Syntax-Recognized: text-zmn\n"); 
      compiler->pushOnStack(new Variable(LexType::Text, std::string("test")));               
  }
;

%%

int main(int argc, char *argv[])
{
	yyparse();

	return 0;
}