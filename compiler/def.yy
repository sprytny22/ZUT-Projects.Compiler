%{
  #include <iostream>
  #include <string> 
  #include "headers/Compiler.h"
  #include "headers/Debug.h"

  extern "C" int yylex();
  extern "C" int yyerror(const char *msg, ...);

	#define INFILE_ERROR 1
	#define OUTFILE_ERROR 2

  extern FILE *yyin;
  extern FILE *yyout;

  namespace Operators {
    std::string Sub = "sub";
    std::string Add = "add";
    std::string Mul = "mul";
    std::string Div = "div";
  }
  
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

%token INT DOUBLE STRING;
%token IF
%token READ PRINT PRINTEXT;
%token EQ NEQ GEQ LEQ LARGER SMALLER;

%token<textValue> TEXT;
%token<integerValue> VALUE_INTEGER;
%token<decimalValue> VALUE_DECIMAL;


%%

lines:
    line
  | lines line { 
      printf("wiele linii\n"); 
    }
;

line:
    declaration { 
      printf("linia deklaracji\n");
    }
  | assignment { 
      printf("linia przypisania\n");
    }
  | func ';'
  | if_expression ';'
;

expressionInBrackets:
  '(' expression ')' {
    printf("wyrazenie w nawiasie \n");
  }
;

if_start:
  IF '(' expression compOperator expression ')'  {
    printf("poczatek instrukcji warunkowej \n");  
    compiler->ifStart();
  }
;

if_expression:
    if_start '{' lines '}' {
      printf("wnetrze instrukcji warunkowej \n"); 
      compiler->ifEnd();
    }
  | if_start '{'  '}' { 
      printf("pustrze wnetrze instrukcji warunkowej \n");
      compiler->ifEnd();  
    }
;

compOperator: 
    EQ {
      printf("operator rowna sie \n");  
      compiler->pushConditionOnStack("beq");
    }
	| NEQ {
      printf("operator rozna sie \n"); 
      compiler->pushConditionOnStack("bne");
    }
	| GEQ { 
      printf("operator wiekszy rowny \n"); 
      compiler->pushConditionOnStack("bge");
    }
	| LEQ {
      printf("operator mniejszy rowny \n"); 
      compiler->pushConditionOnStack("ble");
    }
  | LARGER {
      printf("operator mniejszy rowny \n"); 
      compiler->pushConditionOnStack("bgt");
    }
  | SMALLER {
      printf("operator mniejszy rowny \n"); 
      compiler->pushConditionOnStack("blt");
    }
;

func:
    PRINT expression { 
      printf("wyswietlenie wyrazenia w nawiasie \n");
      compiler->print();
    }
  | PRINTEXT TEXT { 
      printf("wyswietlenie wyrazenia w nawiasie \n");
      compiler->printext(std::string($2));
    }
  | READ expression {
      printf("wczytywanie \n"); 
      compiler->read();   
    }
;

assignment:
    typeName elementCmp '=' elementCmp ';' { 
      printf("przypisanie proste.\n");  
    }
  | typeName elementCmp '=' expression ';' { 
      printf("przypisanie zlozone.\n");  
    }
  | TEXT '=' expression ';' { 
      printf("przypisanie identyfikatora \n");  
      compiler->simpleAssigmentText($1);
    }
  | INT TEXT '=' expression ';' { 
      printf("przypisanie identyfikatora dla inta \n");
      compiler->simpleAssigmentInt($2);
    }
  | DOUBLE TEXT '=' expression ';' { 
      printf("przypisanie identyfikatora dla double \n");
      compiler->simpleAssigmentDouble($2);
    }
;

declaration:
    INT TEXT ';' { 
      printf("deklaracja inta\n");
      compiler->declareInt(std::string($2));
    }
  | DOUBLE TEXT ';' { 
      printf("deklaracja double\n");
      compiler->declareDouble(std::string($2));
    }
; 
 
typeName:
    INT {  
      printf("typ int\n"); 
    }
  | DOUBLE {  
      printf("typ double\n"); 
    }
  | STRING { 
      printf("typ string\n"); 
    }
;

expression:
    components '+' expression {  
      printf("dodawanie\n");
      compiler->createThree(Operators::Add);
    }
	| components '-' expression { 
      printf("odejmowanie\n");
      compiler->createThree(Operators::Sub);  
    }
	| components
;

components:
	  components '*' elementCmp {  
      printf("mnozenie\n"); 
      compiler->createThree(Operators::Mul);  
    }
	| components '/' elementCmp { 
      printf("dzielenie\n"); 
      compiler->createThree(Operators::Div); 
    }
	| elementCmp { 
      printf("(skladnik)\n"); 
    }
;

elementCmp:
	  VALUE_INTEGER	{  
      printf("wartosc calkowita\n");
      compiler->pushOnStack(new Variable(LexType::Int, std::to_string($1))); 
    }
	| VALUE_DECIMAL	{  
      printf("wartosc zmiennoprzecinkowa\n");
      compiler->pushOnStack(new Variable(LexType::Double, std::to_string($1)));   
  }
  | TEXT {  
      printf("text-zmn\n");     
      compiler->pushOnStackText(new Variable(LexType::Int, std::string($1)));               
  }
;    
           
%%

int main(int argc, char *argv[])
{

  Compiler* compiler = new Compiler();

	yyparse();

  delete compiler;

	return 0;
}